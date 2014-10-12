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
  QTextEdit* text = new QTextEdit();
  text->resize(620, 460);
  input = addWidget(text);
  input->setPos(0, 20);
}

QString StringScene::get_input() {
  return ((QTextEdit*)input->widget())->toPlainText();
}


UrlScene::UrlScene() {
  //create widget
  QTreeView* tree = new QTreeView();
  tree->resize(620, 460); 
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
  
