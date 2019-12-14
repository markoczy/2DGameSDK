#include <examples.h>

using namespace game;
using namespace std;
using namespace sf;

// Type of player entity
const int _PLAYER_TYPE = 200;
const int _ENEMY_TYPE = 300;
const int _CAM_TYPE = 500;

const int _PLAYER_PROJECTILE = 800;
const int _ENEMY_PROJECTILE = 900;

const std::vector<sf::Texture*> _PROJECTILE_GREEN = {
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green1.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green2.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green3.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green4.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green5.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green6.png"),
};

const std::vector<sf::Texture*> _PROJECTILE_AM_RED = {
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red1.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red2.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red3.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red4.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red5.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red6.png"),
};

sf::SoundBuffer* _SOUND_HIT_HURT_2 = AssetManager::GetAudio("res/audio/Hit_Hurt2.wav");

sf::SoundBuffer* _SOUND_EXPLOSION = AssetManager::GetAudio("res/audio/Explosion.wav");

using KinematicShape = game::Shape<KinematicShapeDefinition>;

std::vector<sf::Texture*> initExplosion1() {
  auto ret = std::vector<sf::Texture*>(63);
  for(int i = 0; i < 63; i++) {
    stringstream ss;
    ss << "res/textures/effects/Sinestesia/explosions2/3_" << setfill('0') << setw(2) << i << ".png";
    ret[i] = AssetManager::GetTexture(ss.str());
  }
  return ret;
}

std::vector<sf::Texture*> _EXPLOSION1 = initExplosion1();

struct HitData {
  int Type = 0;
  int HpLoss = 1;
};

class OnHit : public Observable<HitData> {
public:
  void SetTriggered(HitData data) {
    mTriggered = true;
    mData = data;
  }

protected:
  bool mTriggered = false;
  HitData mData;

  std::tuple<bool, HitData> triggered() {
    bool ret = mTriggered;
    mTriggered = false;
    return std::make_tuple(ret, mData);
  }
};

class DestructibleBehaviour : public Observable<void*> {
public:
  using HitObserver = MethodObserver<HitData, DestructibleBehaviour>;

  DestructibleBehaviour(GameBase* game, OnHit* onHit, SingleSpriteRenderStrategy* renderer, sf::SoundBuffer* hitSound, int hp = 1, int coolDown = 10) : mGame(game), mRenderer(renderer), mHitSound(hitSound), mHp(hp), mCooldown(coolDown), mLastHit(coolDown) {
    mOnHit = new HitObserver(this, &DestructibleBehaviour::HandleHit);
    mOnHit->SubscribeTo(onHit);
  }

  void Update() {
    hitBehaviour();
    glowBehaviour();
    Observable<void*>::Update();
  }

  void HandleHit(HitData data) {
    std::cout << "Handle Hit" << std::endl;
    mHpLoss = data.HpLoss;
  }

protected:
  GameBase* mGame = nullptr;
  HitObserver* mOnHit = nullptr;
  SingleSpriteRenderStrategy* mRenderer = nullptr;
  sf::SoundBuffer* mHitSound = nullptr;
  int mHp = 1;
  int mCooldown = 10;

  // Hit Logic
  int mLastHit = 0;
  bool mDestroyed = false;
  bool mEventSent = false;
  int mHpLoss = 0;

  // Glow Logic
  int mGlowTime = 0;
  bool mIsGlowing = false;

  void hitBehaviour() {
    if(mLastHit++ > mCooldown && mHpLoss > 0) {
      mHp -= mHpLoss;
      mLastHit = 0;
      if(mHp > 0) {
        mGame->GetAudioController()->PlayOnce(mHitSound);
        mGlowTime = 5;
      } else {
        mDestroyed = true;
      }
    }
    mHpLoss = 0;
  }

  void glowBehaviour() {
    if(mGlowTime > 0) {
      if(!mIsGlowing) {
        auto sprite = mRenderer->GetSprite();
        sprite->setColor(sf::Color::Red);
        mIsGlowing = true;
      }
      mGlowTime--;
    } else if(mIsGlowing) {
      auto sprite = mRenderer->GetSprite();
      sprite->setColor(sf::Color::White);
      mIsGlowing = false;
    }
  }

  std::tuple<bool, void*> triggered() {
    return std::make_tuple(mDestroyed, nullptr);
  }
};

class Proto1PlayerEntity : public SpriteKinematicEntity {
public:
  using DestructionHandler = MethodObserver<void*, Proto1PlayerEntity>;

  Proto1PlayerEntity(Game* game,
                     sf::Texture* texture,
                     KinematicShape* shape,
                     float speed,
                     Observable<sf::Keyboard::Key>* up,
                     Observable<sf::Keyboard::Key>* down,
                     Observable<sf::Keyboard::Key>* left,
                     Observable<sf::Keyboard::Key>* right,
                     Observable<sf::Keyboard::Key>* space) : SpriteKinematicEntity(_PLAYER_TYPE, game, texture, {shape}, true), mSpeed(speed), mOnHit(new OnHit()) {
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

    mDestructible = new DestructibleBehaviour(game, mOnHit, mSpriteRenderer, _SOUND_HIT_HURT_2, 3, 10);
    (new DestructionHandler(this, &Proto1PlayerEntity::OnDestroy))->SubscribeTo(mDestructible);
    game->AddEvent(mOnHit);
    game->AddEvent(mDestructible);
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
      auto proj = new SequencedProjectile(game, _PLAYER_PROJECTILE, _PROJECTILE_GREEN, ShapeFactory::CreateKinematicCircleShape(game, 5, 0, 0), GetCombinedTransform().translate(0, 80), sf::Vector2f(0, 600), 100, 8);
      // auto proj = new SpriteProjectile(game, 777, AssetManager::GetTexture("res/textures/sample.png"), ShapeFactory::CreateKinematicCircleShape(game, 10, 0, 0), GetCombinedTransform().translate(0, 60), sf::Vector2f(0, 1000));
      mLastShoot.restart();
      game->GetAudioController()->PlayOnce(mShootSound);
    }
  }

  int OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb) {
    mOnHit->SetTriggered({other->GetType(), 1});
    return 0;
  }

  int OnProjectileCollision(CollisionEventType type, Projectile* projectile, cpArbiter* arb) {
    if(projectile->GetType() == _ENEMY_PROJECTILE) {
      mOnHit->SetTriggered({projectile->GetType(), 1});
    }
    return 0;
  }

  void OnDestroy(void*) {
    if(!mDestroying) {
      cout << "Player Before create explosion" << endl;
      auto explosion = new Effect(getGame(), _EXPLOSION1, GetCombinedTransform());
      cout << "Player After create explosion" << endl;

      getGame()->DestroyEvent(mOnHit);
      getGame()->DestroyEvent(mDestructible);
      getGame()->GetStateManager()->DestroyObject(this);
      getGame()->GetStateManager()->DestroyVisualObject(this);
      getGame()->GetAudioController()->PlayOnce(_SOUND_EXPLOSION);
      mDestroying = true;
      cout << "Plaer After destroy" << endl;
    }
  }

private:
  float mCooldownShoot = 500;
  sf::Clock mLastShoot;
  float mSpeed;
  OnHit* mOnHit = nullptr;
  DestructibleBehaviour* mDestructible = nullptr;
  sf::SoundBuffer* mShootSound = AssetManager::GetAudio("res/audio/Laser_Shoot.wav");
  sf::Vector2f mSize;
  // Delta Transform of current tick
  sf::Vector2f mDt;
  bool mDestroying = false;

  // Needed for cleanup
  Observer<sf::Keyboard::Key>* mUp;
  Observer<sf::Keyboard::Key>* mDown;
  Observer<sf::Keyboard::Key>* mLeft;
  Observer<sf::Keyboard::Key>* mRight;
  Observer<sf::Keyboard::Key>* mSpace;
};

class EnemyEntity : public SpriteKinematicEntity {
public:
  using DestructionHandler = MethodObserver<void*, EnemyEntity>;

  EnemyEntity(Game* game,
              sf::Texture* texture,
              KinematicShape* shape) : SpriteKinematicEntity(_ENEMY_TYPE, game, texture, {shape}, true), mOnHit(new OnHit()) {
    mDestructible = new DestructibleBehaviour(game, mOnHit, mSpriteRenderer, _SOUND_HIT_HURT_2, 3, 10);
    (new DestructionHandler(this, &EnemyEntity::OnDestroy))->SubscribeTo(mDestructible);
    game->AddEvent(mOnHit);
    game->AddEvent(mDestructible);
  };

  int OnProjectileCollision(CollisionEventType type, Projectile* projectile, cpArbiter* arb) {
    if(projectile->GetType() == _PLAYER_PROJECTILE) {
      mOnHit->SetTriggered({projectile->GetType(), 1});
    }
    return 0;
  }

  void OnDestroy(void*) {
    if(!mDestroying) {
      cout << GetId() << " Before create explosion" << endl;
      auto explosion = new Effect(getGame(), _EXPLOSION1, GetCombinedTransform());
      cout << GetId() << " After create explosion" << endl;

      getGame()->DestroyEvent(mOnHit);
      getGame()->DestroyEvent(mDestructible);
      getGame()->GetStateManager()->DestroyObject(this);
      getGame()->GetStateManager()->DestroyVisualObject(this);
      getGame()->GetAudioController()->PlayOnce(_SOUND_EXPLOSION);
      mDestroying = true;
    }
  }

  void Shoot() {
    auto game = (Game*)getGame();
    auto proj = new SequencedProjectile(game, _ENEMY_PROJECTILE, _PROJECTILE_AM_RED, ShapeFactory::CreateKinematicCircleShape(game, 5, 0, 0), GetCombinedTransform().translate(0, 80), sf::Vector2f(0, -300), 500, 8);
  }

  void OnTick() {
    if(mTimeLastShot++ > 200) {
      Shoot();
      mTimeLastShot = 0;
    }
  }

private:
  OnHit* mOnHit = nullptr;
  DestructibleBehaviour* mDestructible = nullptr;

  sf::Clock mCoolDown;
  int mHits = 0;
  bool mDestroying = false;

  int mGlowTime = 0;
  bool mIsGlowing = false;
  int mTimeLastShot = 0;
};

PolygonShape<KinematicShapeDefinition>* getEnemyShape(Game* game) {
  auto verts = vector<cpVect>();
  verts.push_back(cpv(-85, -31));
  verts.push_back(cpv(84, -31));
  verts.push_back(cpv(76, -5));
  verts.push_back(cpv(0, 49));
  verts.push_back(cpv(-1, 49));
  verts.push_back(cpv(-77, -5));
  return ShapeFactory::CreateKinematicPolygonShape(game, verts, 0, 0);
  // return new PolygonKinematicShape(game, verts);
}

PolygonShape<KinematicShapeDefinition>* getPlayerShape(Game* game) {
  auto verts = vector<cpVect>();
  verts.push_back(cpv(-62, -27.5));
  verts.push_back(cpv(61, -27.5));
  verts.push_back(cpv(61, 21.5));
  verts.push_back(cpv(4, 67.5));
  verts.push_back(cpv(-5, 67.5));
  verts.push_back(cpv(-62, 21.5));
  return ShapeFactory::CreateKinematicPolygonShape(game, verts, 0, 0);
  // return new PolygonKinematicShape(game, verts);
}

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
  cam->SetScroll(sf::Vector2f(0, 0.5));
  game->SetCameraController(cam);

  auto playerTex = AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_scorpio_1.png");
  auto enemyTex = AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_scorpio_6B.png");
  auto enemyTex2 = AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_am_1B.png");
  auto playerShape = getPlayerShape(game);
  // auto playerShape = ShapeFactory::CreateKinematicRectangleShape(game, 124, 135, 0, 0);
  auto player = new Proto1PlayerEntity(game, playerTex, playerShape, 5.0, upPressed, downPressed, leftPressed, rightPressed, spacePressed);
  float offsetY = -(cam->GetBounds().y / 2.0) + 80;
  player->SetTransform(sf::Transform().translate(0, offsetY));

  auto enemyShape = getEnemyShape(game);
  auto enemy = new EnemyEntity(game, enemyTex, enemyShape);
  enemy->SetTransform(sf::Transform().translate(800, 1800).rotate(180));

  auto enemy2 = new EnemyEntity(game, enemyTex, enemyShape->CopyTemplate());
  enemy2->SetTransform(sf::Transform().translate(1100, 1600).rotate(180));

  auto enemy3 = new EnemyEntity(game, enemyTex, enemyShape->CopyTemplate());
  enemy3->SetTransform(sf::Transform().translate(1400, 1400).rotate(180));

  auto enemy4 = new EnemyEntity(game, enemyTex, enemyShape->CopyTemplate());
  enemy4->SetTransform(sf::Transform().translate(800, 2100).rotate(180));

  auto enemy5 = new EnemyEntity(game, enemyTex, enemyShape->CopyTemplate());
  enemy5->SetTransform(sf::Transform().translate(1100, 2400).rotate(180));

  auto enemy6 = new EnemyEntity(game, enemyTex, enemyShape->CopyTemplate());
  enemy6->SetTransform(sf::Transform().translate(1400, 2700).rotate(180));

  auto enemy7 = new EnemyEntity(game, enemyTex, enemyShape->CopyTemplate());
  enemy7->SetTransform(sf::Transform().translate(1100, 3000).rotate(180));

  // Layout entities in scene
  auto scene = new SceneGraph(game);
  int camId = scene->AddEntity(cam);
  scene->AddEntity(player, camId);
  scene->AddEntity(enemy);
  scene->AddEntity(enemy2);
  scene->AddEntity(enemy3);
  scene->AddEntity(enemy4);
  scene->AddEntity(enemy5);
  scene->AddEntity(enemy6);
  scene->AddEntity(enemy7);
  game->SetScene(scene);

  game->GetAudioController()->PlayRepeated(AssetManager::GetAudio("res/audio/tgfcoder/FrozenJam.oga"));

  game->Run();
  return 0;
}