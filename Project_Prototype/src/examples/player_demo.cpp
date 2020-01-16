#include <examples.h>

using namespace std;
using namespace game;

// Type of player entity
const int _PLAYER_TYPE = 200;

/**
 * @brief Test Entity: Movement Controllable by given observables
 */
class PlayerEntity : public SpriteKinematicEntity {
public:
  PlayerEntity(Game* game,
               sf::Texture* texture,
               float speed,
               Observable<sf::Keyboard::Key>* up,
               Observable<sf::Keyboard::Key>* down,
               Observable<sf::Keyboard::Key>* left,
               Observable<sf::Keyboard::Key>* right) : SpriteKinematicEntity(_PLAYER_TYPE, game, texture), mSpeed(speed) {
    //
    //
    //
    mUp = new MethodObserver<sf::Keyboard::Key, PlayerEntity>(this, &PlayerEntity::MoveUp);
    mDown = new MethodObserver<sf::Keyboard::Key, PlayerEntity>(this, &PlayerEntity::MoveDown);
    mLeft = new MethodObserver<sf::Keyboard::Key, PlayerEntity>(this, &PlayerEntity::MoveLeft);
    mRight = new MethodObserver<sf::Keyboard::Key, PlayerEntity>(this, &PlayerEntity::MoveRight);

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

  void OnTick() {
    if(mDt.x != 0 || mDt.y != 0) {
      Transform(sf::Transform().translate(mDt));
      mDt = sf::Vector2f();
    }
  }

  void MoveUp(sf::Keyboard::Key) {
    mDt.y -= mSpeed;
  }

  void MoveDown(sf::Keyboard::Key) {
    mDt.y += mSpeed;
  }

  void MoveLeft(sf::Keyboard::Key) {
    mDt.x -= mSpeed;
  }

  void MoveRight(sf::Keyboard::Key) {
    mDt.x += mSpeed;
  }

private:
  float mSpeed;
  // Delta Transform of current tick
  sf::Vector2f mDt;

  // Needed for cleanup
  Observer<sf::Keyboard::Key>* mUp;
  Observer<sf::Keyboard::Key>* mDown;
  Observer<sf::Keyboard::Key>* mLeft;
  Observer<sf::Keyboard::Key>* mRight;
};

int playerDemo(float zoom) {
  cout << "Start playerDemo" << endl;

  // Create game
  auto options = GameOptions{"My Game", sf::Vector2i(512, 512), zoom, 50};
  auto game = new Game(options);

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/testmap/tilemap.json", "", "res/maps/testmap/tile_");
  game->SetWorld(world);

  // Create Player entity and Rotating child entity
  auto tex = AssetManager::GetTexture("res/textures/sample.png");
  auto ent = new PlayerEntity(game, tex, 2.0, upPressed, downPressed, leftPressed, rightPressed);

  // Layout entities in scene
  auto scene = new SceneGraph(game);
  auto parent = scene->AddEntity(ent);
  scene->AddEntity(ent, parent);

  // Send Events to controller
  game->AddEvent(upPressed);
  game->AddEvent(downPressed);
  game->AddEvent(leftPressed);
  game->AddEvent(rightPressed);

  // Run Game
  game->Run();

  return 0;
}