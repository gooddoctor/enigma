#include <QGridLayout>

#include "decrypt_dialog.hpp"

using namespace element;

DecryptDialog::DecryptDialog(QWidget* parent) : QDialog(parent) {
  password_label = new QLabel("Пароль");
  password_input = new QLineEdit();
  show_check = new QCheckBox("Просмотр в редакторе");
  //create buttons;
  ok_button = new QPushButton("OK");
  cancel_button = new QPushButton("Cancel");
  connect(ok_button, SIGNAL(clicked()), SLOT(accept()));
  connect(cancel_button, SIGNAL(clicked()), SLOT(reject()));
  //layout out it
  QGridLayout* layout = new QGridLayout();
  layout->addWidget(password_label, 0, 0);
  layout->addWidget(password_input, 0, 1);
  layout->addWidget(show_check, 1, 0);
  layout->addWidget(ok_button, 2, 0);
  layout->addWidget(cancel_button, 2, 1);
  setLayout(layout);
}

QString DecryptDialog::get_password() {
  return password_input->text();
}

bool DecryptDialog::get_show() {
  return show_check->isChecked();
}
