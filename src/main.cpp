#include <QApplication>
#include <QHBoxLayout>

#include "element/encrypt_element.hpp"
#include "element/decrypt_element.hpp"

#include "function/encrypt_function.hpp"
#include "function/decrypt_function.hpp"

#include "view/image_view.hpp"
#include "view/text_view.hpp"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  element::Encrypt* encrypt = new element::Encrypt();
  encrypt->on_action([](const QString& file, const QString& password,
			       const std::map<QString, bool>& options) {
    //decrypt file and remove if needed
    function::encrypt(file, file + ".dec", password);
    if (options.at("remove"))
      QFile::remove(file);
  });
  element::Decrypt* decrypt = new element::Decrypt();
  decrypt->on_action([](const QString& file, const QString& password,
		        const std::map<QString, bool>& options) {
    //get original file name
    QString original = file;
    original = original.remove(".dec");
    //decrypt file and show if needed 
    function::decrypt(file, original, password);
    if (options.at("show") && original.contains(".txt")) {
      view::Text* text = new view::Text(original);
      text->show();
    } else if (options.at("show") && (original.contains(".png")  || original.contains(".jpg"))) {
      view::Image* image = new view::Image(original);
      image->show();
    }
  });
  
  QHBoxLayout* layout = new QHBoxLayout();
  layout->addWidget(encrypt);
  layout->addWidget(decrypt);
  
  QWidget* main_window = new QWidget();
  main_window->setLayout(layout);
  main_window->show();

  return app.exec();
}
