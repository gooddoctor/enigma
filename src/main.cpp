#include <assert.h>

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

  scene->on_mouse_right([encrypt, scene]() {
    Hint* hint = Hint::instance();
    hint->set_short_hint(encrypt->get_long_description(scene->get_one()->get_name()));
    hint->move(main_window->geometry().x(), main_window->geometry().y());
    hint->show();
  });
  
  scene->on_wheel_up([scene]() {
    scene->after_one();
  });

  scene->on_wheel_down([scene]() {
    scene->before_one();
  });

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
  
  
  Image* mouse_right = new Image("resource/mouse_right.png");
  mouse_right->set_border(false);
  mouse_right->setPos(520, 5);
  scene->addItem(mouse_right);

  Image* help = new Image("resource/help.png");
  help->setPos(570, 5);
  scene->addItem(help);
  help->on_click([encrypt, scene]() {
    Hint* hint = Hint::instance();
    hint->set_short_hint(encrypt->get_long_description(scene->get_one()->get_name()));
    hint->move(main_window->geometry().x(), main_window->geometry().y());
    hint->show();
  });

  Image* wheel_down = new Image("resource/wheel_down.png");
  wheel_down->set_border(false);
  wheel_down->setPos(0, 435);
  scene->addItem(wheel_down);

  Button* backward = new Button("Назад");
  backward->setPos(wheel_down->boundingRect().width() + 5, 440);
  backward->on_click([scene]() {
    scene->before_one();
  });
  scene->addItem(backward);

  Image* wheel_up = new Image("resource/wheel_up.png");
  wheel_up->set_border(false);
  wheel_up->setPos(500, 435);
  scene->addItem(wheel_up);

  Button* next = new Button("Вперед");
  next->setPos(wheel_up->boundingRect().width() + 500 + 5, 440);
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
	  scene->set_input(url->get_value());
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
  
  for (auto& it : encrypt->get_bindings()) {
    recipe::Ingredient first =  encrypt->get_ingredient(it.first);
    recipe::Ingredient second =  encrypt->get_ingredient(it.second);
    assert(first.get_type() == second.get_type()); //shit happens
    switch (first.get_type()) {
      case recipe::Ingredient::URL:
	Url::find(first.get_name())->on_change([first, second]() {
	  QString path =  Url::find(first.get_name())->get_value().toString(); //get first
	  Url::find(second.get_name())->set_value(QUrl::fromLocalFile(path + ".dec")); //set second
	});
	break;
      case recipe::Ingredient::BOOL:
	break;
      case recipe::Ingredient::STRING:
	break;
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


