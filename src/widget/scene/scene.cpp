#include "scene.hpp"

#include <QFileSystemModel>
#include <QTextEdit>
#include <QTreeView>


using namespace widget;

Scene::Scene() : QGraphicsScene(nullptr) {
  ok = new Button("OK");
  ok->setPos(0, 0);
  addItem(ok);
  cancel = new Button("Cancel");
  cancel->setPos(40, 0);
  addItem(cancel);
}

Scene* Scene::on_ok(const Item::ClickCallback& callback) {
  ok->on_click(callback);
  return this;
}

Scene* Scene::on_cancel(const Item::ClickCallback& callback) {
  cancel->on_click(callback);
  return this;
}


PasswordScene::PasswordScene() {
  input = addWidget(new QTextEdit());
  input->setPos(0, 20);
}


FilesystemScene::FilesystemScene() {
  //create widget
  QTreeView* tree = new QTreeView();
  QFileSystemModel* model = new QFileSystemModel();
  model->setRootPath(QDir::currentPath());
  tree->setModel(model);
  //add widget
  input = addWidget(tree);
  input->setPos(0, 20);
}
