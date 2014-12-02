#ifndef __FUNCTION_H
#define __FUNCTION_H

#include <gcrypt.h>

#include <QByteArray>
#include <QString>

namespace function {
  typedef std::function<gcry_error_t(gcry_cipher_hd_t, unsigned char*, size_t,
				     const unsigned char*, size_t)> CryptoCallback;
  class Block {
  public:
    Block(const QByteArray& data, int multiplicity, const char fill);
    Block(const Block& other) ;
    char* get_data();
    int get_size();
  private:
    QByteArray data;
  };

  void crypto(const QString& input_path, const QString& output_path, const QString& password,
	      const CryptoCallback& crypto_callback);
}

#endif
