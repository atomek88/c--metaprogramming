#include "factory_recursion.h"
#include <iostream>
#include <memory>
using namespace std;
using namespace cspp51045;

struct Scrollbar {
  virtual size_t position() = 0;
};

struct Button {
  virtual void press() = 0;
};

struct QtScrollbar : public Scrollbar {
  size_t position() { return 0; }
};

struct QtButton : public Button {
  void press() { cout << "QtButton pressed" << endl; }
};

struct WindowsScrollbar : public Scrollbar {
  size_t position() { return 0; }
};

struct WindowsButton : public Button {
  void press() { cout << "WindowsButton pressed" << endl; }
};

typedef abstract_factory<Scrollbar, Button> AbstractWidgetFactory;
typedef 
  concrete_factory<AbstractWidgetFactory, QtScrollbar, QtButton>
  QtWidgetFactory;

typedef 
  concrete_factory<AbstractWidgetFactory, WindowsScrollbar, WindowsButton>
  WindowsWidgetFactory;

int main()
{
  unique_ptr<AbstractWidgetFactory> factory(new QtWidgetFactory);
  auto button(factory->create<Button>());
  button->press();
  return 0;
}
