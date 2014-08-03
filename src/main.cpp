#include <QDebug>

#include "recipe/crypto.hpp"

using namespace recipe;

int main(int, char**) {
  Recipe* encrypt = new Encrypt;
  encrypt->add_ingredient(Ingredient("input", QUrl("/home/gooddocteur/projects/enigma/"
   						   "lab/some_body_to_know.txt")));
  encrypt->add_ingredient(Ingredient("output", QUrl("/home/gooddocteur/projects/enigma/"
 						    "lab/some_body_to_know.dec"))); 
  encrypt->add_ingredient(Ingredient("password", QString("fish-sword")));
  encrypt->add_ingredient(Ingredient("iv", QString("fish-sword")));
  encrypt->add_ingredient(Ingredient("save", true));
  encrypt->cook();

  Recipe* decrypt = new Decrypt;
  decrypt->add_ingredient(Ingredient("input", QUrl("/home/gooddocteur/projects/enigma/"
						   "lab/some_body_to_know.dec")));
  decrypt->add_ingredient(Ingredient("output", QUrl("/home/gooddocteur/projects/enigma/"
						    "lab/some_body_to_know_dec.txt")));  
  decrypt->add_ingredient(Ingredient("password", QString("fish-sword")));
  decrypt->add_ingredient(Ingredient("iv", QString("fish-sword")));
  decrypt->add_ingredient(Ingredient("save", true));
  decrypt->cook();    

  qDebug() << encrypt->to_string();
}
