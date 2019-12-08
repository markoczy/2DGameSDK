#include <examples.h>

using namespace std;
using namespace game;

const int _PLAYER_TYPE = 200;
const int _GROUND_TYPE = 100;

class PhysPlayerEntity : public SpriteDynamicEntity {
public:
  PhysPlayerEntity(Game* game,
                   sf::Texture* texture,
                   float speed,
                   float jumpForce,
                   vector<Shape<DynamicShapeDefinition>*> shapes,
                   Observable<sf::Keyboard::Key>* up,
                   Observable<sf::Keyboard::Key>* down,
                   Observable<sf::Keyboard::Key>* left,
                   Observable<sf::Keyboard::Key>* right) : SpriteDynamicEntity(_PLAYER_TYPE, game, texture, shapes, true), mSpeed(speed), mJumpForce(jumpForce) {
    //
    //
    //
    mUp = new MethodObserver<sf::Keyboard::Key, PhysPlayerEntity>(this, &PhysPlayerEntity::MoveUp);
    mDown = new MethodObserver<sf::Keyboard::Key, PhysPlayerEntity>(this, &PhysPlayerEntity::MoveDown);
    mLeft = new MethodObserver<sf::Keyboard::Key, PhysPlayerEntity>(this, &PhysPlayerEntity::MoveLeft);
    mRight = new MethodObserver<sf::Keyboard::Key, PhysPlayerEntity>(this, &PhysPlayerEntity::MoveRight);

    mUp->SubscribeTo(up);
    mDown->SubscribeTo(down);
    mLeft->SubscribeTo(left);
    mRight->SubscribeTo(right);
  }

  ~PhysPlayerEntity() {
    delete mUp;
    delete mDown;
    delete mLeft;
    delete mRight;
  }

  void OnTick() {
    if(mForce.x != 0 || mForce.y != 0) {
      SetForce(mForce);
      mForce = cpv(0, 0);
    }
  }

  void MoveUp(sf::Keyboard::Key) {
    if(touchingFloor) {
      mForce.y += mJumpForce;
      // SetForce(cpv(0, mJumpForce));
    }
  }

  void MoveDown(sf::Keyboard::Key) {
    // SetForce(cpv(0, -mSpeed));
  }

  void MoveLeft(sf::Keyboard::Key) {
    mForce.x -= mSpeed;
    // SetForce(cpv(-mSpeed, 0));
  }

  void MoveRight(sf::Keyboard::Key) {
    mForce.x += mSpeed;
    // SetForce(cpv(mSpeed, 0));
  }

  int OnCollision(CollisionEventType type, Entity* other, cpArbiter*) {
    if(other->GetType() == _GROUND_TYPE) {
      if(type == CollisionEventType::Begin) {
        cout << "Touching floor" << endl;
        touchingFloor = true;
      } else if(type == CollisionEventType::Separate) {
        cout << "Separated floor" << endl;
        touchingFloor = false;
      }
    }

    return 1;
  }

  int OnWorldCollision(CollisionEventType type, Tile* tile, cpArbiter*) {
    if(tile->Material->Type == _GROUND_TYPE) {
      if(type == CollisionEventType::Begin) {
        cout << "Touching floor" << endl;
        touchingFloor = true;
      } else if(type == CollisionEventType::Separate) {
        cout << "Separated floor" << endl;
        touchingFloor = false;
      }
    }
    return 1;
  }

private:
  cpVect mForce = cpv(0, 0);
  bool touchingFloor = false;
  float mSpeed;
  float mJumpForce;
  // Delta Transform of current tick
  sf::Vector2f mDt;

  // Needed for cleanup
  Observer<sf::Keyboard::Key>* mUp;
  Observer<sf::Keyboard::Key>* mDown;
  Observer<sf::Keyboard::Key>* mLeft;
  Observer<sf::Keyboard::Key>* mRight;
};

class GameController {
public:
  GameController(Game* game) : mGame(game) {}

  void HandleKeyPress(sf::Keyboard::Key key) {
    auto options = mGame->GetOptions();
    switch(key) {
    case sf::Keyboard::Key::F1:
      options.RenderCollisionMask = false;
      break;
    case sf::Keyboard::Key::F2:
      options.RenderCollisionMask = true;
      break;
    case sf::Keyboard::Key::F3:
      options.RenderAABB = false;
      break;
    case sf::Keyboard::Key::F4:
      options.RenderAABB = true;
      break;
    default:
      break;
    }
    mGame->SetOptions(options);
  }

private:
  Game* mGame = nullptr;
};

int demo1() {
  cout << "Physics Demo" << endl;

  // Create game
  auto options = GameOptions{"My Game", sf::Vector2i(512, 512), 2.0, 50, false, true};
  auto game = new Game(options);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld(game, "res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");
  game->SetWorld(world);

  auto boxTx = AssetManager::GetTexture("res/textures/box/box.png");

  auto scene = new SceneGraph(game);

  auto groundShape = ShapeFactory::CreateStaticRectangleShape(game, 200, 60, 1, 0.3);
  auto ground = new SpriteStaticEntity(1, game, boxTx, {groundShape}, true);
  ground->SetSize(sf::Vector2f(200, 60));
  ground->SetTransform(sf::Transform().translate(100, 200));

  auto shape = ShapeFactory::CreateDynamicRectangleShape(game, 5, 5, 0.1, 0.3, 1, true);
  auto boxRenderer = new SingleSpriteRenderStrategy(game, boxTx);
  boxRenderer->SetSize(sf::Vector2f(5, 5));
  auto box = new DynamicEntity(2, game, boxRenderer, {shape}, true);
  box->SetTransform(sf::Transform().translate(100, 100).rotate(10));

  scene->AddEntity(ground);
  scene->AddEntity(box);
  game->SetScene(scene);

  auto space = game->GetPhysicalWorld();
  cpSpaceSetGravity(space, cpv(0, -10));

  // Run Game
  game->Run();

  return 0;
}

SpriteStaticEntity* getBox(Game* game, float w, float h, float x, float y) {
  auto shape = ShapeFactory::CreateStaticRectangleShape(game, w, h, 0.7, 0.1, false);
  auto ret = new SpriteStaticEntity(_GROUND_TYPE, game, AssetManager::GetTexture("res/textures/box/box.png"), {shape}, true);
  ret->SetSize(sf::Vector2f(w, h));
  ret->SetTransform(sf::Transform().translate(x, y));
  return ret;
}

int demo2() {
  cout << "Physics Demo 2" << endl;

  // Create game
  auto options = GameOptions{"My Game", sf::Vector2i(200, 200), 2.0, 60, false, false, 0.5};
  auto game = new Game(options);

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  auto f1Pressed = new OnKeyPress(sf::Keyboard::F1);
  auto f2Pressed = new OnKeyPress(sf::Keyboard::F2);
  auto f3Pressed = new OnKeyPress(sf::Keyboard::F3);
  auto f4Pressed = new OnKeyPress(sf::Keyboard::F4);

  auto gameController = new GameController(game);
  f1Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));
  f2Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));
  f3Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));
  f4Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld(game, "res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");
  game->SetWorld(world);

  auto boxTx = AssetManager::GetTexture("res/textures/box/box.png");

  auto scene = new SceneGraph(game);

  float groundW = 50;
  float groundH = 5;
  auto groundShape = ShapeFactory::CreateStaticRectangleShape(game, groundW, groundH, 0.7, 0.1);
  auto ground = new SpriteStaticEntity(_GROUND_TYPE, game, boxTx, {groundShape}, true);
  ground->SetSize(sf::Vector2f(groundW, groundH));
  ground->SetTransform(sf::Transform().translate(25, 47.5));

  float playerW = 1;
  float playerH = 1;
  float playerMass = 5;
  // auto shape = new CircleDynamicShape(game, 1);
  auto shape = ShapeFactory::CreateDynamicRectangleShape(game, playerW, playerH, 1, 0.7, 0.1);
  auto player = new PhysPlayerEntity(game, boxTx, 50, 1100, {shape}, upPressed, downPressed, leftPressed, rightPressed);
  player->SetSize(sf::Vector2f(playerW, playerH));
  player->SetTransform(sf::Transform().translate(10, 15));
  player->SetMass(playerMass);
  player->SetMoment(cpMomentForBox(playerMass, playerW, playerH));

  scene->AddEntity(ground);
  scene->AddEntity(getBox(game, 5, 2.5, 10, 43.75));
  scene->AddEntity(getBox(game, 5, 2.5, 15, 43.75));
  scene->AddEntity(getBox(game, 5, 2.5, 15, 41.25));

  scene->AddEntity(getBox(game, 5, 2.5, 25, 43.75));
  scene->AddEntity(getBox(game, 5, 2.5, 25, 41.25));

  scene->AddEntity(getBox(game, 5, 2.5, 30, 41.25));
  scene->AddEntity(getBox(game, 5, 2.5, 30, 38.75));

  scene->AddEntity(getBox(game, 5, 2.5, 40, 36.25));

  scene->AddEntity(getBox(game, 5, 10, 45, 32.5));

  scene->AddEntity(getBox(game, 5, 2.5, 30, 22.5));
  scene->AddEntity(getBox(game, 5, 2.5, 25, 22.5));

  scene->AddEntity(player);
  game->SetScene(scene);

  // Send Events to controller
  game->AddEvent(upPressed);
  game->AddEvent(downPressed);
  game->AddEvent(leftPressed);
  game->AddEvent(rightPressed);

  game->AddEvent(f1Pressed);
  game->AddEvent(f2Pressed);
  game->AddEvent(f3Pressed);
  game->AddEvent(f4Pressed);

  auto space = game->GetPhysicalWorld();
  cpSpaceSetGravity(space, cpv(0, -10));

  // Run Game
  game->Run();

  return 0;
}

int demo3() {
  cout << "Physics Demo 3" << endl;
  // Create game
  auto options = GameOptions{"My Game", sf::Vector2i(512, 512), 2, 60, false, false, 0.1};
  auto game = new Game(options);

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  auto f1Pressed = new OnKeyPress(sf::Keyboard::F1);
  auto f2Pressed = new OnKeyPress(sf::Keyboard::F2);
  auto f3Pressed = new OnKeyPress(sf::Keyboard::F3);
  auto f4Pressed = new OnKeyPress(sf::Keyboard::F4);

  auto gameController = new GameController(game);
  f1Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));
  f2Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));
  f3Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));
  f4Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld(game, "res/physicstest/tilemap.json", "res/physicstest/materialmap.json", "res/physicstest/tile_");
  game->SetWorld(world);

  auto boxTx = AssetManager::GetTexture("res/textures/box/box.png");

  auto scene = new SceneGraph(game);

  // float groundW = 51.2;
  // float groundH = 5;
  // auto groundShape = ShapeFactory::CreateStaticRectangleShape(game, groundW, groundH, 0.7, 0.1, false);
  // auto ground = new SpriteStaticEntity(_GROUND_TYPE, game, boxTx, {groundShape}, true);
  // ground->SetSize(sf::Vector2f(groundW, groundH));
  // ground->SetTransform(sf::Transform().translate(25.6, 2.5));
  // scene->AddEntity(ground);

  float playerW = 1;
  float playerH = 1;
  float playerMass = 5;
  // auto shape = new CircleDynamicShape(game, 1);
  auto shape = ShapeFactory::CreateDynamicRectangleShape(game, playerW, playerH, 1, 0.7, 0.1);
  auto player = new PhysPlayerEntity(game, boxTx, 50, 1100, {shape}, upPressed, downPressed, leftPressed, rightPressed);
  player->SetSize(sf::Vector2f(playerW, playerH));
  player->SetTransform(sf::Transform().translate(10, 15));
  player->SetMass(playerMass);
  player->SetMoment(cpMomentForBox(playerMass, playerW, playerH));
  scene->AddEntity(player);

  auto cam = new BoundedFollowCameraController(game, player);
  auto bounds = cam->GetBounds();
  cam->SetCenter(sf::Vector2f(bounds.x / 2 + 4.8, bounds.y / 2));
  game->SetCameraController(cam);

  auto box = new SpriteStaticEntity(_GROUND_TYPE, game, boxTx, {}, false);
  box->SetTransform(sf::Transform().translate(20, 15));
  scene->AddEntity(box);
  game->SetScene(scene);

  auto heart1 = new sf::Sprite(*AssetManager::GetTexture("res/textures/overlay/heart_14x16.png"));
  heart1->setPosition(5, 5);
  auto heart2 = new sf::Sprite(*AssetManager::GetTexture("res/textures/overlay/heart_14x16.png"));
  heart2->setPosition(25, 5);
  auto overlay = new OverlayDisplay(game);
  overlay->AddElement(heart1);
  overlay->AddElement(heart2);
  game->SetOverlayDisplay(overlay);

  // Send Events to controller
  game->AddEvent(upPressed);
  game->AddEvent(downPressed);
  game->AddEvent(leftPressed);
  game->AddEvent(rightPressed);

  game->AddEvent(f1Pressed);
  game->AddEvent(f2Pressed);
  game->AddEvent(f3Pressed);
  game->AddEvent(f4Pressed);

  auto space = game->GetPhysicalWorld();
  cpSpaceSetGravity(space, cpv(0, -10));

  std::cout << "World size: (" << game->GetWorld()->GetBounds().width << ", " << game->GetWorld()->GetBounds().height << ")" << std::endl;

  // Run Game
  game->Run();

  return 0;
}

int physicsDemo() {
  return demo3();
}