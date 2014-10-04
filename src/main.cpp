#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>

#include "widget/widget.hpp"

using namespace widget;

RotationStackWidget* main_window;

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  
  Button* btn = new Button("How you doin?");
  btn->on_click([]() {
    qDebug() << "your lipse move but i cant hear what they say";
  });

  String* pswd = new String("Password", "Fish-Sword");
  pswd->on_click([]() {
    FilesystemScene* fs = new FilesystemScene();
    main_window->push(fs);
  });
  pswd->setPos(0, 40);

  Scene* scene = new Scene();
  scene->addItem(pswd);
  
  main_window = new RotationStackWidget();
  main_window->push(scene);
  main_window->show();

  return app.exec();
}


