#ifndef __SCENE_H
#define __SCENE_H

#include <QGraphicsProxyWidget>
#include <QGraphicsScene>

#include "ingredient/ingredient.hpp"

namespace widget {
  class Scene : public QGraphicsScene { Q_OBJECT
    typedef std::function<void(void)> WheelCallback;
    typedef std::vector<WheelCallback> WheelCallbacks;
  public:
    Scene();
    Scene* on_finish(const Item::ClickCallback& callback);
    Scene* on_cancel(const Item::ClickCallback& callback);
    Scene* on_mouse_right(const Item::ClickCallback& callback);
    Scene* on_wheel_up(const WheelCallback& callback);
    Scene* on_wheel_down(const WheelCallback& callback);
  private:
    Item::ClickCallbacks mouse_right_callbacks;
    WheelCallbacks wheel_up_callbacks;
    WheelCallbacks wheel_down_callbacks;
  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
    void wheelEvent(QGraphicsSceneWheelEvent* e) override;
  protected:
    Button* finish;
    Button* cancel;
    QGraphicsProxyWidget* input;
  };

  class StringScene : public Scene { Q_OBJECT
  public:
    StringScene();
    QString get_input();
    void set_input(const QString& str);
  };

  class UrlScene : public Scene { Q_OBJECT
  public:
    UrlScene();
    UrlScene* on_new_file(const Item::ClickCallback& callback);
    QUrl get_input();
    void set_input(const QUrl& url);
  private:
    QWidget* create_tree();
  private:
    QUrl url;
    Button* new_file;
  };

  class OneItemScene : public Scene {
    typedef std::vector<Item*> Items;
    typedef std::function<void()> ChangeCallback;
    typedef std::vector<ChangeCallback> ChangeCallbacks;
  public:
    OneItemScene* add_item(Item* item);
    OneItemScene* before_one();
    OneItemScene* after_one();
    Item* get_one();
    OneItemScene* one_change(const ChangeCallback& callback);
  private:
    void fire_change();
  private:
    Item* one = nullptr;
    Items items; 
    ChangeCallbacks change_callbacks;
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
