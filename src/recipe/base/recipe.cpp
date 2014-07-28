#include <assert.h>

#include "recipe.hpp"

using namespace recipe;

static const QString TYPE_to_str[] = {"BOOL", "STRING", "URL"};

Ingredient::Ingredient() : Ingredient("", false) { }

Ingredient::Ingredient(const QString& name, const bool& value) : Ingredient(name, BOOL) {
  bool_value = value;
}

Ingredient::Ingredient(const QString& name, const QString& value) : Ingredient(name, STRING) {
  string_value = value;
}

Ingredient::Ingredient(const QString& name, const QUrl& value) :  Ingredient(name, URL) {
  url_value = value;
}
  
QString Ingredient::get_name() const {
  return name;
}

Ingredient::TYPE Ingredient::get_type() {
  return type;
}

bool Ingredient::get_bool_value() {
  return bool_value;
}

QString Ingredient::get_string_value() {
  return string_value;
}

QUrl Ingredient::get_url_value() {
  return url_value;
}

QString Ingredient::to_string() const {
  QString str = QString("(%1, %2, %3)" "\n").arg(name).arg(TYPE_to_str[type]);
  switch (type) {
    case BOOL:
      return str.arg(bool_value);
    case STRING:
      return str.arg(string_value);
    case URL:
      return str.arg(url_value.toString());
  }
}

Ingredient::Ingredient(const QString& name, const TYPE& type) {
  this->name = name;
  this->type = type;
}


Recipe::Recipe() { }

Recipe* Recipe::add_ingredient(const Ingredient& ingredient) {
  ingredients.insert({ingredient.get_name(), ingredient});
  return this;
}

Ingredient Recipe::get_ingredient(const QString& ingredient) {
  assert(ingredients.find(ingredient) != ingredients.end());
  return ingredients[ingredient];
}

QString Recipe::to_string() {
  QString str;
  for (const auto& it : ingredients)
    str.append(it.second.to_string());
  return str;
}

