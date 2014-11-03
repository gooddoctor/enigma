#ifndef __WIDGET_H
#define __WIDGET_H

#include <QStackedWidget>

#include "hint/hint.hpp"
#include "rotation/rotation.hpp"
#include "scene/scene.hpp"

namespace widget {
  class StackWidget : public QStackedWidget { Q_OBJECT
  public:
    StackWidget(QWidget* parent = 0);
    virtual StackWidget* push(Scene* scene);
    virtual StackWidget* pop();
  };

  class RotationStackWidget : public StackWidget { Q_OBJECT
  public:
    RotationStackWidget(QWidget* parent = 0);
    RotationStackWidget* push(Scene* scene) override;
    RotationStackWidget* pop() override;
  private:
    void show_rotation(Rotation* rotation);
  private slots:
    void hide_rotation();
  };

}

#endif
