#include <2DGameSDK/Game.h>
#include <2DGameSDK/GameOptions.h>
#include <2DGameSDK/event/observable/Observable.h>
#include <2DGameSDK/event/observer/MethodObserver.h>
#include <2DGameSDK/event/observer/Observer.h>
// #include <2DGameSDK/ResourceCache.h>
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
class Emitter : Observable<TData> {
protected:
  TData* triggered(bool* trigger) {
    trigger = mData != nullptr;
    return mData;
  }

private:
  TData* mData = nullptr;
};

// template class Observer<MyClass>;
// template class MethodObserver<MyClass, ClassWithMethod>;

int testObserver2() {
  auto ctrl = ClassWithMethod();
  auto observer = MethodObserver<MyClass, ClassWithMethod>(&ctrl, &ClassWithMethod::Method);
  observer.Callback(new MyClass());
  // auto observable = Observable<MyClass>();
  // auto observable = Observable<MyClass>();
  // observable.Subscribe(&observer);

  // auto c = MyClass();
  // observable.Emit(&c);
}

int main() {
  std::cout << "Hello Compiler" << std::endl;
  game::GameOptions options{
      "My Game", sf::Vector2i(800, 600), 50};

  testObserver2();

  game::Game app(options);
  app.Run();

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