#include <QFile>
#include <QMessageBox>

#include "view.hpp"

using namespace view;

View::View(const QString& file_path, QWidget* parent) : QWidget(parent) {
  this->file_path = file_path;
}

void View::closeEvent(QCloseEvent* e) {
  if (QMessageBox::question(this, "Enigma", "Remove?", 
      QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
    QFile::remove(file_path);
}
