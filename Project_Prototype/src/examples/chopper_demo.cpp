#include <examples.h>

using namespace std;
using namespace game;

// Type of player entity
const int _PLAYER_TYPE = 200;
const int _ENEMY_TYPE = 100;
static const float _OFFSET = 90;

/**
 * @brief Test Entity: Rotates on every tick
 *
 */
class RotatingEntity : public SpriteKinematicEntity {
public:
  RotatingEntity(Game* game,
                 int type,
                 sf::Texture* texture,
                 Shape* shape,
                 float rotPerTick,
                 sf::Vector2f pos = sf::Vector2f()) : SpriteKinematicEntity(type, game, texture, vector<Shape*>({shape})), mRot(rotPerTick) {
    auto rect = mSprite.getTextureRect();
    mCenter = sf::Vector2f(rect.width / 2, rect.height / 2);
    SetTransform(sf::Transform().translate(pos));
  }

  void OnTick() {
    Transform(sf::Transform().rotate(mRot));
  }

  bool IsCollidable() {
    return true;
  }

private:
  float mRot;
  sf::Vector2f mCenter;
};

class ChopperEntity : public SpriteKinematicEntity {
public:
  ChopperEntity(Game* game,
                sf::Texture* tex,
                Shape* shape,
                float speed,
                float rotSpeed,
                Observable<sf::Keyboard::Key>* up,
                Observable<sf::Keyboard::Key>* down,
                Observable<sf::Keyboard::Key>* left,
                Observable<sf::Keyboard::Key>* right,
                sf::Vector2f pos = sf::Vector2f()) : SpriteKinematicEntity(_PLAYER_TYPE, game, tex, vector<Shape*>({shape})), mSpeed(speed), mRotSpeed(rotSpeed) {
    //
    //
    //
    mUp = new MethodObserver<sf::Keyboard::Key, ChopperEntity>(this, &ChopperEntity::MoveForward);
    mDown = new MethodObserver<sf::Keyboard::Key, ChopperEntity>(this, &ChopperEntity::MoveBackward);
    mLeft = new MethodObserver<sf::Keyboard::Key, ChopperEntity>(this, &ChopperEntity::RotLeft);
    mRight = new MethodObserver<sf::Keyboard::Key, ChopperEntity>(this, &ChopperEntity::RotRight);

    mUp->SubscribeTo(up);
    mDown->SubscribeTo(down);
    mLeft->SubscribeTo(left);
    mRight->SubscribeTo(right);

    auto rect = mSprite.getTextureRect();
    mCenter = sf::Vector2f(rect.width / 2, rect.height / 2);
    SetTransform(sf::Transform().translate(pos));
    mDir = sf::Vector2f(0, -1);
  }

  void OnTick() {
    sf::Transform transform;
    if(mDw != 0) {
      // transform.rotate(mDw, mCenter);
      transform.rotate(mDw);
      mAngle += mDw;
    }
    // translate
    else if(mDt.x != 0 || mDt.y != 0) {
      cout << "mDt: (" << mDt.x << ", " << mDt.y << ")" << endl;
      transform.translate(mDt);
    }
    auto pos = transform.transformPoint(sf::Vector2f());
    Transform(transform);
    mDt = sf::Vector2f();
    mDw = 0.0;
  }

  void MoveForward(sf::Keyboard::Key) {
    mDt += mSpeed * mDir;
  }

  void MoveBackward(sf::Keyboard::Key) {
    mDt -= mSpeed * mDir;
  }

  void RotLeft(sf::Keyboard::Key) {
    mDw += mRotSpeed;
  }

  void RotRight(sf::Keyboard::Key) {
    mDw -= mRotSpeed;
  }

  bool IsCollidable() {
    return true;
  }

  int OnCollision(CollisionEventType type, Entity* other, cpArbiter*) {
    // if(other->GetType() == _ENEMY_TYPE) {
    //   std::cout << "Collision with enemy detected!! Point: (" << point.x
    //             << ", " << point.y << ")" << std::endl;
    // }
    std::string typeStr;
    switch(type) {
    case CollisionEventType::Begin:
      typeStr = "Begin";
      break;
    case CollisionEventType::PreSolve:
      typeStr = "Pre Solve";
      break;
    case CollisionEventType::PostSolve:
      typeStr = "Post Solve";
      break;
    case CollisionEventType::Separate:
      typeStr = "Separate";
      break;
    }

    if(other->GetType() == _ENEMY_TYPE) {
      std::cout << "Collision with Enemy: " << typeStr << std::endl;
      return 1;
    }
    // std::cout << "Registered Collision Event " << typeStr << " cur: " << GetId() << " other " << other->GetId() << std::endl;
    return 0;
  }

private:
  float mSpeed, mRotSpeed;

  // Delta Transform of current tick
  sf::Vector2f mDt = sf::Vector2f();
  // Delta Rotation of current tick
  float mDw = 0;

  float mAngle;
  sf::Vector2f mDir;
  sf::Vector2f mCenter;

  // Needed for cleanup
  Observer<sf::Keyboard::Key>* mUp;
  Observer<sf::Keyboard::Key>* mDown;
  Observer<sf::Keyboard::Key>* mLeft;
  Observer<sf::Keyboard::Key>* mRight;
};

RectangleShape* getChopperCollisionMask(Game* game) {
  return ShapeFactory::CreateKinematicRectangleShape(game, 16, 32, 0, 0);
}

PolygonShape* getRotorCollisionMask(Game* game) {
  auto verts = vector<cpVect>();

  verts.push_back(cpv(1, 13));
  verts.push_back(cpv(-1, 13));
  verts.push_back(cpv(-1, 1));
  verts.push_back(cpv(-13, 1));
  verts.push_back(cpv(-13, -1));
  verts.push_back(cpv(-1, -1));
  verts.push_back(cpv(-1, -13));
  verts.push_back(cpv(1, -13));
  verts.push_back(cpv(1, -1));
  verts.push_back(cpv(13, -1));
  verts.push_back(cpv(13, 1));
  verts.push_back(cpv(1, 1));
  return ShapeFactory::CreateKinematicPolygonShape(game, verts, 0, 0);
  // return new PolygonKinematicShape(game, verts);
}

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

int chopperDemo() {
  cout << "Start chopperDemo" << endl;

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  auto f1Pressed = new OnKeyPress(sf::Keyboard::F1);
  auto f2Pressed = new OnKeyPress(sf::Keyboard::F2);
  auto f3Pressed = new OnKeyPress(sf::Keyboard::F3);
  auto f4Pressed = new OnKeyPress(sf::Keyboard::F4);

  // Create game
  auto game = new Game();
  game->SetOptions(GameOptions{"My Game", sf::Vector2i(512, 512), 1.0, 50, false, false});

  auto gameController = new GameController(game);
  f1Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));
  f2Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));
  f3Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));
  f4Pressed->Subscribe(new MethodObserver<sf::Keyboard::Key, GameController>(gameController, &gameController->HandleKeyPress));

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");
  game->SetWorld(world);

  // Create Player entity and Rotating child entity
  auto tex = AssetManager::GetTexture("res/textures/heli/heli.png");
  auto tex2 = AssetManager::GetTexture("res/textures/heli/rotor.png");
  auto chopperCollisionMask = getChopperCollisionMask(game);
  auto ent = new ChopperEntity(game, tex, chopperCollisionMask, 2.0, 5.0, upPressed, downPressed, leftPressed, rightPressed, sf::Vector2f(50, 50));

  // auto ent2 = new RotatingEntity(game, 1, tex2, rotorCollisionMask, 15.0, sf::Vector2f(-5, 2));
  auto rotorCollisionMask = getRotorCollisionMask(game);
  auto ent2 = new RotatingEntity(game, _PLAYER_TYPE, tex2, rotorCollisionMask, 15.0, sf::Vector2f(0, 0));

  // auto tex3 = AssetManager::GetTexture("res/textures/heli/rotor.png");
  auto enemyCollisionMask = getRotorCollisionMask(game);
  auto enemy = new RotatingEntity(game, _ENEMY_TYPE, tex2, enemyCollisionMask, 15.0, sf::Vector2f(200, 200));

  // Layout entities in scene
  auto scene = new SceneGraph();
  auto parent = scene->AddEntity(ent); //scene->GetRoot()->AddChild(ent);
  scene->AddEntity(ent2, parent); // parent->AddChild(ent2);
  scene->AddEntity(enemy);
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

  // Run Game
  game->Run();

  return 0;
}