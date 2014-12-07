#include <QFileDialog>
#include <QMimeData>

#include "element.hpp"

using namespace element;

Element::Element(const QImage& image, QWidget* parent) : QWidget(parent) {
  this->image = image;
  setAcceptDrops(true);
}

QSize Element::sizeHint() const {
  return image.size();
}

Element* Element::on_action(const ActionCallback& callback) {
  action_callbacks.push_back(callback);
  return this;
}

void Element::fire_action(const QString& file, const QString& password, 
			  const std::map<QString, bool>& options) {
  for (const auto& it : action_callbacks)
    it(file, password, options);
}

void Element::mousePressEvent(QMouseEvent* e) {
  QString file = QFileDialog::getOpenFileName();
  if (!file.isEmpty())
    select(file);
}

void Element::paintEvent(QPaintEvent* e) {
  QWidget::paintEvent(e);
  QPainter painter(this);
  painter.drawImage(0, 0, image.scaled(width(), height()));
}

void Element::dragEnterEvent(QDragEnterEvent* e) {
  QWidget::dragEnterEvent(e);
  if (e->mimeData()->hasFormat("text/uri-list") && e->mimeData()->urls().size() == 1)
    e->acceptProposedAction();
}

void Element::dropEvent(QDropEvent* e) {
  QWidget::dropEvent(e);
  QList<QUrl> list = e->mimeData()->urls();
  for (QUrl url : list)
    select(url.path());
}  


