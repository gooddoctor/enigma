#include <QGraphicsOpacityEffect>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPropertyAnimation>

#include "hint.hpp"

using namespace widget;

void Hint::set_hint(const QString& hint) {
  hint_item->setHtml(hint);
}

Hint::Hint() : QWidget(nullptr, Qt::FramelessWindowHint) {
  //create timer
  timer = new QTimer(this);
  timer->setSingleShot(true); 
  connect(timer, SIGNAL(timeout()), this, SLOT(hide()));
  //create background
  background = QPixmap("widget/hint/resource/background.png");
  //create item  
  hint_item = new QGraphicsTextItem();
  //create scene
  QGraphicsScene* scene = new QGraphicsScene();
  scene->setBackgroundBrush(QBrush(QColor(105, 210, 231), Qt::SolidPattern));
  scene->addItem(hint_item);
  //create view
  QGraphicsView* view = new QGraphicsView(scene, this);
  view->setStyleSheet("background: transparent");
  view->setAttribute(Qt::WA_TranslucentBackground, true);
  view->setGeometry(6, 6, background.size().width() - 10, background.size().height() - 10);
  //configure widget
  setGraphicsEffect(new QGraphicsOpacityEffect(this));
  setAttribute(Qt::WA_TranslucentBackground, true);
  resize(background.size());
}

void Hint::mousePressEvent(QMouseEvent* event) {
  QWidget::mousePressEvent(event);
  //thats our logic
  hide();
}

void Hint::paintEvent(QPaintEvent* event) {
  QWidget::paintEvent(event);
    //draw background
  QPainter painter(this);
  painter.drawPixmap(0, 0, background);
}

void Hint::showEvent(QShowEvent* event) {
  QWidget::showEvent(event);
  //set effect
  QGraphicsOpacityEffect* effect = (QGraphicsOpacityEffect*)graphicsEffect();
  QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity");
  animation->setDuration(600);
  animation->setStartValue(0.6);
  animation->setEndValue(1.0);
  animation->start(QAbstractAnimation::DeleteWhenStopped);
  //set timer
  timer->start(3000);
}
