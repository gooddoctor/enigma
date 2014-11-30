#ifndef __ELEMENT_H
#define __ELEMENT_H

#include <QDragEnterEvent>
#include <QPainter>
#include <QWidget>

namespace element {
  class Element : public QWidget { Q_OBJECT
    typedef std::function<void(const QString&, const QString&, 
			       const std::map<QString, bool>&)> ActionCallback;
    typedef std::vector<ActionCallback> ActionCallbacks;
  public:
    Element(const QImage& image, QWidget* parent = 0);
    Element* on_action(const ActionCallback& callback);
  private:
    ActionCallbacks action_callbacks;
    QImage image;
  protected:
    virtual void fire_action(const QString& file, const QString& password, 
			     const std::map<QString, bool>& options);
    virtual void select(const QString& file) = 0;
    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void paintEvent(QPaintEvent* e) override;
    virtual void dragEnterEvent(QDragEnterEvent* e) override;
    virtual void dropEvent(QDropEvent* e) override;
  };
}

#endif
