#include "item.hpp"

#include <QPainter>

using namespace widget;

Item::Item(QGraphicsItem* parent) : QGraphicsItem(parent) {
  setAcceptHoverEvents(true);
}

bool Item::is_hover() {
  return hover;
}

Item* Item::on_click(const ClickCallback& callback) {
  click_callbacks.push_back(callback);
  return this;
}

void Item::hoverEnterEvent(QGraphicsSceneHoverEvent*) {
  hover = true;
  update();
}

void Item::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
  hover = false;
  update();
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent*) {
  for (const auto& it : click_callbacks)
    it();
}


Button::Button(const QString& text, QGraphicsItem* parent) : Item(parent) {
  this->text = text;
}

QRectF Button::boundingRect() const {
  return QRectF(0, 0, button_metrics.width(text), button_metrics.height() + 10);
}

void Button::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->setPen(QPen());
  painter->setFont(button_font);
  if (!is_hover())
    painter->fillRect(boundingRect(), button_background);
  else
    painter->fillRect(boundingRect(), QColor(button_background).darker(110));
  painter->drawText(0, button_metrics.height(), text);
}


Image::Image(const QString& image, QGraphicsItem* parent) : Item(parent) {
  this->image = QPixmap(image);
}

QRectF Image::boundingRect() const {
  return QRectF(0, 0, image.width(), image.height());
}

void Image::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->drawPixmap(0, 0, image);
  painter->drawRect(boundingRect());
}
