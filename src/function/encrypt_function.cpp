#include "encrypt_function.hpp"

using namespace function;

void function::encrypt(const QString& input_path, const QString& output_path, 
		       const QString& password) {
  crypto(input_path, output_path, password, &gcry_cipher_encrypt);
}
