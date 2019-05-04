#include <2DGameSDK/Common.h>
#include <2DGameSDK/Core.h>
#include <2DGameSDK/Event.h>
#include <2DGameSDK/Scene.h>
#include <2DGameSDK/World.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <tuple>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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
  tuple<bool, TData*> triggered() {
    cout << "Called triggered of Emitter" << endl;
    // mData != nullptr,
    // mData};
    auto ret = tuple<bool, TData*>(mData != nullptr, mData);
    mData = nullptr;
    return ret;
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

  void Render(sf::RenderTarget* targe, sf::RenderStates states = sf::RenderStates::Default) {
    cout << "MyEntity renders.." << endl;
  }
};

int testEntity() {
  auto ent = new MyEntity();
  ent->Tick();
  ent->Render(nullptr);
}

int testEntity2() {
  cout << "Start Testentity 30" << endl;
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

    scene.Render(&window);
    // ent->Render(&window);
    // ent2->Render(&window);
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

int testWorldLoader() {
  cout << "Start testWorldLoader 5" << endl;
  sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
  cout << "before create" << endl;
  auto world = GameWorldFactory::CreateGameWorld("res/testmap/tilemap.json", "", "res/testmap/test-2_");
  cout << "after create" << endl;

  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();

    // cout << "before render" << endl;
    world->Render(&window);
    // cout << "after render" << endl;
    // ent->Render(&window);
    // ent2->Render(&window);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    // window.draw(shape);
    window.display();
  }
}

const int PLAYER_TYPE = 200;

class PlayerEntity : public SpriteTransformableEntity {
public:
  PlayerEntity(sf::Texture* texture,
               float speed,
               Observable<EmptyEventData>* up,
               Observable<EmptyEventData>* down,
               Observable<EmptyEventData>* left,
               Observable<EmptyEventData>* right) : SpriteTransformableEntity(PLAYER_TYPE, texture), mSpeed(speed) {
    //
    //
    //
    auto upSubscriber = new MethodObserver<EmptyEventData, PlayerEntity>(this, &PlayerEntity::MoveUp);
    auto downSubscriber = new MethodObserver<EmptyEventData, PlayerEntity>(this, &PlayerEntity::MoveDown);
    auto leftSubscriber = new MethodObserver<EmptyEventData, PlayerEntity>(this, &PlayerEntity::MoveLeft);
    auto rightSubscriber = new MethodObserver<EmptyEventData, PlayerEntity>(this, &PlayerEntity::MoveRight);

    mUpSubscr = up->Subscribe(upSubscriber);
    mDownSubscr = down->Subscribe(downSubscriber);
    mLeftSubscr = left->Subscribe(leftSubscriber);
    mRightSubscr = right->Subscribe(rightSubscriber);
  }

  ~PlayerEntity() {
    mUp->Unsubscribe(mUpSubscr);
  }

  void Tick() {
    if(mDt.x != 0 || mDt.y != 0) {
      GetTransformable()->move(mDt);
      mDt = sf::Vector2f();
    }
  }

  void MoveUp(EmptyEventData* unused) {
    mDt.y -= mSpeed;
  }
  void MoveDown(EmptyEventData* unused) {
    mDt.y += mSpeed;
  }
  void MoveLeft(EmptyEventData* unused) {
    mDt.x -= mSpeed;
  }
  void MoveRight(EmptyEventData* unused) {
    mDt.x += mSpeed;
  }

private:
  float mSpeed;
  sf::Vector2f mDt;

  // Needed for cleanup
  Observable<EmptyEventData>* mUp;
  Observable<EmptyEventData>* mDown;
  Observable<EmptyEventData>* mLeft;
  Observable<EmptyEventData>* mRight;
  int mUpSubscr, mDownSubscr, mLeftSubscr, mRightSubscr;
};

int testGame() {
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  cout << "Start testGame 2" << endl;
  cout << "before create" << endl;
  auto world = GameWorldFactory::CreateGameWorld("res/testmap/tilemap.json", "", "res/testmap/test-2_");
  cout << "after create" << endl;

  auto tex = AssetManager::GetTexture("res/textures/testtile/testtile_0.png");
  auto tex2 = AssetManager::GetTexture("res/textures/sample.png");
  auto ent = new PlayerEntity(tex, 1.0, upPressed, downPressed, leftPressed, rightPressed);
  auto ent2 = new SpriteTransformableEntity(1, tex2);

  auto scene = new SceneGraph();
  auto parent = scene->GetRoot()->AddChild(ent);
  auto child = parent->AddChild(ent2);

  // vector<ObservableBase*> events;

  GameOptions options{"My Game", sf::Vector2i(800, 600), 50};
  game::Game app(options, scene, world);

  app.AddEvent(upPressed);
  app.AddEvent(downPressed);
  app.AddEvent(leftPressed);
  app.AddEvent(rightPressed);
  app.Run();

  // sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");while(window.isOpen()) {
  //   sf::Event event;
  //   while(window.pollEvent(event)) {
  //     if(event.type == sf::Event::Closed)
  //       window.close();
  //   }
  //   window.clear();

  //   // cout << "before render" << endl;
  //   world->Render(&window);
  //   // cout << "after render" << endl;
  //   // ent->Render(&window);
  //   // ent2->Render(&window);
  //   std::this_thread::sleep_for(std::chrono::milliseconds(20));
  //   // window.draw(shape);
  //   window.display();
  // }
}

int main() {
  std::cout << "Hello Compiler 4" << std::endl;

  // testEvents();
  // testEntity();
  // testEntity2();
  // testTiles();
  // testWorldLoader();
  testGame();

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