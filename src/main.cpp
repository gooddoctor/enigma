#include <QDebug>

#include "recipe/base/recipe.hpp"

using namespace recipe;

int main(int, char**) {
  Recipe recipe;
  recipe.add_ingredient(Ingredient("input", QUrl("/home/gooddocteur/somebody_body_to_know.txt")));
  recipe.add_ingredient(Ingredient("password", QString("243165482")));
  recipe.add_ingredient(Ingredient("output", 
				   QUrl("/home/gooddocteur/somebody_body_to_know_dec.txt")));
  recipe.add_ingredient(Ingredient("is_delete", true));
  
  qDebug() << recipe.to_string();
}
