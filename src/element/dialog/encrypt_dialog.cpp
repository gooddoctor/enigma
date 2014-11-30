#include <QGridLayout>

#include "encrypt_dialog.hpp"

using namespace element;

EncryptDialog::EncryptDialog(QWidget* parent) : QDialog(parent) {
  password_label = new QLabel("Пароль");
  password_input = new QLineEdit();
  remove_check = new QCheckBox("Удалить оригинал");
  //create buttons;
  ok_button = new QPushButton("OK");
  cancel_button = new QPushButton("Cancel");
  connect(ok_button, SIGNAL(clicked()), SLOT(accept()));
  connect(cancel_button, SIGNAL(clicked()), SLOT(reject()));
  //layout out it
  QGridLayout* layout = new QGridLayout();
  layout->addWidget(password_label, 0, 0);
  layout->addWidget(password_input, 0, 1);
  layout->addWidget(remove_check, 1, 0);
  layout->addWidget(ok_button, 2, 0);
  layout->addWidget(cancel_button, 2, 1);
  setLayout(layout);
}

QString EncryptDialog::get_password() {
  return password_input->text();
}

bool EncryptDialog::get_remove() {
  return remove_check->isChecked();
}

  
