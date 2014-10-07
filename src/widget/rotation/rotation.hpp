#ifndef __ROTATION_H
#define __ROTATION_H

#include <QWidget>

namespace widget {
  class Rotation : public QWidget { Q_OBJECT
  public:
    Rotation(const QImage& from, const QImage& to, QWidget* parent = 0);
  private slots:
    virtual void tick(qreal ticker) = 0;
  private:
    QImage from;
    QImage to;
  protected:
    void paintEvent(QPaintEvent*);
  protected:
    int degree = 0;
  signals:
    void finish();
  };

  class LeftRotation : public Rotation { Q_OBJECT
  public:
    LeftRotation(const QPixmap& from, const QPixmap& to, QWidget* parent = 0);
  private slots:
    void tick(qreal ticker) override;
  };

  class RightRotation : public Rotation { Q_OBJECT
  public:
    RightRotation(const QPixmap& from, const QPixmap& to, QWidget* parent = 0);
  private slots:
    void tick(qreal ticker) override;
  };
}

#endif
