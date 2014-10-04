#include "widget.hpp"

using namespace widget;

StackWidget::StackWidget(QWidget* parent) : QStackedWidget(parent) { }

StackWidget* StackWidget::push(Scene* scene) {
  QGraphicsView* current = new QGraphicsView(scene);
  addWidget(current);
  setCurrentWidget(current);
  //setting callback
  scene->on_cancel(std::bind(&StackWidget::pop, this));
  return this;
}

StackWidget* StackWidget::pop() {
  if (currentIndex() != 0)
    removeWidget((QGraphicsView*)currentWidget());
  return this;
}


RotationStackWidget::RotationStackWidget(QWidget* parent) : StackWidget(parent) { }

RotationStackWidget* RotationStackWidget::push(Scene* scene) {
  //push it
  StackWidget::push(scene);
  //show rotation
  QGraphicsView* current = (QGraphicsView*)widget(currentIndex());
  QGraphicsView* previous = (QGraphicsView*)widget(currentIndex() - 1);
  if (previous != nullptr)
    show_rotation(new RightRotation(to_pixmap(previous), to_pixmap(current)));
  return this;
}

RotationStackWidget* RotationStackWidget::pop() {
  //save current widget
  QGraphicsView* current = (QGraphicsView*)currentWidget();
  //pop it
  StackWidget::pop();
  //show rotation
  QGraphicsView* previous = (QGraphicsView*)currentWidget();
  if (previous != nullptr)
    show_rotation(new LeftRotation(to_pixmap(current), to_pixmap(previous)));
  return this;
}

void RotationStackWidget::show_rotation(Rotation* rotation) {
  connect(rotation, SIGNAL(finish()), this, SLOT(hide_rotation()));
  addWidget(rotation);
  setCurrentWidget(rotation);
}

void RotationStackWidget::hide_rotation() {
  QWidget* widget = currentWidget();
  removeWidget(currentWidget());
  delete widget;
}


