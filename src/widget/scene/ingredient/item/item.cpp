#include "item.hpp"

#include <QPainter>

using namespace widget;

Item::Item(QGraphicsItem* parent) : QGraphicsItem(parent) {
  setAcceptHoverEvents(true);
}

QColor Item::get_background() {
  return background;
}

void Item::set_background(const QColor& background) {
  this->background = background;
}

QFont Item::get_font() {
  return font;
}

void Item::set_font(const QFont& font) {
  this->font = font;
}

bool Item::is_hover() {
  return hover;
}

void Item::set_hover(bool hover) {
  this->hover = hover; // do not need update. trust me
}

QFontMetrics Item::metrics() const {
  return QFontMetrics(font);
}

Item* Item::on_click(const ClickCallback& callback) {
  click_callbacks.push_back(callback);
  return this;
}

void Item::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
  QGraphicsItem::hoverEnterEvent(e);
  hover = true;
  update();
}

void Item::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
  QGraphicsItem::hoverLeaveEvent(e);
  hover = false;
  update();
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent* e) {
  QGraphicsItem::mousePressEvent(e);
  for (const auto& it : click_callbacks) it();
}


Button::Button(const QString& text, QGraphicsItem* parent) : Item(parent) {
  this->text = text;
  set_background(QColor(105, 210, 231));
  set_font(QFont("Monospace"));
}

QRectF Button::boundingRect() const {
  return QRectF(0, 0, metrics().width(text), metrics().height() + 10);
}

void Button::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->setPen(QPen());
  painter->setFont(get_font());
  if (!is_hover())
    painter->fillRect(boundingRect(), get_background());
  else
    painter->fillRect(boundingRect(), QColor(get_background()).darker(110));
  painter->drawText(0, metrics().height(), text);
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
