#include <QFile>

#include "crypto.hpp"

using namespace recipe;

Crypto::Crypto() {
  //add some common ingredient to our recipe
  add_ingredient(Ingredient("input", QUrl("")));
  add_ingredient(Ingredient("output", QUrl("")));
  add_ingredient(Ingredient("password", QString("")));
  add_ingredient(Ingredient("iv", QString("")));
  add_ingredient(Ingredient("save", false));
  //add some commin binding
  add_binding("input", "output");
  //add some common short descriptions
  add_short_description("input", "Входной файл?");
  add_short_description("output", "Файл на выходе?");
  add_short_description("password", "Пароль?");
  add_short_description("iv", "Вектор???");
  add_short_description("save", "Сохранить оригинал?");
  //add some common long descriptions
  add_long_description("save", " Указывает на то, будет ли сохранен входной файл");
}

Crypto* Crypto::apply(const Callback& callback) {
  gcry_error_t error;
  gcry_cipher_hd_t cipher_hd;
  
  error = gcry_cipher_open(&cipher_hd, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_ECB, 0);
  e_assert(!error, "gcry_cipher_open fail");

  Block password(get_ingredient("password").get_string_value().toUtf8(),
		 gcry_cipher_get_algo_keylen(GCRY_CIPHER_AES128), '\0');
  error = gcry_cipher_setkey(cipher_hd, password.get_data(), 
 			     gcry_cipher_get_algo_keylen(GCRY_CIPHER_AES128));
  e_assert(!error, "gcry_cipher_setkey fail");

  Block iv(get_ingredient("iv").get_string_value().toUtf8(), 
	   gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES128), '\0');
  error = gcry_cipher_setiv(cipher_hd, iv.get_data(), 
			    gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES128));
  e_assert(!error, "gcry_cipher_setiv fail");

  QFile input(get_ingredient("input").get_url_value().path());
  bool success = input.open(QIODevice::ReadOnly);
  e_assert(success, "open " + input.fileName() + " fail");

  Block in(input.readAll(), gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES128), '\0');
  Block out(in);
  error = callback(cipher_hd, (unsigned char*)out.get_data(), out.get_size(), 
	      (unsigned char*)in.get_data(), in.get_size());
  e_assert(!error, "crypto callback fail");

  QFile output(get_ingredient("output").get_url_value().path());
  success = output.open(QIODevice::WriteOnly);
  e_assert(success, "open " + output.fileName() + " fail");
  
  int num = output.write(out.get_data(), out.get_size());
  e_assert(num == out.get_size(), "write " + output.fileName() + " fail");

  return this;
}


Encrypt::Encrypt() {
  add_long_description("input", "Указывает файл который будет содержать исходный текст");
  add_long_description("output", "Указывает файл который будет содержать шифрованный текст");
  add_long_description("password", "Ключ который будет использоваться для шифрования");
  add_long_description("iv", "Инициализационный вектор использованный в шифровании...");
}

Encrypt* Encrypt::cook() {
  apply(gcry_cipher_encrypt);
  return this;
}


Decrypt::Decrypt(){
  add_long_description("input", "Указывает файл который будет содержать шифрованный текст");
  add_long_description("output", "Указывает файл который будет содержать расшифрованный текст");
  add_long_description("password", "Указывает ключ который будет использоваться при расшифровки");
  add_long_description("iv", "Инициализационный вектор использованный при расшифровки...");
}

Decrypt* Decrypt::cook() {
  apply(gcry_cipher_decrypt);
  return this;
}

