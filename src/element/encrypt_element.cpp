#include "dialog/encrypt_dialog.hpp"

#include "encrypt_element.hpp"

using namespace element;

Encrypt::Encrypt(QWidget* parent) : Element(QImage(":enigma/resource/encrypt.png"), parent) { }

void Encrypt::select(const QString& file) {
  dialog::Encrypt dialog;
  if (dialog.exec())
    fire_action(file, dialog.get_password(), {{"remove", dialog.get_remove()}});
}

