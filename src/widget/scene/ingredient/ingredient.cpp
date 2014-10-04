#include <QPainter>

#include "ingredient.hpp"

using namespace widget;

template <typename T>
typename Ingredient<T>::Ingredients Ingredient<T>::ingredients;


Bool::Bool(const QString& name, bool value) : Ingredient<bool>(name, value) {
  pixmap = QPixmap(":ingredient/resource/bool.png");
  set_font(QFont("monospace", 18, QFont::Bold));
  on_click(std::bind(&Bool::toggle, this));
}

void Bool::toggle() {
  value = !value;
  update();
}

QRectF Bool::boundingRect() const {
  return QRectF(0, 0, pixmap.width(), pixmap.height());
}

void Bool::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->setFont(get_font());
  if (is_hover()) {
    painter->drawPixmap(0, 0, value ? to_grayscale(pixmap) : pixmap);
    set_hover(false); //show only once
  } else {
    painter->drawPixmap(0, 0, value ? pixmap : to_grayscale(pixmap));
  }
  painter->drawRect(boundingRect());
}
  

String::String(const QString& name, const QString& value) : Ingredient<QString>(name, value) {
  set_font(QFont("monospace", 12, QFont::Bold));
}

QRectF String::boundingRect() const {
  return QRectF(0, 0, metrics().width(value), metrics().height() + 5);
}

void String::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->drawText(0, metrics().height(), value);
  painter->drawRect(boundingRect());
}


Url::Url(const QString& name, const QUrl& value) : Ingredient<QUrl>(name, value)  { }

QRectF Url::boundingRect() const {
  return QRectF(0, 0, metrics().width(value.path()), metrics().height() + 10);
}

void Url::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->drawText(0, metrics().height(), value.path());
  painter->drawRect(boundingRect());
}
