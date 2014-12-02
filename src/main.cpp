#include "function/encrypt_function.hpp"
#include "function/decrypt_function.hpp"

using namespace function;

int main(int argc, char** argv) {
  encrypt("test.txt", "test.dec", "hello how you doin");
  decrypt("test.dec", "test.dec.txt", "hello how you doin");
}
