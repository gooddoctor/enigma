#include <QFont>
#include <QFontMetrics>
#include <QPainter>

#include "ingredient.hpp"

using namespace view;

template <typename T>
Ingredient<T>::Ingredient(const QString& name, const T& value) : QGraphicsItem(nullptr) {
  this->name = name;
  this->value = value;
}

template <typename T>
QString Ingredient<T>::get_name() {
  return name;
}

template <typename T>
T Ingredient<T>::get_value() {
  return value;
}


static const QFont bool_font("monospace", 18, QFont::Bold);
static const QFontMetrics bool_metrics(bool_font);

Bool::Bool(const QString& name, bool value) : Ingredient<bool>(name, value) {
  setAcceptHoverEvents(true);
  pixmap = QPixmap(":ingredient/resource/bool.png");
}

QRectF Bool::boundingRect() const {
  return QRectF(0, 0, pixmap.width(), pixmap.height());
}

void Bool::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->setFont(bool_font);
  if (highlight_effect) {
    painter->drawPixmap(0, 0, value ? to_grayscale(pixmap) : pixmap);
    highlight_effect = false; //show only once
  } else {
    painter->drawPixmap(0, 0, value ? pixmap : to_grayscale(pixmap));
  }
  painter->drawRect(boundingRect());
}

void Bool::hoverEnterEvent(QGraphicsSceneHoverEvent*) {
  highlight_effect = true;
  update();
}

void Bool::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
  highlight_effect = false;
  update();
}

void Bool::mousePressEvent(QGraphicsSceneMouseEvent*) {
  value = !value;
  update();
}


static QFont string_font("monospace", 12, QFont::Bold);
static QFontMetrics string_metrics(string_font);

String::String(const QString& name, const QString& value) : Ingredient<QString>(name, value) {
  enter = new Button("Ввод", this);
  enter->setPos(2, string_metrics.height() + 5);
}

QRectF String::boundingRect() const {
  return QRectF(0, 0, std::max(string_metrics.width(value), (int)enter->boundingRect().width()), 
		string_metrics.height() + enter->boundingRect().height() + 5);
}

void String::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->drawText(0, string_metrics.height(), value);
  painter->drawRect(boundingRect());
}

String* String::on_enter(const Button::ClickCallback& callback) {
  enter->on_click(callback);
  return this;
}


Url::Url(const QString& name, const QUrl& value) : Ingredient<QUrl>(name, value)  {
  this->path = new QGraphicsTextItem(value.path(), this);
  this->path->setTextInteractionFlags(Qt::TextSelectableByMouse);
  this->path->setPos(0, 0);
  browse = new Button("Обзор", this);
  browse->setPos(2, this->path->boundingRect().height() + 5);
}

QRectF Url::boundingRect() const {
  return QRectF(0, 0, path->boundingRect().width(), 
		path->boundingRect().height() + browse->boundingRect().height() + 10);
}

void Url::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->setPen(QPen());
  painter->drawRect(boundingRect());
}

Url* Url::on_browse(const Button::ClickCallback& callback) {
  browse->on_click(callback);
  return this;
}




