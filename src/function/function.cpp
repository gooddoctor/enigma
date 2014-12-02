#include <cassert>

#include <QFile>

#include "function.hpp"

using namespace function;

Block::Block(const QByteArray& data, int multiplicity, const char fill) {
  if (data.size() % multiplicity == 0)
    this->data = data;
  else
    this->data = data.leftJustified(((data.size() / multiplicity) + 1) * multiplicity,
				    fill);
}

Block::Block(const Block& other) {
  this->data = other.data;
}

char* Block::get_data() {
  return data.data();
}

int Block::get_size() {
  return data.size();
}


void function::crypto(const QString& input_path, const QString& output_path, const QString& password,
		      const CryptoCallback& crypto_callback) {
  gcry_error_t error;
  gcry_cipher_hd_t cipher_hd;
  error = gcry_cipher_open(&cipher_hd, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_ECB, 0);
  assert(!error);

  Block password_block(password.toUtf8(), gcry_cipher_get_algo_keylen(GCRY_CIPHER_AES128), '\0');
  error = gcry_cipher_setkey(cipher_hd, password_block.get_data(), 
  			     gcry_cipher_get_algo_keylen(GCRY_CIPHER_AES128));
  assert(!error);
  
  Block iv(password.toUtf8(), gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES128), '\0');
  error = gcry_cipher_setiv(cipher_hd, iv.get_data(), 
			    gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES128));
  assert(!error);

  QFile input_file(input_path);
  bool success = input_file.open(QIODevice::ReadOnly);
  assert(success);

  Block input_block(input_file.readAll(), gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES128), '\0');
  Block output_block(input_block);
  error = crypto_callback(cipher_hd, (unsigned char*)output_block.get_data(), output_block.get_size(),
			  (unsigned char*)input_block.get_data(), input_block.get_size());
  assert(!error);

  QFile output_file(output_path);
  success = output_file.open(QIODevice::WriteOnly);
  assert(success);

  int num = output_file.write(output_block.get_data(), output_block.get_size());
  assert(num == output_block.get_size());
}

