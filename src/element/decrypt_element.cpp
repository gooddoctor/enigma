#include "dialog/decrypt_dialog.hpp"

#include "decrypt_element.hpp"

using namespace element;

Decrypt::Decrypt(QWidget* parent) : Element(QImage("resource/decrypt.png"), parent) { }

void Decrypt::select(const QString& file) {
  dialog::Decrypt dialog;
  if (dialog.exec())
    fire_action(file, dialog.get_password(), {{"show", dialog.get_show()}});
}



