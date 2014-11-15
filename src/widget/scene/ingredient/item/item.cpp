#include "item.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

using namespace widget;

Item::Item(QGraphicsItem* parent) : Item("", parent) { }

Item::Item(const QString& name, QGraphicsItem* parent) : QGraphicsItem(parent) {
  this->name = name;
  setAcceptHoverEvents(true);
}

QString Item::get_name() {
  return name;
}

void Item::set_name(const QString& name) {
  this->name = name;
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
  if (e->button() == Qt::LeftButton)
    for (const auto& it : click_callbacks) it();
}


Button::Button(const QString& text, QGraphicsItem* parent) : Item(parent) {
  this->text = text;
  set_background(QColor(105, 210, 231));
  set_font(QFont("Monospace", 16, QFont::Bold));
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
  painter->drawRect(boundingRect());
}


Image::Image(const QString& image, QGraphicsItem* parent) : Item(parent) {
  this->image = QPixmap(image);
}

void Image::set_border(bool border) {
  this->border = border;
}

QRectF Image::boundingRect() const {
  return QRectF(0, 0, image.width(), image.height());
}

void Image::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->drawPixmap(0, 0, image);
  if (border)
    painter->drawRect(boundingRect());
}
