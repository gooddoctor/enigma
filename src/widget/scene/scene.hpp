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

  class OneItemScene : public Scene {
    typedef std::vector<Item*> Items;
  public:
    OneItemScene* add_item(Item* item);
    OneItemScene* before_one();
    OneItemScene* after_one();
  private:
    Item* one = nullptr;
    Items items; 
  };
  
  class OneIngredientScene : public OneItemScene {
  public:
    template <typename T>
    OneIngredientScene* add_ingredient(Ingredient<T>* ingredient) {
      add_item(ingredient);
      return this;
    }
  };

}

#endif
