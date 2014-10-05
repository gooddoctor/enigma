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
  protected:
    QGraphicsProxyWidget* input;
  };

  class StringScene : public Scene { Q_OBJECT
  public:
    StringScene();
    QString get_input();
  };

  class UrlScene : public Scene { Q_OBJECT
  public:
    UrlScene();
    QUrl get_input();
  };
}

#endif
