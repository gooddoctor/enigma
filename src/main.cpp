#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>

#include "recipe/crypto.hpp"
#include "widget/widget.hpp"


using namespace recipe;
using namespace widget;

RotationStackWidget* main_window;

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  
  Recipe* encrypt = new Encrypt();
  encrypt->add_ingredient(recipe::Ingredient("input", QUrl("/home/gooddocteur/projects/enigma/"
							   "lab/some_body_to_know.txt")));
  encrypt->add_ingredient(recipe::Ingredient("output", QUrl("/home/gooddocteur/projects/enigma/"
							    "lab/some_body_to_know.dec"))); 
  encrypt->add_ingredient(recipe::Ingredient("password", QString("fish-sword")));
  encrypt->add_ingredient(recipe::Ingredient("iv", QString("fish-sword")));
  encrypt->add_ingredient(recipe::Ingredient("save", true));

  Scene* scene = new Scene();
  int pos = 0;
  for (auto& it : encrypt->get_ingredients()) {
    switch (it.second.get_type()) {
      case recipe::Ingredient::BOOL: {
	Bool* boolean = new Bool(it.second.get_name(), it.second.get_bool_value());
	boolean->setPos(pos, 60);
	scene->addItem(boolean);
	break;
      }
      case recipe::Ingredient::STRING: {
	String* str = new String(it.second.get_name(), it.second.get_string_value());
	str->on_click([str]() {
	  StringScene* scene = new StringScene();
	  scene->on_ok([str, scene]() {
	    str->set_value(scene->get_input());
	  });
	  main_window->push(scene);
	});
	str->setPos(pos, 60);
	scene->addItem(str);
	break;
      }
      case recipe::Ingredient::URL: {
	Url* url = new Url(it.second.get_name(), it.second.get_url_value());
	url->on_click([url]() {
	  UrlScene* scene = new UrlScene();
	  scene->on_ok([url, scene]() {
	    url->set_value(scene->get_input());
	  });
	  main_window->push(scene);
	});
	url->setPos(pos, 60);
	scene->addItem(url);
	break;
      }
    }
    pos += 600;
  }

  Image* finish = new Image("resource/finish.png");
  finish->on_click([encrypt]() {
    for (auto& it : encrypt->get_ingredients()) {
      switch (it.second.get_type()) {
	case recipe::Ingredient::BOOL:
	  encrypt->add_ingredient(recipe::
				  Ingredient(it.second.get_name(),  
					     Bool::find(it.second.get_name())->get_value()));
	  break;
	case recipe::Ingredient::STRING:
	  encrypt->add_ingredient(recipe::
				  Ingredient(it.second.get_name(),
					     String::find(it.second.get_name())->get_value()));
	  break;
	case recipe::Ingredient::URL:
	  encrypt->add_ingredient(recipe::
				  Ingredient(it.second.get_name(),
					     Url::find(it.second.get_name())->get_value()));
	  break;
      }
    }
    encrypt->cook();
  });
  finish->setPos(pos, 60);
  scene->addItem(finish);


  main_window = new RotationStackWidget();
  main_window->push(scene);
  main_window->show();

  return app.exec();
}


