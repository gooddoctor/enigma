#include <QPainter>
#include <QTimeLine>

#include "rotation.hpp"

using namespace widget;

QImage to_rotated(const QImage& image, int angle, Qt::Axis axis) {
  QTransform transform;
  transform.rotate(angle, axis);
  return image.transformed(transform);
}

Rotation::Rotation(const QImage& from, const QImage& to, QWidget* parent) : QWidget(parent) {
  //setting pixmap
  this->from = from;
  this->to = to;
  //setting timeline
  QTimeLine* timeline = new QTimeLine(800, this);
  connect(timeline, SIGNAL(valueChanged(qreal)), this, SLOT(tick(qreal)));
  connect(timeline, SIGNAL(finished()), this, SIGNAL(finish()));
  timeline->start();
}

void Rotation::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  if (std::abs(degree) < 90)
    painter.drawImage(QPointF(0, 0), to_rotated(from, degree, Qt::YAxis));
  else
    painter.drawImage(QPointF(0, 0), to_rotated(to, degree, Qt::YAxis));
}


LeftRotation::LeftRotation(const QPixmap& from, const QPixmap& to, QWidget* parent) 
	    : Rotation(from.toImage(), to_rotated(to.toImage(), 180, Qt::YAxis), parent) { }

void LeftRotation::tick(qreal ticker) {
  degree = 180 * ticker;
  update();
}


RightRotation::RightRotation(const QPixmap& from, const QPixmap& to, QWidget* parent) 
	     : Rotation(from.toImage(), to_rotated(to.toImage(), -180, Qt::YAxis), parent) { }

void RightRotation::tick(qreal ticker) {
  degree = -180 * ticker;
  update();
}


