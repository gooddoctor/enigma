#include <QDebug>
#include <QApplication>

#include "element/encrypt.hpp"

using namespace element;

int main(int argc, char** argv) {
  std::map<QString, QString> temp = {{"foo", "bar"}, {"foo", "bar"}};
  QApplication app(argc, argv);
  Encrypt decrypt;
  decrypt.on_action([](const QString& file, const QString& password, 
		       const std::map<QString, bool>& options) {
    qDebug() << file << password << options.at("remove");
  });
  decrypt.show();
  return app.exec();
}
