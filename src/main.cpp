#include <QDebug>

#include <QApplication>
#include <QGraphicsView>
#include <QMainWindow>

#include "recipe/crypto.hpp"
#include "view/view.hpp"

using namespace recipe;
using namespace view;


int main(int argc, char** argv) {
Recipe* encrypt = new Encrypt;
  encrypt->add_ingredient(Ingredient("input", QUrl("/home/gooddocteur/projects/enigma/"
   						   "lab/some_body_to_know.txt")));
  encrypt->add_ingredient(Ingredient("output", QUrl("/home/gooddocteur/projects/enigma/"
 						    "lab/some_body_to_know.dec"))); 
  encrypt->add_ingredient(Ingredient("password", QString("fish-sword")));
  encrypt->add_ingredient(Ingredient("iv", QString("fish-sword")));
  encrypt->add_ingredient(Ingredient("save", true));

  QApplication app(argc, argv);

  QGraphicsScene* scene = new QGraphicsScene(main_window);

  int pos = 10;

  for (auto& it : encrypt->get_ingredients()) {
    switch (it.second.get_type()) {
      case recipe::Ingredient::BOOL: {
	Bool* boolean = new Bool(it.first);
	boolean->setPos(pos, 0);
	scene->addItem(boolean);
	break;
      }
      case recipe::Ingredient::STRING: {
	String* str = new String(it.second.get_string_value());
	str->on_enter([str]() {
	  PasswordScene* scene = new PasswordScene();
	  scene->on_back([]() {
	    main_window->pop();
	  });
	  scene->on_ok([str, scene]() {
	    str->set_text(scene->get_password());
	    main_window->pop();
	  });
	  main_window->push(scene);
	});
	str->setPos(pos, 0);
	scene->addItem(str);
	break;
      }
      case recipe::Ingredient::URL: {
	URL* url = new URL(it.second.get_url_value().path());
	url->on_browse([url]() {
	  FilesystemScene* scene = new FilesystemScene();
	  scene->on_back([]() {
	    main_window->pop();
	  });
	  scene->on_select([url](const QString& path) {
	    url->set_path(path);
	    main_window->pop();
	  });
	  main_window->push(scene);
	});
	url->setPos(pos, 0);	
	scene->addItem(url);
	break;
      }
    }
    pos += 600;
  }

  Image* finish = new Image("view/resource/finish.png");
  finish->on_click([encrypt]() {
    // for (auto& it : encrypt->get_ingredients()) {
    //   switch (it.second.get_type()) {
    // 	case recipe::Ingredient::BOOL:
    // 	  encrypt->add_ingredient(Ingredient(it.first, 
    // 				  ((Bool*)main_window->find(it.first)).value()));
    // 	  break;
    // 	case recipe::Ingredient::STRING:
    // 	  encrypt->add_ingredient(Ingredient(it.first,
    // 				  ((String*)main_window->find(it.first)).value()));
    // 	  break;
    // 	case recipe::Ingredient::URL:
    // 	  encrypt->add_ingredient(Ingredient(it.first, 
    // 				  ((URL*)main_window->find(it.first)).value()));
    // 	  break;
    //   }
    // }
  });
  finish->setPos(pos, 0);
  scene->addItem(finish);

  pos += 600;

  scene->setSceneRect(0, 0, pos, 480);

  main_window = new Stack();
  main_window->push(scene);
  main_window->show();
 
  return app.exec();
}
