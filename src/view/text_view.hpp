#ifndef __TEXT_VIEW_H
#define __TEXT_VIEW_H

#include <QPlainTextEdit>

#include "view.hpp"

namespace view {
  class Text : public View {
  public:
    Text(const QString& file_path, QWidget* parent = 0);
  private:
    QPlainTextEdit* text_edit;
  };
}

#endif
