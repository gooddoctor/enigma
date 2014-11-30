#ifndef __ENCRYPT_H
#define __ENCRYPT_H

#include "element.hpp"

namespace element {
  class Encrypt : public Element { Q_OBJECT
  public:
    Encrypt(QWidget* parent = 0);
  protected:
    virtual void select(const QString& file) override;
  };
}

#endif
