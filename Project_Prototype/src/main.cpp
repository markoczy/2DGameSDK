#include <2DGameSDK/Core.h>
#include <2DGameSDK/Event.h>
#include <2DGameSDK/Scene.h>
#include <2DGameSDK/World.h>

#include <chrono>
#include <iostream>
#include <thread>

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

class MyEntity : public Entity {
public:
  MyEntity() : Entity(1) {}

  void Tick() {
    cout << "MyEntity ticks.." << endl;
  }

  void Render(sf::RenderTarget* target) {
    cout << "MyEntity renders.." << endl;
  }
};

int testEntity() {
  auto ent = new MyEntity();
  ent->Tick();
  ent->Render(nullptr);
}

int testEntity2() {
  cout << "Start Testentity 29" << endl;
  auto cache = TextureCache();
  auto tex = AssetManager::GetTexture("res/textures/testtile/testtile_0.png");
  auto tex2 = AssetManager::GetTexture("res/textures/sample.png");
  auto ent = new SpriteTransformableEntity(1, tex);
  auto ent2 = new SpriteTransformableEntity(1, tex2);

  auto scene = SceneGraph();
  auto parent = scene.GetRoot()->AddChild(ent);
  auto child = parent->AddChild(ent2);

  sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
  auto view = window.getView();
  // view.zoom(0.1);
  // view.setSize(200, 200);
  // window.setView(view);

  sf::CircleShape shape(100.f);
  shape.setTexture(tex);
  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();

    ent->Render(&window);
    ent2->Render(&window);
    ent->GetTransformable()->move(1, 1);
    ent2->GetTransformable()->rotate(5.0);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    // window.draw(shape);
    window.display();
  }

  return 0;
}

int testTiles() {
  Tile t;
  t.Id = 2;
  cout << "Tile ID:" << t.Id << endl;
  return 0;
}

int main() {
  std::cout << "Hello Compiler" << std::endl;

  // testEvents();
  // testEntity();
  testEntity2();
  testTiles();

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