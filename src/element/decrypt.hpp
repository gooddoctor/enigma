#ifndef __DECRYPT_H
#define __DECRYPT_H

#include "element.hpp"

namespace element {
  class Decrypt : public Element { Q_OBJECT
  public:
    Decrypt(QWidget* parent = 0);
  protected:
    virtual void select(const QString& file) override;
  };
}

#endif
