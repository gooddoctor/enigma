#include <QPainter>

#include "ingredient.hpp"

using namespace widget;

template <typename T>
typename Ingredient<T>::Ingredients Ingredient<T>::ingredients;

Bool::Bool(const QString& name, bool value) : Ingredient<bool>(name, value) {
  pixmap = QPixmap(":ingredient/resource/bool.png");
  set_background(QColor(250,105,0));
  set_font(QFont("monospace", 18, QFont::Bold));
  on_click(std::bind(&Bool::toggle, this));
}

void Bool::toggle() {
  value = !value;
  update();
}

void Bool::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) {
  Ingredient<bool>::paint(painter, item, widget);
  painter->drawPixmap((boundingRect().width() -  pixmap.width()) / 2, 
		      (boundingRect().height() - pixmap.height()) /2, 
		      value ? to_grayscale(pixmap) : pixmap);
}
  

String::String(const QString& name, const QString& value) : Ingredient<QString>(name, value) {
  set_background(QColor(224,228,204));
  set_font(QFont("monospace", 18, QFont::Bold));
}

void String::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) {
  Ingredient<QString>::paint(painter, item, widget);
  painter->drawText((boundingRect().width() - metrics().width(value)) / 2, 
		    (boundingRect().height() - metrics().height()) / 2, 
		    value);
}


Url::Url(const QString& name, const QUrl& value) : Ingredient<QUrl>(name, value)  {
  set_background(QColor(243,134,48));
  set_font(QFont("monospace", 12, QFont::Bold));
}

void Url::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) {
  Ingredient<QUrl>::paint(painter, item, widget);
  if (metrics().width("M") * value.path().size() > boundingRect().width()) { //stripped variant
    QString stripped = value.path().mid(0, boundingRect().width() / metrics().width("M"));
    stripped = stripped.mid(0, stripped.size() - 3) + "...";
    painter->drawText((boundingRect().width() - metrics().width(stripped)) / 2, 
		      (boundingRect().height() - metrics().height()) / 2, 
		      stripped);
  } else { //not stripped variant
  painter->drawText((boundingRect().width() - metrics().width(value.path())) / 2, 
		    (boundingRect().height() - metrics().height()) / 2, 
		    value.path());
  }
}
