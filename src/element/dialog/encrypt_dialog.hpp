#ifndef __ENCRYPT_DIALOG_H
#define __ENCRYPT_DIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace element {
  class EncryptDialog : public QDialog { Q_OBJECT
  public:
    EncryptDialog(QWidget* parent = 0);
    QString get_password();
    bool get_remove();
  private:
    QLabel* password_label;
    QLineEdit* password_input;
    QCheckBox* remove_check;
    QPushButton* ok_button;
    QPushButton* cancel_button;
  };
}

#endif
