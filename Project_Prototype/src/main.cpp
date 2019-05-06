#include <2DGameSDK/Common.h>
#include <2DGameSDK/Core.h>
#include <2DGameSDK/Event.h>
#include <2DGameSDK/Scene.h>
#include <2DGameSDK/World.h>

#include <chrono>
#include <cmath>
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

// Type of player entity
const int PLAYER_TYPE = 200;

/**
 * @brief Test Entity: Movement Controllable by given observables
 */
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
    mUp = new MethodObserver<EmptyEventData, PlayerEntity>(this, &PlayerEntity::MoveUp);
    mDown = new MethodObserver<EmptyEventData, PlayerEntity>(this, &PlayerEntity::MoveDown);
    mLeft = new MethodObserver<EmptyEventData, PlayerEntity>(this, &PlayerEntity::MoveLeft);
    mRight = new MethodObserver<EmptyEventData, PlayerEntity>(this, &PlayerEntity::MoveRight);

    mUp->SubscribeTo(up);
    mDown->SubscribeTo(down);
    mLeft->SubscribeTo(left);
    mRight->SubscribeTo(right);
  }

  ~PlayerEntity() {
    delete mUp;
    delete mDown;
    delete mLeft;
    delete mRight;
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
  // Delta Transform of current tick
  sf::Vector2f mDt;

  // Needed for cleanup
  Observer<EmptyEventData>* mUp;
  Observer<EmptyEventData>* mDown;
  Observer<EmptyEventData>* mLeft;
  Observer<EmptyEventData>* mRight;
};

/**
 * @brief Test Entity: Rotates on every tick
 * 
 */
class RotatingEntity : public SpriteTransformableEntity {
public:
  RotatingEntity(sf::Texture* texture, float rotPerTick) : SpriteTransformableEntity(1, texture), mRot(rotPerTick) {
    auto rect = mSprite.getTextureRect();
    cout << "Texture rect: w = " << rect.width << ", h = " << rect.height << endl;
    GetTransformable()->setOrigin(float(rect.width) / 2.0, float(rect.height) / 2.0);
  }

  void Tick() {
    GetTransformable()->rotate(mRot);
  }

private:
  float mRot;
};

static const float _OFFSET = 90;
static const int _WALK_ANIM[] = {1, 2, 1, 0, 3, 4, 3, 0};

class Gta2PlayerEntity : public AnimatedTransformableEntity {
public:
  Gta2PlayerEntity(std::map<int, sf::Texture*> animationStates,
                   float speed,
                   float rotSpeed,
                   Observable<EmptyEventData>* up,
                   Observable<EmptyEventData>* down,
                   Observable<EmptyEventData>* left,
                   Observable<EmptyEventData>* right) : AnimatedTransformableEntity(PLAYER_TYPE, animationStates), mSpeed(speed), mRotSpeed(rotSpeed) {
    //
    //
    //
    mUp = new MethodObserver<EmptyEventData, Gta2PlayerEntity>(this, &Gta2PlayerEntity::MoveForward);
    mDown = new MethodObserver<EmptyEventData, Gta2PlayerEntity>(this, &Gta2PlayerEntity::MoveBackward);
    mLeft = new MethodObserver<EmptyEventData, Gta2PlayerEntity>(this, &Gta2PlayerEntity::RotLeft);
    mRight = new MethodObserver<EmptyEventData, Gta2PlayerEntity>(this, &Gta2PlayerEntity::RotRight);

    mUp->SubscribeTo(up);
    mDown->SubscribeTo(down);
    mLeft->SubscribeTo(left);
    mRight->SubscribeTo(right);

    SetAnimState(1);

    auto rect = mCurState.getTextureRect();
    GetTransformable()->setOrigin(9, 9);
    GetTransformable()->move(9, 9);

    GetTransformable()->setRotation(0);
    // float rot = offset;
    // float rotRad = (rot * 2.0 * 3.141) / 360.0;
    // rot = (rot * 180.0) / (2.0 * 3.141);
    mDir = sf::Vector2f(0, -1);
  }

  void Tick() {
    // GetTransformable()->rotate(5.0);
    auto transformable = GetTransformable();
    if(mDw != 0) {
      transformable->rotate(mDw);
      float rot = _OFFSET - transformable->getRotation();
      float rotRad = (rot * 3.141) / 180.0;
      // rot = (rot * 180.0) / (2.0 * 3.141);
      mDir = sf::Vector2f(cos(rotRad), -sin(rotRad));
      // cout << "Rotation: " << rot << ", Dir.X: " << mDir.x << ", Dir.Y: " << mDir.y << endl;
    } else if(mDt.x != 0 || mDt.y != 0) {
      transformable->move(mDt);

      // walk animation
      SetAnimState(_WALK_ANIM[mCurWalk]);
      mCurSkip++;
      if(mCurSkip == 3) {
        mCurWalk++;
        mCurSkip = 0;
      }
      if(mCurWalk >= 8) {
        mCurWalk = 0;
      }
    } else {
      SetAnimState(0);
    }
    mDt = sf::Vector2f();
    mDw = 0.0;
  }

  void MoveForward(EmptyEventData* unused) {
    mDt += mSpeed * mDir;
  }

  void MoveBackward(EmptyEventData* unused) {
    mDt -= mSpeed * mDir;
  }

  void RotLeft(EmptyEventData* unused) {
    mDw -= mRotSpeed;
  }

  void RotRight(EmptyEventData* unused) {
    mDw += mRotSpeed;
  }

private:
  int mCurWalk = 0;
  int mCurSkip = 0;
  float mSpeed, mRotSpeed;
  // Delta Transform of current tick
  sf::Vector2f mDt = sf::Vector2f();
  // Delta Rotation of current tick
  float mDw = 0;

  sf::Vector2f mDir;

  // Needed for cleanup
  Observer<EmptyEventData>* mUp;
  Observer<EmptyEventData>* mDown;
  Observer<EmptyEventData>* mLeft;
  Observer<EmptyEventData>* mRight;
};

int testGame() {
  cout << "Start testGame 3" << endl;

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/testmap/tilemap.json", "", "res/testmap/test-2_");

  // Create Player entity and Rotating child entity
  auto tex = AssetManager::GetTexture("res/textures/sample.png");
  auto tex2 = AssetManager::GetTexture("res/textures/discus.png");
  auto ent = new PlayerEntity(tex, 2.0, upPressed, downPressed, leftPressed, rightPressed);
  auto ent2 = new RotatingEntity(tex2, 5.0);

  // Layout entities in scene
  auto scene = new SceneGraph();
  auto parent = scene->GetRoot()->AddChild(ent);
  auto child = parent->AddChild(ent2);

  // Create game
  GameOptions options{"My Game", sf::Vector2i(800, 600), 2.0, 50};
  auto app = new Game(options, scene, world);

  // Send Events to controller
  app->AddEvent(upPressed);
  app->AddEvent(downPressed);
  app->AddEvent(leftPressed);
  app->AddEvent(rightPressed);

  // Run Game
  app->Run();
}

int testGame2() {
  cout << "Start testGame2 1" << endl;

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/testmap/tilemap.json", "", "res/testmap/test-2_");

  cout << "1" << endl;
  // Create Player entity and Rotating child entity
  auto idle = AssetManager::GetTexture("res/textures/gunner/gunner_idle.png");
  auto walk0 = AssetManager::GetTexture("res/textures/gunner/gunner_walk0.png");
  auto walk1 = AssetManager::GetTexture("res/textures/gunner/gunner_walk1.png");
  auto walk2 = AssetManager::GetTexture("res/textures/gunner/gunner_walk2.png");
  auto walk3 = AssetManager::GetTexture("res/textures/gunner/gunner_walk3.png");
  cout << "2" << endl;
  map<int, sf::Texture*> animStates;
  animStates[0] = idle;
  animStates[1] = walk0;
  animStates[2] = walk1;
  animStates[3] = walk2;
  animStates[4] = walk3;
  cout << "3" << endl;
  auto ent = new Gta2PlayerEntity(animStates, 2.0, 5.0, upPressed, downPressed, leftPressed, rightPressed);

  // Layout entities in scene
  cout << "4" << endl;
  auto scene = new SceneGraph();
  auto parent = scene->GetRoot()->AddChild(ent);

  // Create game
  cout << "5" << endl;
  GameOptions options{"My Game", sf::Vector2i(800, 600), 2.0, 50};
  auto app = new Game(options, scene, world);

  // Send Events to controller
  cout << "6" << endl;
  app->AddEvent(upPressed);
  app->AddEvent(downPressed);
  app->AddEvent(leftPressed);
  app->AddEvent(rightPressed);

  // Run Game
  cout << "7" << endl;
  app->Run();
}

int main() {
  std::cout << "Hello Compiler 28" << std::endl;

  // testEvents();
  // testEntity();
  // testEntity2();
  // testTiles();
  // testWorldLoader();
  // testGame();
  testGame2();

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