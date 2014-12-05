#include <QVBoxLayout>

#include "image_view.hpp"

using namespace view;

Image::Image(const QString& file_path, QWidget* parent) : View(file_path, parent) {
  image = QImage(file_path);
  
  label = new QLabel();
  label->setPixmap(QPixmap::fromImage(image));
  label->setAlignment(Qt::AlignCenter);

  scroll = new QScrollArea();
  scroll->setWidget(label);
  scroll->setWidgetResizable(true);

  slider = new QSlider(Qt::Horizontal);
  slider->setValue(0);
  QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));

  QVBoxLayout* layout = new QVBoxLayout;
  layout->setContentsMargins(QMargins(0, 0, 0, 0));
  layout->addWidget(scroll);
  layout->addWidget(slider);
  setLayout(layout);
}

void Image::zoom(int x) {
  QImage scaled = image.scaled((image.width() * x / 100) + image.width(),
			       (image.height() * x / 100) + image.height());
  label->setPixmap(QPixmap::fromImage(scaled));
  label->resize(scaled.width(), scaled.height());
}
