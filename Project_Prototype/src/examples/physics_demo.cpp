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
                   vector<DynamicShape*> shapes,
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

int demo1() {
  cout << "Physics Demo" << endl;

  // Create game
  auto game = new Game();
  game->SetOptions(GameOptions{"My Game", sf::Vector2i(512, 512), 2.0, 50, false, true});

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");
  game->SetWorld(world);

  auto boxTx = AssetManager::GetTexture("res/textures/box/box.png");

  auto scene = new SceneGraph();

  auto groundShape = new RectangleKinematicShape(game, 200, 60, false);
  groundShape->SetElasticity(1);
  groundShape->SetFriction(0.3);
  auto ground = new SpriteStaticEntity(1, game, boxTx, {groundShape}, true);
  ground->SetSize(sf::Vector2f(200, 60));
  ground->SetTransform(sf::Transform().translate(100, 200));

  auto shape = new RectangleDynamicShape(game, 5, 5);
  shape->SetElasticity(1);
  shape->SetDensity(0.1);
  shape->SetFriction(0.3);
  auto box = new SpriteDynamicEntity(2, game, boxTx, {shape}, true);
  box->SetSize(sf::Vector2f(5, 5));
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

int demo2() {
  cout << "Physics Demo" << endl;

  // Create game
  auto game = new Game();
  game->SetOptions(GameOptions{"My Game", sf::Vector2i(200, 200), 4.0, 60, false, false});

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");
  game->SetWorld(world);

  auto boxTx = AssetManager::GetTexture("res/textures/box/box.png");

  auto scene = new SceneGraph();

  float groundW = 50;
  float groundH = 5;
  auto groundShape = new RectangleKinematicShape(game, groundW, groundH, false);
  groundShape->SetElasticity(0.1);
  groundShape->SetFriction(0.7);
  auto ground = new SpriteStaticEntity(_GROUND_TYPE, game, boxTx, {groundShape}, true);
  ground->SetSize(sf::Vector2f(groundW, groundH));
  ground->SetTransform(sf::Transform().translate(25, 47.5));

  float playerW = 1;
  float playerH = 1;
  float playerMass = 5;
  auto shape = new RectangleDynamicShape(game, playerW, playerH);
  shape->SetElasticity(0.1);
  // shape->SetDensity(1);
  shape->SetFriction(0.7);
  auto box = new PhysPlayerEntity(game, boxTx, 50, 1000, {shape}, upPressed, downPressed, leftPressed, rightPressed);
  box->SetSize(sf::Vector2f(playerW, playerH));
  box->SetTransform(sf::Transform().translate(25, 5));
  box->SetMass(playerMass);
  box->SetMoment(cpMomentForBox(playerMass, playerW, playerH));

  scene->AddEntity(ground);
  scene->AddEntity(box);
  game->SetScene(scene);

  // Send Events to controller
  game->AddEvent(upPressed);
  game->AddEvent(downPressed);
  game->AddEvent(leftPressed);
  game->AddEvent(rightPressed);

  auto space = game->GetPhysicalWorld();
  cpSpaceSetGravity(space, cpv(0, -10));

  // Run Game
  game->Run();

  return 0;
}

int physicsDemo() {
  return demo2();
}