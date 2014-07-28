#ifndef __RECIPE_H
#define __RECIPE_H

#include <map>

#include <QString>
#include <QUrl>

namespace recipe {
  class Ingredient {
  public:
    enum TYPE {BOOL, STRING, URL};
  public:
    Ingredient();
    Ingredient(const QString& name, const bool& value);
    Ingredient(const QString& name, const QString& value);
    Ingredient(const QString& name, const QUrl& value);
    //meta
    QString get_name() const;
    TYPE get_type();
    //getters
    bool get_bool_value();
    QString get_string_value();
    QUrl get_url_value();
    //other
    QString to_string() const;
  private:
    Ingredient(const QString& name, const TYPE& type);
  private:
    //meta
    QString name;
    TYPE type;
    //values
    bool bool_value;
    QString string_value;
    QUrl url_value;
  };

  class Recipe {
  typedef std::map<QString, Ingredient> Ingredients;
  public:
    Recipe();
    Recipe* add_ingredient(const Ingredient& ingredient);
    Ingredient get_ingredient(const QString& ingredient);
    QString to_string();
  private:
    Ingredients ingredients;
  };
}

#endif
