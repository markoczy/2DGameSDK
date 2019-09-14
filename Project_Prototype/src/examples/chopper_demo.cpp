#include <examples.h>

using namespace std;
using namespace game;

// Type of player entity
const int _PLAYER_TYPE = 200;
static const float _OFFSET = 90;

/**
 * @brief Test Entity: Rotates on every tick
 * 
 */
class RotatingEntity : public SpriteTransformableEntity {
public:
  RotatingEntity(sf::Texture* texture,
                 float rotPerTick,
                 sf::Vector2f pos = sf::Vector2f()) : SpriteTransformableEntity(1, texture), mRot(rotPerTick) {
    auto rect = mSprite.getTextureRect();
    // cout << "Texture rect: w = " << rect.width << ", h = " << rect.height << endl;
    GetTransformable()->setOrigin(float(rect.width) / 2.0, float(rect.height) / 2.0);
    GetTransformable()->setPosition(pos);
  }

  void Tick() {
    GetTransformable()->rotate(mRot);
  }

private:
  float mRot;
};

class ChopperEntity : public SpriteTransformableEntity {
public:
  ChopperEntity(sf::Texture* tex,
                float speed,
                float rotSpeed,
                Observable<EmptyEventData>* up,
                Observable<EmptyEventData>* down,
                Observable<EmptyEventData>* left,
                Observable<EmptyEventData>* right,
                sf::Vector2f pos = sf::Vector2f()) : SpriteTransformableEntity(_PLAYER_TYPE, tex), mSpeed(speed), mRotSpeed(rotSpeed) {
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
    GetTransformable()->setOrigin(float(rect.width) / 2.0, float(rect.height) / 2.0);
    GetTransformable()->setPosition(pos);
    GetTransformable()->setRotation(0);
    mDir = sf::Vector2f(0, -1);
  }

  void Tick() {
    auto transformable = GetTransformable();
    // rotate
    if(mDw != 0) {
      transformable->rotate(mDw);
      float rot = _OFFSET - transformable->getRotation();
      float rotRad = (rot * 3.141) / 180.0;
      mDir = sf::Vector2f(cos(rotRad), -sin(rotRad));
    }
    // translate
    else if(mDt.x != 0 || mDt.y != 0) {
      transformable->move(mDt);
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

int chopperDemo() {
  cout << "Start chopperDemo" << endl;

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");

  // Create Player entity and Rotating child entity
  auto tex = AssetManager::GetTexture("res/textures/heli/heli.png");
  auto tex2 = AssetManager::GetTexture("res/textures/heli/rotor.png");
  auto ent = new ChopperEntity(tex, 2.0, 5.0, upPressed, downPressed, leftPressed, rightPressed, sf::Vector2f(50, 50));
  auto ent2 = new RotatingEntity(tex2, 15.0, sf::Vector2f(8, 15));

  // Layout entities in scene
  auto scene = new SceneGraph();
  auto parent = scene->GetRoot()->AddChild(ent);
  auto child = parent->AddChild(ent2);

  // Create game
  GameOptions options{"My Game", sf::Vector2i(512, 512), 2.0, 50, true, true};
  auto app = new Game(options, scene, world);

  // Send Events to controller
  app->AddEvent(upPressed);
  app->AddEvent(downPressed);
  app->AddEvent(leftPressed);
  app->AddEvent(rightPressed);

  // Run Game
  app->Run();
}