#include "dialog/encrypt_dialog.hpp"

#include "encrypt.hpp"

using namespace element;

Encrypt::Encrypt(QWidget* parent) : Element(QImage("resource/encrypt.png"), parent) { }

void Encrypt::select(const QString& file) {
  EncryptDialog dialog;
  if (dialog.exec())
    fire_action(file, dialog.get_password(), {{"remove", dialog.get_remove()}});
}

