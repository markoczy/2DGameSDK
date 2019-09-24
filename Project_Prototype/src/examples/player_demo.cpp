#include <examples.h>

using namespace std;
using namespace game;

// Type of player entity
const int _PLAYER_TYPE = 200;

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
               Observable<EmptyEventData>* right) : SpriteTransformableEntity(_PLAYER_TYPE, texture), mSpeed(speed) {
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
      Transform(sf::Transform().translate(mDt));
      // GetTransformable()->move(mDt);
      mDt = sf::Vector2f();
    }
  }

  void MoveUp(EmptyEventData*) {
    mDt.y -= mSpeed;
  }

  void MoveDown(EmptyEventData*) {
    mDt.y += mSpeed;
  }

  void MoveLeft(EmptyEventData*) {
    mDt.x -= mSpeed;
  }

  void MoveRight(EmptyEventData*) {
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
  RotatingEntity(int type,
                 sf::Texture* texture,
                 std::vector<sf::Vector2f> collisionMask,
                 float rotPerTick,
                 sf::Vector2f pos = sf::Vector2f()) : SpriteTransformableEntity(type, texture, collisionMask), mRot(rotPerTick) {
    auto rect = mSprite.getTextureRect();
    mCenter = sf::Vector2f(rect.width / 2, rect.height / 2);
    SetTransform(sf::Transform().translate(pos));
  }

  void Tick() {
    Transform(sf::Transform().rotate(mRot, mCenter));
  }

private:
  float mRot;
  sf::Vector2f mCenter;
};

int playerDemo(float zoom) {
  cout << "Start playerDemo" << endl;

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/testmap/tilemap.json", "", "res/testmap/tile_");

  // Create Player entity and Rotating child entity
  auto tex = AssetManager::GetTexture("res/textures/sample.png");
  // auto tex2 = AssetManager::GetTexture("res/textures/discus.png");
  auto ent = new PlayerEntity(tex, 2.0, upPressed, downPressed, leftPressed, rightPressed);
  // auto ent2 = new RotatingEntity(tex2, 5.0);

  // Layout entities in scene
  auto scene = new SceneGraph();
  auto parent = scene->AddEntity(ent); // scene->GetRoot()->AddChild(ent);
  scene->AddEntity(ent, parent); // parent->AddChild(ent2);

  // Create game
  GameOptions options{"My Game", sf::Vector2i(512, 512), zoom, 50};
  auto app = new Game(options, scene, world);

  // Send Events to controller
  app->AddEvent(upPressed);
  app->AddEvent(downPressed);
  app->AddEvent(leftPressed);
  app->AddEvent(rightPressed);

  // Run Game
  app->Run();

  return 0;
}