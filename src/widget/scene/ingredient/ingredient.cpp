#include <QPainter>

#include "util/util.hpp"

#include "ingredient.hpp"

using namespace widget;

template <typename T>
typename Ingredient<T>::Ingredients Ingredient<T>::ingredients;

template <typename T>
Ingredient<T>::Ingredient(const QString& name, const T& value) : Item(nullptr) {
  this->name = name;
  this->value = value;
  ingredients.push_back(this);
}

template <typename T>
QString Ingredient<T>::get_name() {
  return name;
}

template <typename T>
T Ingredient<T>::get_value() {
  return value;
}


Bool::Bool(const QString& name, bool value) : Ingredient<bool>(name, value) {
  pixmap = QPixmap(":ingredient/resource/bool.png");
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
  painter->setFont(bool_font);
  if (is_hover()) {
    painter->drawPixmap(0, 0, value ? to_grayscale(pixmap) : pixmap);
    set_hover(false); //show only once
  } else {
    painter->drawPixmap(0, 0, value ? pixmap : to_grayscale(pixmap));
  }
  painter->drawRect(boundingRect());
}
  

String::String(const QString& name, const QString& value) : Ingredient<QString>(name, value) { }

QRectF String::boundingRect() const {
  return QRectF(0, 0, string_metrics.width(value), string_metrics.height() + 5);
}

void String::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->drawText(0, string_metrics.height(), value);
  painter->drawRect(boundingRect());
}


Url::Url(const QString& name, const QUrl& value) : Ingredient<QUrl>(name, value)  { }

QRectF Url::boundingRect() const {
  return QRectF(0, 0, url_metrics.width(value.path()), url_metrics.height() + 10);
}

void Url::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->drawText(0, string_metrics.height(), value.path());
  painter->drawRect(boundingRect());
}
