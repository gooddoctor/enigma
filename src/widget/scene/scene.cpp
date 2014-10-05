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


StringScene::StringScene() {
  input = addWidget(new QTextEdit());
  input->setPos(0, 20);
}

QString StringScene::get_input() {
  return ((QTextEdit*)input->widget())->toPlainText();
}


UrlScene::UrlScene() {
  //create widget
  QTreeView* tree = new QTreeView();
  QFileSystemModel* model = new QFileSystemModel();
  model->setRootPath(QDir::currentPath());
  tree->setModel(model);
  //add widget
  input = addWidget(tree);
  input->setPos(0, 20);
}

QUrl UrlScene::get_input() {
  QFileSystemModel* model = (QFileSystemModel*)((QTreeView*)input->widget())->model();
  return model->filePath(((QTreeView*)input->widget())->currentIndex());
}
