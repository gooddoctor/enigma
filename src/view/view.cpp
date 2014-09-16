#include <QFileSystemModel>
#include <QTextEdit>
#include <QTreeView>

#include "view.hpp"

using namespace view;

Scene* Scene::add_ingredient(Bool* ingredient) {
  addItem(ingredient);
  return this;
}

Scene* Scene::add_ingredient(String* ingredient) {
  addItem(ingredient);
  return this;
}

Scene* Scene::add_ingredient(Url* ingredient) {
  addItem(ingredient);
  return this;
}

Bool* Scene::find_bool(const QString& name) {
  return nullptr;
}

String* Scene::find_string(const QString& name) {
  return nullptr;
}

Url* Scene::find_url(const QString& name) {
  return nullptr;
}


PasswordScene::PasswordScene() {
  input = addWidget(new QTextEdit());
  input->setPos(0, 0);
}


FilesystemScene::FilesystemScene() {
  QTreeView* tree = new QTreeView();
  QFileSystemModel* model = new QFileSystemModel();
  model->setRootPath(QDir::currentPath());
  tree->setModel(model);
  connect(tree, SIGNAL(doubleClicked(const QModelIndex&)), 
	  this, SLOT(double_click_handler(const QModelIndex&)));
  input = addWidget(tree);
  input->setPos(0, 0);
}

void FilesystemScene::double_click_handler(const QModelIndex& index) {
  QFileSystemModel* model = (QFileSystemModel*)((QTreeView*)input->widget())->model();
}

  
