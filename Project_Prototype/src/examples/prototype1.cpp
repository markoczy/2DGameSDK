#include <examples.h>

using namespace game;
using namespace std;
using namespace sf;

// Type of player entity
const int _PLAYER_TYPE = 200;

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
      // GetTransformable()->move(mDt);
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

int prototype1() {
  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  float aspectRatio = (float)sf::VideoMode::getDesktopMode().width / (float)sf::VideoMode::getDesktopMode().height;

  // Create game
  auto options = GameOptions{"Arcade Shooter Prototype", sf::Vector2i(1024, 1024 / aspectRatio), 0.5, 60, false, false};
  auto game = new Game(options);

  // Send Events to controller
  game->AddEvent(upPressed);
  game->AddEvent(downPressed);
  game->AddEvent(leftPressed);
  game->AddEvent(rightPressed);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/proto1/tilemap.json", "", "res/maps/proto1/tile_");
  game->SetWorld(world);

  auto tex = AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_scorpio_1.png");
  auto player = new PlayerEntity(game, tex, 10.0, upPressed, downPressed, leftPressed, rightPressed);
  // player->SetTransform(sf::Transform().translate())

  // Layout entities in scene
  auto scene = new SceneGraph(game);
  scene->AddEntity(player);
  game->SetScene(scene);

  auto cam = new BoundedFollowCameraController(game, player);
  auto bounds = cam->GetBounds();
  cam->SetCenter(sf::Vector2f(bounds.x / 2 + 4.8, bounds.y / 2));
  game->SetCameraController(cam);

  game->GetAudioController()->PlayRepeated(AssetManager::GetAudio("res/audio/tgfcoder/FrozenJam.oga"));
  game->Run();
  return 0;
}