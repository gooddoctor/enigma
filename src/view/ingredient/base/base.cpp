#include "base.hpp"

using namespace view;

static const QColor button_background(105, 210, 231);
static const QFont button_font("Monospace");
static const QFontMetrics button_metrics(button_font);

Button::Button(const QString& text, QGraphicsItem* parent) : QGraphicsItem(parent) {
  setAcceptHoverEvents(true);
  this->text = text;
}

QRectF Button::boundingRect() const {
  return QRectF(0, 0, button_metrics.width(text), button_metrics.height() + 10);
}

void Button::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->setPen(QPen());
  painter->setFont(button_font);
  if (!is_hover)
    painter->fillRect(boundingRect(), button_background);
  else
    painter->fillRect(boundingRect(), QColor(button_background).darker(110));
  painter->drawText(0, button_metrics.height(), text);
}

Button* Button::on_click(const ClickCallback& callback) {
  click_callbacks.push_back(callback);
  return this;
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent*) {
  is_hover = true;
  update();
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
  is_hover = false;
  update();
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent*) {
  for (const auto& it : click_callbacks)
    it();
}


QPixmap view::to_grayscale(const QPixmap& original) {
  QImage image = original.toImage();
  for (int i = 0; i < original.width(); ++i) {
    for (int j = 0; j < original.height(); ++j) {
      QRgb col = image.pixel(i, j);
      if (col == Qt::color0) continue;
      image.setPixel(i, j, qRgb(qGray(col), qGray(col), qGray(col)));
    }
  }
  return QPixmap::fromImage(image);
}


Image::Image(const QString& image, QGraphicsItem* parent) : QGraphicsItem(parent) {
  this->image = QPixmap(image);
}

QRectF Image::boundingRect() const {
  return QRectF(0, 0, image.width(), image.height());
}

void Image::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->drawPixmap(0, 0, image);
  painter->drawRect(boundingRect());
}

Image* Image::on_click(const ClickCallback& callback) {
  click_callbacks.push_back(callback);
  return this;
}

void Image::mousePressEvent(QGraphicsSceneMouseEvent*) {
  for (const auto& it : click_callbacks)
    it();
}

/********************************************************************************/
RotationEffect::RotationEffect(const QPixmap& from, const QPixmap& to, QWidget* parent)
	      : QWidget(parent) {
  //setting pixmap
  this->from = from;
  this->to = to;
  //setting timeline
  QTimeLine* timeline = new QTimeLine(800, this);
  connect(timeline, SIGNAL(valueChanged(qreal)), this, SLOT(tick(qreal)));
  connect(timeline, SIGNAL(finished()), this, SIGNAL(finish()));
  timeline->start();
}

void RotationEffect::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  if (std::abs(degree) < 90)
    painter.drawPixmap(QPointF(0, 0), to_rotated(from, degree, Qt::YAxis));
  else
    painter.drawPixmap(QPointF(0, 0), to_rotated(to, degree, Qt::YAxis));
}


LeftRotationEffect::LeftRotationEffect(const QPixmap& from, const QPixmap& to, QWidget* parent) 
		  : RotationEffect(from, to_rotated(to, 180, Qt::YAxis), parent) { }

void LeftRotationEffect::tick(qreal ticker) {
  degree = 180 * ticker;
  update();
}


RightRotationEffect::RightRotationEffect(const QPixmap& from, const QPixmap& to, QWidget* parent) 
		   : RotationEffect(from, to_rotated(to, -180, Qt::YAxis), parent) { }

void RightRotationEffect::tick(qreal ticker) {
  degree = -180 * ticker;
  update();
}


Stack::Stack(QWidget* parent) : QStackedWidget(parent) { }

Stack* Stack::push(QGraphicsScene* scene) {
  //add top widget(push actually)
  QGraphicsView* current = new QGraphicsView(scene);
  addWidget(current);
  setCurrentWidget(current);
  //show rotation effect
  QGraphicsView* previous = (QGraphicsView*)widget(currentIndex() - 1);
  if (previous != nullptr)
     show_rotation(new RightRotationEffect(to_pixmap(previous), to_pixmap(current)));
  return this;
}

void Stack::pop() {
  //remove top widget(pop actually)
  QGraphicsView* current = (QGraphicsView*)currentWidget();
  removeWidget(current);
  //show rotation effect
  QGraphicsView* previous = (QGraphicsView*)currentWidget();
  show_rotation(new LeftRotationEffect(to_pixmap(current), to_pixmap(previous)));
  //free it
  delete current;
}

void Stack::show_rotation(RotationEffect* rotation) {
  connect(rotation, SIGNAL(finish()), this, SLOT(hide_rotation()));
  addWidget(rotation);
  setCurrentWidget(rotation);
}

void Stack::hide_rotation() {
  QWidget* widget = currentWidget();
  removeWidget(currentWidget());
  delete widget;
}
/********************************************************************************/



QPixmap view::to_grayscale(const QPixmap& original) {
  QImage image = original.toImage();
  for (int i = 0; i < original.width(); ++i) {
    for (int j = 0; j < original.height(); ++j) {
      QRgb col = image.pixel(i, j);
      if (col == Qt::color0) continue;
      image.setPixel(i, j, qRgb(qGray(col), qGray(col), qGray(col)));
    }
  }
  return QPixmap::fromImage(image);
}

QPixmap view::to_rotated(const QPixmap& original, int angle, Qt::Axis axis) {
  QTransform transform;
  transform.rotate(angle, axis);
  return original.transformed(transform);
}

QPixmap view::to_pixmap(QGraphicsView* view) {
  //create
  QPixmap pixmap(view->width(), view->height());
  pixmap.fill(qRgb(255, 255, 255));
  //render
  QPainter painter(&pixmap);
  view->render(&painter);
  //thats it
  return pixmap;
}
