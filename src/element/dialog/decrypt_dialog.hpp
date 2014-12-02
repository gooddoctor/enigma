#ifndef __DECRYPT_DIALOG_H
#define __DECRYPT_DIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace element {
  namespace dialog {
    class Decrypt : public QDialog { Q_OBJECT
    public:
      Decrypt(QWidget* parent = 0);
      QString get_password();
      bool get_show();
    private:
      QLabel* password_label;
      QLineEdit* password_input;
      QCheckBox* show_check;
      QPushButton* ok_button;
      QPushButton* cancel_button;
    };
  }
}

#endif
