#ifndef __HINT_H
#define __HINT_H

#include <QGraphicsTextItem>
#include <QTimer>
#include <QWidget>

namespace widget {
  class Hint : public QWidget { Q_OBJECT
  public:
    static Hint* instance() {
      static Hint* instance = new Hint();
      return instance;
    }
  public:
    void set_short_hint(const QString& hint);
  private:
    Hint();
  private:
    QTimer* timer;
    QPixmap background;
    QGraphicsTextItem* hint_item;
  protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent* event) override;    
  };
}

#endif
