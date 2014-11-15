#include "scene.hpp"

#include <QFileSystemModel>
#include <QGraphicsSceneMouseEvent>
#include <QStandardPaths>
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

Scene* Scene::on_mouse_right(const Item::ClickCallback& callback) {
  mouse_right_callbacks.push_back(callback);
  return this;
}

Scene* Scene::on_wheel_up(const WheelCallback& callback) {
  wheel_up_callbacks.push_back(callback);
  return this;
}

Scene* Scene::on_wheel_down(const WheelCallback& callback) {
  wheel_down_callbacks.push_back(callback);
  return this;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* e) {
  QGraphicsScene::mousePressEvent(e);
  if (e->button() == Qt::RightButton)
    for (auto it : mouse_right_callbacks) it();
}

void Scene::wheelEvent(QGraphicsSceneWheelEvent* e) {
  if (e->delta() > 0)
    for (auto it : wheel_up_callbacks) it();
  else
    for (auto it : wheel_down_callbacks) it();
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

void StringScene::set_input(const QString& str) {
  //under construction
}

UrlScene::UrlScene() {
  new_file = new Button("Новый файл");
  new_file->setPos(640 - new_file->boundingRect().width() - 5, 5);
  addItem(new_file);
  //add widget
  input = addWidget(create_tree());
  input->setPos(0, finish->boundingRect().height() + 10);
}

UrlScene* UrlScene::on_new_file(const Item::ClickCallback& callback) {
  new_file->on_click(callback);
  return this;
}

QUrl UrlScene::get_input() {
  QTreeView* widget = (QTreeView*)input->widget();
  QFileSystemModel* model = (QFileSystemModel*)widget->model();
  if (QFileInfo(model->filePath(widget->currentIndex())).isFile())
    return model->filePath(((QTreeView*)input->widget())->currentIndex());
  else
     return url;
}

void UrlScene::set_input(const QUrl& url) {
  this->url = url;
  //create url path if needed
  if (!QFileInfo(url.path()).exists()) {
    QFile file(url.path());
    file.open(QIODevice::ReadWrite);
    file.close();
  }
  //create and config widget
  QTreeView* tree = (QTreeView*)input->widget();
  QFileSystemModel* model = (QFileSystemModel*)tree->model();
  QDir url_dir(url.path());
  do {
    tree->expand(model->index(url_dir.absolutePath()));
  } while (url_dir.cdUp());
  tree->selectionModel()->setCurrentIndex(model->index(url.path()), 
					  QItemSelectionModel::ClearAndSelect);
}

QWidget* UrlScene::create_tree() {
  //create model
  QFileSystemModel* model = new QFileSystemModel();
  model->setRootPath(QDir::currentPath());
  //create and configure view
  QTreeView* tree = new QTreeView();
  tree->setFont(QFont("Monospace", 16, QFont::Bold));
  tree->setModel(model);
  tree->hideColumn(1);
  tree->hideColumn(2);
  tree->hideColumn(3);  
  tree->resize(640, 480 - finish->boundingRect().height() - 10 - 5);
  //thats all
  return tree;
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
    //notify about it
    fire_change();
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
    //notify about it
    fire_change();
  }
  return this;
}

Item* OneItemScene::get_one() {
  return one;
}

OneItemScene* OneItemScene::one_change(const ChangeCallback& callback) {
  change_callbacks.push_back(callback);
  return this;
}

void OneItemScene::fire_change() {
  for (const auto& it : change_callbacks) it();
}
