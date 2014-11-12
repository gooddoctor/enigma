#ifndef __ITEM_H
#define __ITEM_H

#include <QFont>
#include <QFontMetrics>
#include <QGraphicsItem>

#include "util/util.hpp"

namespace widget {
  class Item : public QGraphicsItem { 
  public:
    typedef std::function<void(void)>  ClickCallback;
    typedef std::vector<ClickCallback> ClickCallbacks;
  public:
    Item(QGraphicsItem* parent = 0);
    Item(const QString& name, QGraphicsItem* parent = 0);
    QString get_name();
    void set_name(const QString& name);
    QColor get_background();
    void set_background(const QColor& background);
    QFont get_font();
    void set_font(const QFont& font);
    bool is_hover();
    void set_hover(bool hover);
    QFontMetrics metrics() const;
    Item* on_click(const ClickCallback& callback);
  private:
    QString name;
    QColor background;
    QFont font;
    bool hover = false;
    ClickCallbacks click_callbacks;
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
    void set_border(bool border);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
  private:
    bool border = true;
    QPixmap image;
  };
}

#endif
