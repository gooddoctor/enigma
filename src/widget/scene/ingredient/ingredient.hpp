#ifndef __INGREDIENT_H
#define __INGREDIENT_H

#include <QUrl>

#include "item/item.hpp"

namespace widget {
  static const QFont bool_font("monospace", 18, QFont::Bold);
  static const QFontMetrics bool_metrics(bool_font);
  static const QFont string_font("monospace", 12, QFont::Bold);
  static const QFontMetrics string_metrics(string_font);
  static const QFont url_font("monospace", 12, QFont::Bold);
  static const QFontMetrics url_metrics(string_font);

  template <typename T>
  class  Ingredient : public Item {
    typedef std::vector<Ingredient<T>*> Ingredients;
  public:
    Ingredient(const QString& name, const T& value);
    QString get_name();
    T get_value();
  private:
    static Ingredients ingredients;
  protected:
    QString name;
    T value;
  };

  class Bool : public Ingredient<bool> {
  public:
    Bool(const QString& name, bool value);
    void toggle();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
  private:
    QPixmap pixmap;
  };

  class String : public Ingredient<QString> {
  public:
    String(const QString& name, const QString& value);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
  };

  class Url : public Ingredient<QUrl> {
  public:
    Url(const QString& name, const QUrl& value);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
  };
}

#endif
