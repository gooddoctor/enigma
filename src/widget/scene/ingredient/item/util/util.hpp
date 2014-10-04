#ifndef __UTIL_H
#define __UTIL_H

#include <QGraphicsView>
#include <QPixmap>

namespace widget {
  QPixmap to_grayscale(const QPixmap& original);
  QPixmap to_pixmap(QGraphicsView* view);
}

#endif
