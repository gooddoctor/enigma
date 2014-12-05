#include "view.hpp"

#include <QLabel>
#include <QScrollArea>
#include <QSlider>

namespace view {
  class Image : public View { Q_OBJECT
  public:
    Image(const QString& file_path, QWidget* parent = 0);
  public slots:
    void zoom(int x);
  private:
    QImage image;
    QLabel* label;
    QScrollArea* scroll;
    QSlider* slider;
  };
}
