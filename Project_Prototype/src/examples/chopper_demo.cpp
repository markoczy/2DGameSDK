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
class RotatingEntity : public SpriteTransformableEntity {
public:
  RotatingEntity(Game* game,
                 int type,
                 sf::Texture* texture,
                 std::vector<sf::Vector2f> collisionMask,
                 float rotPerTick,
                 sf::Vector2f pos = sf::Vector2f()) : SpriteTransformableEntity(type, game, texture, collisionMask), mRot(rotPerTick) {
    auto rect = mSprite.getTextureRect();
    mCenter = sf::Vector2f(rect.width / 2, rect.height / 2);
    SetTransform(sf::Transform().translate(pos));
  }

  void OnTick() {
    Transform(sf::Transform().rotate(mRot, mCenter));
  }

  bool IsCollidable() {
    return true;
  }

private:
  float mRot;
  sf::Vector2f mCenter;
};

class ChopperEntity : public SpriteTransformableEntity {
public:
  ChopperEntity(Game* game,
                sf::Texture* tex,
                std::vector<sf::Vector2f> collisionMask,
                float speed,
                float rotSpeed,
                Observable<EmptyEventData>* up,
                Observable<EmptyEventData>* down,
                Observable<EmptyEventData>* left,
                Observable<EmptyEventData>* right,
                sf::Vector2f pos = sf::Vector2f()) : SpriteTransformableEntity(_PLAYER_TYPE, game, tex, collisionMask), mSpeed(speed), mRotSpeed(rotSpeed) {
    //
    //
    //
    mUp = new MethodObserver<EmptyEventData, ChopperEntity>(this, &ChopperEntity::MoveForward);
    mDown = new MethodObserver<EmptyEventData, ChopperEntity>(this, &ChopperEntity::MoveBackward);
    mLeft = new MethodObserver<EmptyEventData, ChopperEntity>(this, &ChopperEntity::RotLeft);
    mRight = new MethodObserver<EmptyEventData, ChopperEntity>(this, &ChopperEntity::RotRight);

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
      transform.rotate(mDw, mCenter);
      mAngle += mDw;
    }
    // translate
    else if(mDt.x != 0 || mDt.y != 0) {
      transform.translate(mDt);
    }
    Transform(transform);
    mDt = sf::Vector2f();
    mDw = 0.0;
  }

  void MoveForward(EmptyEventData*) {
    mDt += mSpeed * mDir;
  }

  void MoveBackward(EmptyEventData*) {
    mDt -= mSpeed * mDir;
  }

  void RotLeft(EmptyEventData*) {
    mDw -= mRotSpeed;
  }

  void RotRight(EmptyEventData*) {
    mDw += mRotSpeed;
  }

  bool IsCollidable() {
    return true;
  }

  void OnCollision(Entity* other, sf::Vector2f point) {
    if(other->GetType() == _ENEMY_TYPE) {
      std::cout << "Collision with enemy detected!! Point: (" << point.x
                << ", " << point.y << ")" << std::endl;
    }
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
  Observer<EmptyEventData>* mUp;
  Observer<EmptyEventData>* mDown;
  Observer<EmptyEventData>* mLeft;
  Observer<EmptyEventData>* mRight;
};

std::vector<sf::Vector2f> getChopperCollisionMask() {
  auto ret = std::vector<sf::Vector2f>();
  ret.push_back(sf::Vector2f(7, 0));
  ret.push_back(sf::Vector2f(3, 7));
  ret.push_back(sf::Vector2f(3, 11));
  ret.push_back(sf::Vector2f(0, 12));
  ret.push_back(sf::Vector2f(1, 21));
  ret.push_back(sf::Vector2f(7, 32));

  ret.push_back(sf::Vector2f(9, 32));
  ret.push_back(sf::Vector2f(15, 21));
  ret.push_back(sf::Vector2f(16, 12));
  ret.push_back(sf::Vector2f(13, 11));
  ret.push_back(sf::Vector2f(13, 7));
  ret.push_back(sf::Vector2f(9, 0));

  return ret;
}

std::vector<sf::Vector2f> getRotorCollisionMask() {
  auto ret = std::vector<sf::Vector2f>();
  ret.push_back(sf::Vector2f(12, 0));
  ret.push_back(sf::Vector2f(12, 12));
  ret.push_back(sf::Vector2f(0, 12));
  ret.push_back(sf::Vector2f(0, 14));
  ret.push_back(sf::Vector2f(12, 14));
  ret.push_back(sf::Vector2f(12, 26));
  ret.push_back(sf::Vector2f(14, 26));
  ret.push_back(sf::Vector2f(14, 14));
  ret.push_back(sf::Vector2f(26, 14));
  ret.push_back(sf::Vector2f(26, 12));
  ret.push_back(sf::Vector2f(14, 12));
  ret.push_back(sf::Vector2f(14, 0));
  return ret;
}

int chopperDemo() {
  cout << "Start chopperDemo" << endl;

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  // Create game
  auto game = new Game();
  game->SetOptions(GameOptions{"My Game", sf::Vector2i(512, 512), 2.0, 50, true, true});

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");
  game->SetWorld(world);

  // Create Player entity and Rotating child entity
  auto tex = AssetManager::GetTexture("res/textures/heli/heli.png");
  auto tex2 = AssetManager::GetTexture("res/textures/heli/rotor.png");
  auto chopperCollisionMask = getChopperCollisionMask();
  auto ent = new ChopperEntity(game, tex, chopperCollisionMask, 2.0, 5.0, upPressed, downPressed, leftPressed, rightPressed, sf::Vector2f(50, 50));

  auto rotorCollisionMask = getRotorCollisionMask();
  auto ent2 = new RotatingEntity(game, _PLAYER_TYPE, tex2, rotorCollisionMask, 15.0, sf::Vector2f(-5, 2));

  // auto tex3 = AssetManager::GetTexture("res/textures/heli/rotor.png");
  auto enemy = new RotatingEntity(game, _ENEMY_TYPE, tex2, rotorCollisionMask, 15.0, sf::Vector2f(200, 200));

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

  // Run Game
  game->Run();

  return 0;
}