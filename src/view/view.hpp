#ifndef __VIEW_H
#define __VIEW_H

#include <QWidget>

namespace view {
  class View : public QWidget {
  public:
    View(const QString& file_path, QWidget* parent = 0);
  private:
    QString file_path;
  protected:
    void closeEvent(QCloseEvent* e);
  };
}

#endif
