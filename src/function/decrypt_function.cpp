#include "decrypt_function.hpp"

using namespace function;

void function::decrypt(const QString& input_path, const QString& output_path, 
		       const QString& password) {
  crypto(input_path, output_path, password, &gcry_cipher_decrypt);
}
