#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>

#include "widget/scene/ingredient/item/item.hpp"

using namespace widget;

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  
  Button* btn = new Button("How you doin?");
  btn->on_click([]() {
    qDebug() << "your lipse move but i cant hear what they say";
  });

  QGraphicsScene* scene = new QGraphicsScene();
  scene->addItem(btn);
  
  QMainWindow* main_window = new QMainWindow();
  main_window->setCentralWidget(new QGraphicsView(scene));
  main_window->show();

  return app.exec();
}


