#ifndef __ITEM_H
#define __ITEM_H

#include <QFont>
#include <QFontMetrics>
#include <QGraphicsItem>

namespace widget {
  static const QColor button_background(105, 210, 231);
  static const QFont button_font("Monospace");
  static const QFontMetrics button_metrics(button_font);

  class Item : public QGraphicsItem { 
  public:
    typedef std::function<void(void)>  ClickCallback;
    typedef std::vector<ClickCallback> ClickCallbacks;
  public:
    Item(QGraphicsItem* parent = 0);
    bool is_hover();
    void set_hover(bool hover);
    Item* on_click(const ClickCallback& callback);
  private:
    ClickCallbacks click_callbacks;
    bool hover = false;
  protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* e) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* e) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
  };

  class Button : public Item {
  public:
    Button(const QString& text, QGraphicsItem* parent = 0);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
  private:
    QString text;
  };

  class Image : public Item {
  public:
    Image(const QString& image, QGraphicsItem* parent = 0);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
  private:
    QPixmap image;
  };
}

#endif
