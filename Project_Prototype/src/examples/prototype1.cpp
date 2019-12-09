#include <examples.h>

using namespace game;
using namespace std;
using namespace sf;

// Type of player entity
const int _PLAYER_TYPE = 200;
const int _CAM_TYPE = 500;

class Proto1PlayerEntity : public SpriteKinematicEntity {
public:
  Proto1PlayerEntity(Game* game,
                     sf::Texture* texture,
                     float speed,
                     Observable<sf::Keyboard::Key>* up,
                     Observable<sf::Keyboard::Key>* down,
                     Observable<sf::Keyboard::Key>* left,
                     Observable<sf::Keyboard::Key>* right,
                     Observable<sf::Keyboard::Key>* space) : SpriteKinematicEntity(_PLAYER_TYPE, game, texture), mSpeed(speed) {
    //
    //
    //
    mUp = new MethodObserver<sf::Keyboard::Key, Proto1PlayerEntity>(this, &Proto1PlayerEntity::MoveUp);
    mDown = new MethodObserver<sf::Keyboard::Key, Proto1PlayerEntity>(this, &Proto1PlayerEntity::MoveDown);
    mLeft = new MethodObserver<sf::Keyboard::Key, Proto1PlayerEntity>(this, &Proto1PlayerEntity::MoveLeft);
    mRight = new MethodObserver<sf::Keyboard::Key, Proto1PlayerEntity>(this, &Proto1PlayerEntity::MoveRight);
    mSpace = new MethodObserver<sf::Keyboard::Key, Proto1PlayerEntity>(this, &Proto1PlayerEntity::Shoot);

    mUp->SubscribeTo(up);
    mDown->SubscribeTo(down);
    mLeft->SubscribeTo(left);
    mRight->SubscribeTo(right);
    mSpace->SubscribeTo(space);

    mSize = sf::Vector2f(texture->getSize().x, texture->getSize().y);
  }

  ~Proto1PlayerEntity() {
    delete mUp;
    delete mDown;
    delete mLeft;
    delete mRight;
    delete mSpace;
  }

  void OnTick() {
    if(mDt.x != 0 || mDt.y != 0) {
      auto transform = GetTransform();
      auto bottomLeft = transform.transformPoint(sf::Vector2f(-mSize.x / 2, -mSize.y / 2));
      auto topRight = transform.transformPoint(sf::Vector2f(mSize.x / 2, mSize.y / 2));
      auto camBounds = getGame()->GetCameraController()->GetBounds();

      if(bottomLeft.x + mDt.x < -camBounds.x / 2) {
        mDt.x = -(camBounds.x / 2) - bottomLeft.x;
      } else if(topRight.x + mDt.x > camBounds.x / 2) {
        mDt.x = camBounds.x / 2 - topRight.x;
      }

      if(bottomLeft.y + mDt.y < -camBounds.y / 2) {
        mDt.y = -(camBounds.y / 2) - bottomLeft.y;
      } else if(topRight.y + mDt.y > camBounds.y / 2) {
        mDt.y = camBounds.y / 2 - topRight.y;
      }

      SetTransform(transform * sf::Transform().translate(mDt));
      mDt = sf::Vector2f();
    }
  }

  void MoveUp(sf::Keyboard::Key) {
    mDt.y += mSpeed;
  }

  void MoveDown(sf::Keyboard::Key) {
    mDt.y -= mSpeed;
  }

  void MoveLeft(sf::Keyboard::Key) {
    mDt.x -= mSpeed;
  }

  void MoveRight(sf::Keyboard::Key) {
    mDt.x += mSpeed;
  }

  void Shoot(sf::Keyboard::Key) {
    if(mLastShoot.getElapsedTime().asMilliseconds() > mCooldownShoot) {
      auto game = (Game*)getGame();
      auto proj = new SequencedProjectile(game, 777, projectileTex, ShapeFactory::CreateKinematicCircleShape(game, 10, 0, 0), GetCombinedTransform().translate(-11, 80), sf::Vector2f(0, 800), 8);
      // auto proj = new SpriteProjectile(game, 777, AssetManager::GetTexture("res/textures/sample.png"), ShapeFactory::CreateKinematicCircleShape(game, 10, 0, 0), GetCombinedTransform().translate(0, 60), sf::Vector2f(0, 1000));
      mLastShoot.restart();
      game->GetAudioController()->PlayOnce(mShootSound);
    }
  }

private:
  float mCooldownShoot = 500;
  sf::Clock mLastShoot;
  float mSpeed;
  sf::SoundBuffer* mShootSound = AssetManager::GetAudio("res/audio/Laser_Shoot.wav");
  std::vector<sf::Texture*> projectileTex = {
      AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green1.png"),
      AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green2.png"),
      AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green3.png"),
      AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green4.png"),
      AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green5.png"),
      AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green6.png"),
  };
  sf::Vector2f mSize;
  // Delta Transform of current tick
  sf::Vector2f mDt;

  // Needed for cleanup
  Observer<sf::Keyboard::Key>* mUp;
  Observer<sf::Keyboard::Key>* mDown;
  Observer<sf::Keyboard::Key>* mLeft;
  Observer<sf::Keyboard::Key>* mRight;
  Observer<sf::Keyboard::Key>* mSpace;
};

class ScrollCamera : public DefaultCameraController, public Entity {
public:
  ScrollCamera(Game* game) : DefaultCameraController(game), Entity(_CAM_TYPE, game) {
    SetZoom(game->GetOptions().InitialZoom);
    SetCenter(sf::Vector2f(GetBounds().x / 2, GetBounds().y / 2));
  }

  ~ScrollCamera() {}

  sf::Transform GetTransform() {
    return mTransform;
  }

  sf::Transform GetCombinedTransform() {
    return mTransform;
  }

  void SetScroll(sf::Vector2f scrollPerTick) {
    mScroll = scrollPerTick;
  }

  void SetCenter(sf::Vector2f center) {
    DefaultCameraController::SetCenter(center);
    SetTransform(sf::Transform().translate(center));
  }

  void OnTick() {
    DefaultCameraController::OnTick();
    auto newCenter = mCenter + mScroll;
    SetCenter(newCenter);
  }

  void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default) {}

protected:
  sf::Transform mTransform;
  sf::Vector2f mLocalCenter;
  sf::Vector2f mScroll;

  bool setTransform(sf::Transform transform) {
    mTransform = transform;
    return true;
  }
  bool transform(sf::Transform) { return false; }
};

int prototype1() {
  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);
  auto spacePressed = new OnKeyPress(sf::Keyboard::Space);

  float aspectRatio = (float)sf::VideoMode::getDesktopMode().width / (float)sf::VideoMode::getDesktopMode().height;

  // Create game
  auto options = GameOptions{"Arcade Shooter Prototype", sf::Vector2i(1024, 1024 / aspectRatio), 0.5, 60, false, false};
  auto game = new Game(options);

  // Send Events to controller
  game->AddEvent(upPressed);
  game->AddEvent(downPressed);
  game->AddEvent(leftPressed);
  game->AddEvent(rightPressed);
  game->AddEvent(spacePressed);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/proto1/tilemap.json", "", "res/maps/proto1/tile_");
  game->SetWorld(world);

  auto cam = new ScrollCamera(game);
  cam->SetScroll(sf::Vector2f(0, 1));
  game->SetCameraController(cam);

  auto tex = AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_scorpio_1.png");
  auto player = new Proto1PlayerEntity(game, tex, 5.0, upPressed, downPressed, leftPressed, rightPressed, spacePressed);
  float offsetY = -(cam->GetBounds().y / 2.0) + 80;
  player->SetTransform(sf::Transform().translate(0, offsetY));

  // Layout entities in scene
  auto scene = new SceneGraph(game);
  int camId = scene->AddEntity(cam);
  scene->AddEntity(player, camId);
  game->SetScene(scene);

  game->GetAudioController()->PlayRepeated(AssetManager::GetAudio("res/audio/tgfcoder/FrozenJam.oga"));

  game->Run();
  return 0;
}