#include <2DGameSDK/Core.h>
#include <2DGameSDK/Event.h>
#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace game;

class MyClass {
public:
  MyClass() {
    cout << "Instance of MyClass created" << endl;
  }
  void MyAction() {
    cout << "MyAction called" << endl;
  }
  int MyVal = 42;
};

class ClassWithMethod {
public:
  void Method(MyClass* c) {
    std::cout << "Action inside class closure" << std::endl;
    c->MyAction();
  }
};

template <class TData>
class Emitter : public Observable<TData> {
public:
  void Emit(TData* data) {
    // TODO destroy old??
    mData = data;
  }

protected:
  TData* triggered(bool* trigger) {
    cout << "Called triggered of Emitter" << endl;
    // bool tr = mData != nullptr;
    *trigger = mData != nullptr;
    auto data = mData;
    mData = nullptr;
    return data;
  }

private:
  TData* mData = nullptr;
};

int testEvents() {
  auto data = new MyClass();
  auto handler = new ClassWithMethod();
  auto observer = new MethodObserver<MyClass, ClassWithMethod>(handler, &ClassWithMethod::Method);

  auto emitter = new Emitter<MyClass>();
  emitter->Subscribe(observer);

  auto ctrl = EventController();
  ctrl.AddEvent(emitter);

  cout << "*** Emitting data" << endl;
  emitter->Emit(data);

  cout << "*** Updating Controller" << endl;
  ctrl.Tick();

  cout << "*** Updating Controller" << endl;
  ctrl.Tick();

  return 0;
}

int main() {
  std::cout << "Hello Compiler" << std::endl;

  testEvents();

  // game::GameOptions options{
  //     "My Game", sf::Vector2i(800, 600), 50};
  // game::Game app(options);
  // app.Run();

  // sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  // sf::CircleShape shape(100.f);
  // shape.setFillColor(sf::Color::Blue);

  // auto cache = TextureCache();

  // auto assets = AssetManager();
  // auto tex = cache.Get("res/textures/testtile/testtile_0.png");
  // shape.setTexture(tex);

  // while(window.isOpen()) {
  //   sf::Event event;
  //   while(window.pollEvent(event)) {
  //     if(event.type == sf::Event::Closed)
  //       window.close();
  //   }
  //   window.clear();
  //   window.draw(shape);
  //   window.display();
  // }

  // auto k = cache.Get("res/textures/testtile/testtile_0.png");
  // cache.Clear();
  // std::cout << "End." << std::endl;
  // system("pause");

  return 0;
}