#ifndef __VIEW_H
#define __VIEW_H

#include <QGraphicsProxyWidget>
#include <QGraphicsScene>

#include "ingredient/ingredient.hpp"

namespace view {
  class Scene : public QGraphicsScene { Q_OBJECT
  public:
    Scene* add_ingredient(Bool* ingredient);
    Scene* add_ingredient(String* ingredient);
    Scene* add_ingredient(Url* url);
    Bool* find_bool(const QString& name);
    String* find_string(const QString& name);
    Url* find_url(const QString& name);
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
  private slots:
    void double_click_handler(const QModelIndex& index);
  private:
    QGraphicsProxyWidget* input;
  };
}

#endif
