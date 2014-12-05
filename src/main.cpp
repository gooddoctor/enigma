#include <QApplication>

#include "function/encrypt_function.hpp"
#include "function/decrypt_function.hpp"
#include "view/image_view.hpp"

using namespace function;
using namespace view;

int main(int argc, char** argv) {
  // encrypt("test.txt", "test.dec", "hello how you doin");
  // decrypt("test.dec", "test.dec.txt", "hello how you doin");

  QApplication app(argc, argv);
  Image* image = new Image("test.jpg");
  image->show();
  return app.exec();
}
