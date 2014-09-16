#ifndef __BASE_H
#define __BASE_H

#include <QFont>
#include <QGraphicsItem>
#include <QPainter>

namespace view {
  class Button : public QGraphicsItem {
  public:
    typedef std::function<void(void)>  ClickCallback;
    typedef std::vector<ClickCallback> ClickCallbacks;
  public:
    Button(const QString& text, QGraphicsItem* parent = 0);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    Button* on_click(const ClickCallback& callback);
  protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
  private:
    QString text;
    bool is_hover = false;
    ClickCallbacks click_callbacks;
  };

  class Image : public QGraphicsItem {
    typedef std::function<void()>  ClickCallback;
    typedef std::vector<ClickCallback> ClickCallbacks;
  public:
    Image(const QString& image, QGraphicsItem* parent = 0);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    Image* on_click(const ClickCallback& callback);
  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
  private:
    QPixmap image;
    ClickCallbacks click_callbacks;
  };

  class RotationEffect : public QWidget { Q_OBJECT
  public:
    RotationEffect(const QPixmap& from, const QPixmap& to, QWidget* parent = 0);
  private slots:
    virtual void tick(qreal ticker) = 0;
  private:
    QPixmap from;
    QPixmap to;
  protected:
    void paintEvent(QPaintEvent*);
  protected:
    int degree = 0;
  signals:
    void finish();
  };

  class LeftRotationEffect : public RotationEffect { Q_OBJECT
  public:
    LeftRotationEffect(const QPixmap& from, const QPixmap& to, QWidget* parent = 0);
  private slots:
    void tick(qreal ticker) override;
  };
  
  class RightRotationEffect : public RotationEffect { Q_OBJECT
  public:
    RightRotationEffect(const QPixmap& from, const QPixmap& to, QWidget* parent = 0);
  private slots:
    void tick(qreal ticker) override;
  };  

  class Stack : public QStackedWidget { Q_OBJECT
  public:
    Stack(QWidget* parent = 0);
    Stack* push(QGraphicsScene* scene);
    void pop();
  private:
    void show_rotation(RotationEffect* rotation);
  private slots:
    void hide_rotation();
  };

  QPixmap to_grayscale(const QPixmap& original);
  QPixmap to_rotated(const QPixmap& original, int angle, Qt::Axis axis);
  QPixmap to_pixmap(QGraphicsView* view);
}  

#endif
