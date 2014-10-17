#include "scene.hpp"

#include <QFileSystemModel>
#include <QTextEdit>
#include <QTreeView>

using namespace widget;

Scene::Scene() : QGraphicsScene(nullptr) {
  finish = new Button("Завершить");
  finish->setPos(0, 5);
  addItem(finish);
  cancel = new Button("Отменить");
  cancel->setPos(finish->boundingRect().width() + 5, 5);
  addItem(cancel);
}

Scene* Scene::on_finish(const Item::ClickCallback& callback) {
  finish->on_click(callback);
  return this;
}

Scene* Scene::on_cancel(const Item::ClickCallback& callback) {
  cancel->on_click(callback);
  return this;
}


StringScene::StringScene() {
  QTextEdit* text = new QTextEdit();
  text->resize(640, 480 - finish->boundingRect().height() - 10 - 5);
  input = addWidget(text);
  input->setPos(0, finish->boundingRect().height() + 10);
}

QString StringScene::get_input() {
  return ((QTextEdit*)input->widget())->toPlainText();
}


UrlScene::UrlScene() {
  new_file = new Button("Новый файл");
  new_file->setPos(640 - new_file->boundingRect().width() - 5, 5);
  addItem(new_file);
  //create widget
  QTreeView* tree = new QTreeView();
  tree->resize(640, 480 - finish->boundingRect().height() - 10 - 5);
  QFileSystemModel* model = new QFileSystemModel();
  model->setRootPath(QDir::currentPath());
  tree->setModel(model);
  tree->hideColumn(1);
  tree->hideColumn(2);
  tree->hideColumn(3);  
  //add widget
  input = addWidget(tree);
  input->setPos(0, finish->boundingRect().height() + 10);
}

UrlScene* UrlScene::on_new_file(const Item::ClickCallback& callback) {
  new_file->on_click(callback);
  return this;
}

QUrl UrlScene::get_input() {
  QFileSystemModel* model = (QFileSystemModel*)((QTreeView*)input->widget())->model();
  return model->filePath(((QTreeView*)input->widget())->currentIndex());
}


OneItemScene* OneItemScene::add_item(Item* item) {
  QSizeF scene_size = sceneRect().size();
  QSizeF item_size = item->boundingRect().size();
  item->setPos((scene_size.width() - item_size.width()) / 2,
	       (scene_size.height() - item_size.height()) / 2); //middle
  //make the ONE!
  if (one == nullptr)
    one = item;
  else
    item->hide();
  //save it and add it to scene
  items.push_back(item);
  Scene::addItem(item);
  //thats all
  return this;
}

OneItemScene* OneItemScene::before_one() {
  auto it = std::find(items.begin(), items.end(), one);
  if (it != items.begin()) {
    one->hide();
    one = *(--it);
    one->show();
  }
  return this;
}

OneItemScene* OneItemScene::after_one() {
  auto it = std::find(items.begin(), items.end(), one); 
  it++; //item after one
  if (it != items.end()) {
    one->hide();
    one = *it;
    one->show();
  }
  return this;
}
  
