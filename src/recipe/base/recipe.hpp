#ifndef __RECIPE_H
#define __RECIPE_H

#include <map>

#include <QString>
#include <QUrl>

namespace recipe {
  class Block {
  public:
    Block(const QByteArray& data, int multiplicity, const char fill);
    Block(const Block& other);
    char* get_data();
    int get_multiplicity();
    char get_fill();
    int get_size();
    QString to_string();
  private:
    QByteArray data;
    int multiplicity;
    char fill;
  };

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
    virtual Recipe* add_ingredient(const Ingredient& ingredient);
    virtual Ingredient get_ingredient(const QString& ingredient);
    virtual Ingredients get_ingredients();
    virtual Recipe* cook() = 0;
    virtual QString to_string();
  private:
    Ingredients ingredients;
  };

  void e_assert(bool expression, const QString& message);
}

#endif
