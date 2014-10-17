#include <QApplication>
#include <QDebug>
#include <QDir>
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

  OneIngredientScene* scene = new OneIngredientScene();
  scene->on_finish([encrypt]() {
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
  scene->setSceneRect(0, 0, 640, 480);
  
  Button* backward = new Button("Назад");
  backward->setPos(0, 440);
  backward->on_click([scene]() {
    scene->before_one();
  });
  scene->addItem(backward);

  Button* next = new Button("Вперед");
  next->setPos(backward->boundingRect().width() + 5, 440);
  next->on_click([scene]() {
    scene->after_one();
  });
  scene->addItem(next);


  for (auto& it : encrypt->get_ingredients()) {
    switch (it.second.get_type()) {
      case recipe::Ingredient::BOOL: {
	Bool* boolean = new Bool(it.second.get_name(), it.second.get_bool_value());
	scene->add_ingredient(boolean);
	break;
      }
      case recipe::Ingredient::STRING: {
	String* str = new String(it.second.get_name(), it.second.get_string_value());
	str->on_click([str]() {
	  StringScene* scene = new StringScene();
	  scene->on_finish([str, scene]() {
	    str->set_value(scene->get_input());
	  });
	  main_window->push(scene);
	});
	scene->add_ingredient(str);
	break;
      }
      case recipe::Ingredient::URL: {
	Url* url = new Url(it.second.get_name(), it.second.get_url_value());
	url->on_click([url]() {
	  UrlScene* scene = new UrlScene();
	  scene->on_finish([url, scene]() {
	    url->set_value(scene->get_input());
	  });
	  scene->on_new_file([scene]() {
	    StringScene* subscene = new StringScene();
	    subscene->on_finish([scene, subscene]() {
	      QFile file(QDir(scene->get_input().toString()).filePath(subscene->get_input()));
	      file.open(QIODevice::ReadWrite); //create file
	      file.close();
	    });
	    main_window->push(subscene);
	  });
	  main_window->push(scene);
	});
	scene->add_ingredient(url);
	break;
      }
    }
  }
  
  // Image* finish = new Image("resource/finish.png");
  // finish->on_click([encrypt]() {
  //   for (auto& it : encrypt->get_ingredients()) {
  //     switch (it.second.get_type()) {
  // 	case recipe::Ingredient::BOOL:
  // 	  encrypt->add_ingredient(recipe::
  // 				  Ingredient(it.second.get_name(),  
  // 					     Bool::find(it.second.get_name())->get_value()));
  // 	  break;
  // 	case recipe::Ingredient::STRING:
  // 	  encrypt->add_ingredient(recipe::
  // 				  Ingredient(it.second.get_name(),
  // 					     String::find(it.second.get_name())->get_value()));
  // 	  break;
  // 	case recipe::Ingredient::URL:
  // 	  encrypt->add_ingredient(recipe::
  // 				  Ingredient(it.second.get_name(),
  // 					     Url::find(it.second.get_name())->get_value()));
  // 	  break;
  //     }
  //   }
  //   encrypt->cook();
  // });
  // finish->setPos(pos, 60);
  // scene->addItem(finish);

  main_window = new RotationStackWidget();
  main_window->push(scene);
  main_window->show();

  return app.exec();
}


