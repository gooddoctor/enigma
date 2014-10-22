#include <gcrypt.h>

#include "base/recipe.hpp"

namespace recipe {
  class Crypto : public Recipe {
    typedef std::function<gcry_error_t(gcry_cipher_hd_t, unsigned char*, size_t,
					  const unsigned char*, size_t)> Callback;
  public:
    Crypto();
    Crypto* apply(const Callback& callback);
  };

  class Encrypt : public Crypto {
  public:
    Encrypt* cook() override;
  };

  class Decrypt : public Crypto {
  public:
    Decrypt* cook() override;
  };  
}
  
