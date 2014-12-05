#include <QVBoxLayout>

#include "text_view.hpp"

using namespace view;

Text::Text(const QString& file_path, QWidget* parent) : View(file_path, parent) {
  text_edit = new QPlainTextEdit();
  //fill it
  QFile file(file_path);
  file.open(QIODevice::ReadOnly);
  text_edit->setPlainText(file.readAll());
  //place it
  QVBoxLayout* layout = new QVBoxLayout();
  layout->setContentsMargins(QMargins(0, 0, 0, 0));
  layout->addWidget(text_edit);
  setLayout(layout);
}
