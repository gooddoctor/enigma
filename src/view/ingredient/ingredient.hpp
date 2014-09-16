#ifndef __INGREDIENT_H
#define __INGREDIENT_H

#include <QUrl>

#include "base/base.hpp"

namespace view {
  template <typename T>
  class Ingredient : public QGraphicsItem {
  public:
    Ingredient(const QString& name, const T& value);
    QString get_name();
    T get_value();
  protected:
    QString name;
    T value;
  };

  class Bool : public Ingredient<bool> {
  public:
    Bool(const QString& name, bool value);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
  protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
  private:
    QPixmap pixmap;
    bool highlight_effect = false;
  };

  class String : public Ingredient<QString> {
  public:
    String(const QString& name, const QString& value);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    String* on_enter(const Button::ClickCallback& callback);
  private:
    Button* enter;
  };

  class Url : public Ingredient<QUrl> {
  public:
    Url(const QString& name, const QUrl& value);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    Url* on_browse(const Button::ClickCallback& callback);
  private:
    Button* browse;
    QGraphicsTextItem* path;
  };
}

#endif
