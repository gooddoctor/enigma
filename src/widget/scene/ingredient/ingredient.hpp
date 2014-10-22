#ifndef __INGREDIENT_H
#define __INGREDIENT_H

#include <QUrl>

#include "item/item.hpp"

namespace widget {
  template <typename T>
  class  Ingredient : public Item {
    typedef std::vector<Ingredient<T>*> Ingredients;
    typedef std::function<void(void)> ChangeCallback;
    typedef std::vector<ChangeCallback> ChangeCallbacks;
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
    void set_name(const QString& name) {
      this->name = name;
    }
    T get_value() {
      return value;
    }
    void set_value(const T& value) {
      this->value = value;
      for (const auto& it : change_callbacks) it(); //fire change, fire
    }
    void on_change(const ChangeCallback& callback) {
      change_callbacks.push_back(callback);
    }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
      painter->setFont(get_font());
      painter->drawRect(boundingRect());
      painter->fillRect(boundingRect(), get_background());
    }
    QRectF boundingRect() const {
      return QRectF(0, 0, 600, 360);
    }
  private:
    static Ingredients ingredients;
    ChangeCallbacks change_callbacks;
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
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override;
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
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override;
  };

  class Url : public Ingredient<QUrl> {
  public:
    static Url* find(const QString& name) {
      return dynamic_cast<Url*>(Ingredient<QUrl>::find(name));
    } 
  public:
    Url(const QString& name, const QUrl& value);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override;
  };
}

#endif
