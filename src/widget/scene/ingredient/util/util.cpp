#include "util.hpp"

using namespace widget;

QPixmap widget::to_grayscale(const QPixmap& original) {
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
