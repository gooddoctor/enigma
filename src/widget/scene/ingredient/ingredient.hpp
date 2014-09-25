#ifndef __INGREDIENT_H
#define __INGREDIENT_H

#include <QUrl>

#include "item/item.hpp"

namespace widget {
  template <typename T>
  class  Ingredient : public Item {
    typedef std::vector<Ingredient<T>*> Ingredients;
  public:
    static Ingredient<T>* find(const QString& name) {
      for (auto it :ingredients) {
	if (it->get_name() == name)
	  return it;
      }
      return nullptr;
    }
  public:
    Ingredient(const QString& name, const T& value) {
      this->name = name;
      this->value = value;
      ingredients.push_back(this);
    }
    QString get_name() {
      return name;
    }
    T get_value() {
      return value;
    }
  private:
    static Ingredients ingredients;
  protected:
    QString name;
    T value;
  };

  class Bool : public Ingredient<bool> {
  public:
    static Bool* find(const QString& name) {
      return dynamic_cast<Bool*>(Ingredient<bool>::find(name));
    }
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
    static String* find(const QString& name) {
      return dynamic_cast<String*>(Ingredient<QString>::find(name));
    }
  public:
    String(const QString& name, const QString& value);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
  };

  class Url : public Ingredient<QUrl> {
  public:
    static Url* find(const QString& name) {
      return dynamic_cast<Url*>(Ingredient<QUrl>::find(name));
    } 
  public:
    Url(const QString& name, const QUrl& value);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
  };
}

#endif
