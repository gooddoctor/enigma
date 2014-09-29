#ifndef __SCENE_H
#define __SCENE_H

#include <QGraphicsProxyWidget>
#include <QGraphicsScene>

#include "ingredient/ingredient.hpp"

namespace widget {
  class Scene : public QGraphicsScene { Q_OBJECT
  public:
    Scene();
    Scene* on_ok(const Item::ClickCallback& callback);
    Scene* on_cancel(const Item::ClickCallback& callback);
  private:
    Button* ok;
    Button* cancel;
  };

  class PasswordScene : public Scene { Q_OBJECT
  public:
    PasswordScene();
  private:
    QGraphicsProxyWidget* input;
  };

  class FilesystemScene : public Scene { Q_OBJECT
  public:
    FilesystemScene();
  private:
    QGraphicsProxyWidget* input;
  };
}

#endif
