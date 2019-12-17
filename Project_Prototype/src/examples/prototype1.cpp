#include <examples.h>

using namespace game;
using namespace std;
using namespace sf;

using Key = sf::Keyboard::Key;

// Type of player entity
const int _PLAYER_TYPE = 200;
const int _ENEMY_TYPE = 300;
const int _CAM_TYPE = 500;

const int _DESCTRUCTIBLE_COOLDOWN = 10;

const int _PLAYER_PROJECTILE = 800;
int _ENEMY_PROJECTILE = 900;

const int _PROJECTILE_SEQ_FRAMES = 8;

sf::Texture* _PLAYER_TEXTURE = AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_scorpio_1.png");
sf::Texture* _OVERLAY_HEART_TEXTURE = AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_am_overlay_1.png");

std::vector<sf::Texture*> _PROJECTILE_GREEN = {
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green1.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green2.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green3.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green4.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green5.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/green6.png"),
};

std::vector<sf::Texture*> _PROJECTILE_AM_RED = {
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red1.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red2.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red3.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red4.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red5.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_red6.png"),
};

std::vector<sf::Texture*> _PROJECTILE_AM_YELLOW = {
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_yellow1.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_yellow2.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_yellow3.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_yellow4.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_yellow5.png"),
    AssetManager::GetTexture("res/textures/projectiles/rawdanitsu/am_yellow6.png"),
};

sf::Texture* _ENEMY_TEX = AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_scorpio_6B.png");
sf::Texture* _ENEMY_BUSTER_TEX = AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_scorpio_12B.png");

sf::SoundBuffer* _SOUND_HIT_HURT_2 = AssetManager::GetAudio("res/audio/Hit_Hurt2.wav");

sf::SoundBuffer* _SOUND_EXPLOSION = AssetManager::GetAudio("res/audio/Explosion.wav");

sf::SoundBuffer* _SOUND_PLAYER_SHOOT = AssetManager::GetAudio("res/audio/Laser_Shoot.wav");

sf::SoundBuffer* _SOUND_ENEMY_SHOOT = AssetManager::GetAudio("res/audio/Laser_Shoot.wav");

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

struct SequenceTransformElement {
  sf::Transform Transform;
  int Frames = 1;
};

template <class TEntity>
class SequenceTransformBehaviour {
public:
  SequenceTransformBehaviour(TEntity* base) : mBase(base) {}

  void SetSequenceTransform(vector<SequenceTransformElement> sequenceTransform, unsigned int start = 0, bool repeat = false) {
    mSequenceTransform = sequenceTransform;
    mCurIdx = start;
    mRepeat = repeat;
  }

  void OnTick() {
    if(!mSequenceTransform.size()) return;

    auto cur = mSequenceTransform[mCurIdx];
    if(mCurFrame++ > cur.Frames) {
      mCurFrame = 0;
      if(mCurIdx < mSequenceTransform.size() - 1) {
        mCurIdx++;
      } else if(mRepeat) {
        mCurIdx = 0;
      } else {
        mFinished = true;
      }
    }
    if(!mFinished) mBase->Transform(mSequenceTransform[mCurIdx].Transform);
  }

protected:
  TEntity* mBase = nullptr;
  vector<SequenceTransformElement> mSequenceTransform = vector<SequenceTransformElement>();
  bool mRepeat = false;
  bool mFinished = false;
  unsigned int mCurIdx = 0;
  int mCurFrame = 0;
};

template <class TEntity>
class PlayerMoveBehaviour {
public:
  PlayerMoveBehaviour(TEntity* base, float speed, Key forward, Key backward, Key left, Key right) : mBase(base), mSpeed(speed), mForward(forward), mBackward(backward), mLeft(left), mRight(right) {
    cout << "PlayerMove Constructor" << endl;
  }

  void OnTick() {
    if(sf::Keyboard::isKeyPressed(mForward)) {
      mDt.y += mSpeed;
    }
    if(sf::Keyboard::isKeyPressed(mBackward)) {
      mDt.y -= mSpeed;
    }
    if(sf::Keyboard::isKeyPressed(mLeft)) {
      mDt.x -= mSpeed;
    }
    if(sf::Keyboard::isKeyPressed(mRight)) {
      mDt.x += mSpeed;
    }

    if(mDt.x != 0 || mDt.y != 0) {
      mBase->OnMove(mDt);
    }
    mDt = sf::Vector2f();
  }

protected:
  TEntity* mBase = nullptr;
  float mSpeed = 0;
  Key mForward, mBackward, mLeft, mRight;

  sf::Vector2f mDt;
};

template <class TEntity>
class DestructibleBehaviour {
public:
  DestructibleBehaviour(GameBase* game, TEntity* base, SingleSpriteRenderStrategy* renderer, sf::SoundBuffer* hitSound, int hp = 1, int coolDown = 10) : mGame(game), mBase(base), mRenderer(renderer), mHitSound(hitSound), mHp(hp), mCooldown(coolDown), mLastHit(coolDown) {
  }

  bool IsDestroyed() {
    return mDestroyed;
  }

  int GetHp() {
    return mHp;
  }

  void OnTick() {
    hitBehaviour();
    glowBehaviour();
    if(mDestroyed) mBase->OnDestroy();
  }

  void OnHit(int hpLoss) {
    mHpLoss = hpLoss;
  }

protected:
  GameBase* mGame = nullptr;
  TEntity* mBase = nullptr;
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

template <class TEntity>
class DespawnTimeoutBehaviour {
public:
  DespawnTimeoutBehaviour(GameBase* game, TEntity* base, int timeout = -1) : mGame(game), mBase(base), mTimeout(timeout) {
  }

  void OnTick() {
    if(mTimeout == -1) return;
    if(++mCounter > mTimeout) {
      mGame->GetStateManager()->DestroyObject(mBase);
      mGame->GetStateManager()->DestroyVisualObject(mBase);
    }
  }

protected:
  GameBase* mGame = nullptr;
  TEntity* mBase = nullptr;
  int mTimeout = 0;
  int mCounter = 0;
};

template <class TEntity, int ID = 1>
class RepeatedShootBehaviour {
public:
  RepeatedShootBehaviour(GameBase* game, TEntity* base, int projectileType, std::vector<sf::Texture*> sequence, sf::SoundBuffer* shootSound, KinematicShape* shape, std::vector<sf::Vector2f> offsets, std::vector<sf::Vector2f> velocity, int seqFrames, int shootIntervall = 100, int maxLifetime = 300, int shootDelay = 0) : mGame(game), mBase(base), mType(projectileType), mSequence(sequence), mShootSound(shootSound), mShape(shape), mOffsets(offsets), mVelocity(velocity), mSeqFrames(seqFrames), mShootIntervall(shootIntervall), mMaxLifetime(maxLifetime), mShootDelay(shootDelay) {
  }

  void Shoot() {
    for(unsigned int i = 0; i < mOffsets.size(); i++) {
      new SequencedProjectile(mGame, mType, mSequence, mShape->CopyTemplate(), mBase->GetCombinedTransform().translate(mOffsets[i]), mVelocity[i % mVelocity.size()], mMaxLifetime, mSeqFrames);
    }
    if(mShootSound) mGame->GetAudioController()->PlayOnce(mShootSound);
  }

  void OnTick() {
    if(mShootDelay > 0) {
      mShootDelay--;
      return;
    }
    if(mTimeLastShot++ > mShootIntervall) {
      Shoot();
      mTimeLastShot = 0;
    }
  }

protected:
  GameBase* mGame = nullptr;
  TEntity* mBase = nullptr;
  int mType = 0;
  std::vector<sf::Texture*> mSequence;
  sf::SoundBuffer* mShootSound = nullptr;
  KinematicShape* mShape = nullptr;
  std::vector<sf::Vector2f> mOffsets;
  std::vector<sf::Vector2f> mVelocity;
  int mSeqFrames = 1;
  int mShootIntervall = 100;
  int mMaxLifetime = 300;
  int mShootDelay = 0;

  int mTimeLastShot = 0;
};

template <class TEntity, int ID = 1>
class PlayerShootBehaviour {
public:
  PlayerShootBehaviour(GameBase* game, TEntity* base, Key key, int projectileType, std::vector<sf::Texture*> sequence, sf::SoundBuffer* shootSound, KinematicShape* shape, std::vector<sf::Vector2f> offsets, std::vector<sf::Vector2f> velocity, int seqFrames, int shootIntervall = 100, int maxLifetime = 300) : mGame(game), mBase(base), mKey(key), mType(projectileType), mSequence(sequence), mShootSound(shootSound), mShape(shape), mOffsets(offsets), mVelocity(velocity), mSeqFrames(seqFrames), mShootIntervall(shootIntervall), mMaxLifetime(maxLifetime) {
  }

  void Shoot() {
    for(unsigned int i = 0; i < mOffsets.size(); i++) {
      new SequencedProjectile(mGame, mType, mSequence, mShape->CopyTemplate(), mBase->GetCombinedTransform().translate(mOffsets[i]), mVelocity[i % mVelocity.size()], mMaxLifetime, mSeqFrames);
    }
    if(mShootSound) mGame->GetAudioController()->PlayOnce(mShootSound);
  }

  void OnTick() {
    mTimeLastShot++;
    if(sf::Keyboard::isKeyPressed(mKey) && mTimeLastShot > mShootIntervall) {
      Shoot();
      mTimeLastShot = 0;
    }
  }

protected:
  GameBase* mGame = nullptr;
  TEntity* mBase = nullptr;
  Key mKey;
  int mType = 0;
  std::vector<sf::Texture*> mSequence;
  sf::SoundBuffer* mShootSound = nullptr;
  KinematicShape* mShape = nullptr;
  std::vector<sf::Vector2f> mOffsets;
  std::vector<sf::Vector2f> mVelocity;
  int mSeqFrames = 1;
  int mShootIntervall = 100;
  int mMaxLifetime = 300;

  int mTimeLastShot = 0;
};

class GameController {
public:
  GameController(GameBase* game) : mGame(game) {
  }

  void InitOverlay() {
    auto h = mGame->GetOptions().ScreenDim.y;

    auto font = new sf::Font();
    font->loadFromFile("res/fonts/Press_Start_2P/PressStart2P-Regular.ttf");
    mText = new sf::Text("Score: 000000", *font, 20);
    mText->setStyle(sf::Text::Bold);
    mText->setFillColor(sf::Color::Red);
    mText->setOutlineColor(sf::Color::Red);
    mText->setPosition(730, h - 35);

    mGameOver = new sf::Text("Game Over!", *font, 64);
    mGameOver->setOrigin(mGameOver->getLocalBounds().width / 2, mGameOver->getLocalBounds().height / 2);
    mGameOver->setStyle(sf::Text::Bold);
    mGameOver->setFillColor(sf::Color::Red);
    mGameOver->setOutlineColor(sf::Color::Red);
    mGameOver->setPosition(512, h / 2);

    for(unsigned i = 0; i < mHearts.size(); i++) {
      auto sprite = new sf::Sprite(*_OVERLAY_HEART_TEXTURE);
      // sprite->setPosition(15 + (i * 45), 10);
      sprite->setPosition(15 + (i * 45), h - 42);
      mHearts[i] = sprite;
    }

    auto overlay = mGame->GetOverlayDisplay();
    overlay->AddElement(mText);
    mGameOverId = overlay->AddElement(mGameOver, false);

    for(unsigned i = 0; i < mHearts.size(); i++) {
      mHeartIds[i] = overlay->AddElement(mHearts[i]);
    }
  }

  int GetScore() {
    return mScore;
  }

  void AddScore(int score) {
    mScore += score;
    stringstream ss;
    ss << "Score: " << setfill('0') << setw(6) << mScore;
    mText->setString(ss.str());
    mGame->GetOverlayDisplay()->Update();
  }

  void SetHeartCount(int count) {
    if(mHeartCount == count) return;
    mHeartCount = count;
    for(int i = 0; i < mHearts.size(); i++) {
      if(mHeartCount > i) {
        mGame->GetOverlayDisplay()->Enable(mHeartIds[i]);
      } else {
        mGame->GetOverlayDisplay()->Disable(mHeartIds[i]);
      }
    }
  }

  void GameOver() {
    mGame->GetOverlayDisplay()->Enable(mGameOverId);
  }

protected:
  int mScore = 0;
  sf::Text* mText = nullptr;
  sf::Text* mGameOver = nullptr;
  int mGameOverId = 0;
  GameBase* mGame = nullptr;
  int mHeartCount = 3;
  std::vector<sf::Sprite*> mHearts = std::vector<sf::Sprite*>(3);
  std::vector<int> mHeartIds = std::vector<int>(3);
};

GameController* getGameController(GameBase* game) {
  static GameController* ret = nullptr;
  if(ret == nullptr) {
    ret = new GameController(game);
  }
  return ret;
}

class Proto1PlayerEntity : public SpriteKinematicEntity,
                           public DestructibleBehaviour<Proto1PlayerEntity>,
                           public PlayerMoveBehaviour<Proto1PlayerEntity>,
                           public PlayerShootBehaviour<Proto1PlayerEntity> {
public:
  Proto1PlayerEntity(GameBase* game,
                     sf::Texture* texture,
                     KinematicShape* shape,
                     float speed,
                     Observable<sf::Keyboard::Key>* space)
      //////////////////////////////////////////////////////////////////////////
      : SpriteKinematicEntity(_PLAYER_TYPE,
                              game,
                              texture,
                              {shape},
                              true),
        DestructibleBehaviour(game,
                              this,
                              mSpriteRenderer,
                              _SOUND_HIT_HURT_2,
                              3,
                              _DESCTRUCTIBLE_COOLDOWN),
        PlayerMoveBehaviour(this,
                            speed,
                            sf::Keyboard::Up,
                            sf::Keyboard::Down,
                            sf::Keyboard::Left,
                            sf::Keyboard::Right),
        PlayerShootBehaviour(game,
                             this,
                             sf::Keyboard::Space,
                             _PLAYER_PROJECTILE,
                             _PROJECTILE_GREEN,
                             _SOUND_PLAYER_SHOOT,
                             ShapeFactory::CreateKinematicCircleShape(game, 5, 0, 0),
                             {sf::Vector2f(0, 80)},
                             {sf::Vector2f(0, 600)},
                             8,
                             45,
                             80) {
    mSize = sf::Vector2f(texture->getSize().x, texture->getSize().y);
  }

  ~Proto1PlayerEntity() {
  }

  void OnTick() {
    DestructibleBehaviour::OnTick();
    PlayerMoveBehaviour::OnTick();
    PlayerShootBehaviour::OnTick();
    getGameController(getGame())->SetHeartCount(GetHp());
  }

  void OnMove(sf::Vector2f dt) {
    auto transform = GetTransform();
    auto bottomLeft = transform.transformPoint(sf::Vector2f(-mSize.x / 2, -mSize.y / 2));
    auto topRight = transform.transformPoint(sf::Vector2f(mSize.x / 2, mSize.y / 2));
    auto camBounds = getGame()->GetCameraController()->GetBounds();

    if(bottomLeft.x + dt.x < -camBounds.x / 2) {
      dt.x = -(camBounds.x / 2) - bottomLeft.x;
    } else if(topRight.x + dt.x > camBounds.x / 2) {
      dt.x = camBounds.x / 2 - topRight.x;
    }

    if(bottomLeft.y + dt.y < -camBounds.y / 2) {
      dt.y = -(camBounds.y / 2) - bottomLeft.y;
    } else if(topRight.y + dt.y > camBounds.y / 2) {
      dt.y = camBounds.y / 2 - topRight.y;
    }

    SetTransform(transform * sf::Transform().translate(dt));
  }

  int OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb) {
    OnHit(1);
    return 0;
  }

  int OnProjectileCollision(CollisionEventType type, Projectile* projectile, cpArbiter* arb) {
    if(projectile->GetType() == _ENEMY_PROJECTILE) {
      OnHit(1);
    }
    return 0;
  }

  void OnDestroy() {
    if(!mDestroying) {
      new Effect(getGame(), _EXPLOSION1, GetCombinedTransform());

      getGame()->GetStateManager()->DestroyObject(this);
      getGame()->GetStateManager()->DestroyVisualObject(this);
      getGame()->GetAudioController()->PlayOnce(_SOUND_EXPLOSION);
      getGameController(getGame())->GameOver();
      mDestroying = true;
    }
  }

private:
  sf::Vector2f mSize;
  bool mDestroying = false;
};

class EnemyEntity : public SpriteKinematicEntity,
                    public DestructibleBehaviour<EnemyEntity>,
                    public SequenceTransformBehaviour<EnemyEntity>,
                    public RepeatedShootBehaviour<EnemyEntity>,
                    public DespawnTimeoutBehaviour<EnemyEntity> {
public:
  EnemyEntity(GameBase* game,
              sf::Texture* texture,
              KinematicShape* shape,
              int hp,
              std::vector<sf::Texture*> projectileSequence,
              KinematicShape* projectileShape,
              std::vector<sf::Vector2f> projectileOffsets,
              std::vector<sf::Vector2f> projectileVelocity,
              int score = 100,
              int projectileLifetime = 300,
              int shootInterval = 150,
              int shootDelay = 0,
              int despawnTimeout = -1)
      //////////////////////////////////////////////////////////////////////////
      : SpriteKinematicEntity(_ENEMY_TYPE, game, texture, {shape}, true),
        DestructibleBehaviour(game, this, mSpriteRenderer, _SOUND_HIT_HURT_2, hp, _DESCTRUCTIBLE_COOLDOWN),
        SequenceTransformBehaviour(this),
        RepeatedShootBehaviour(game, this, _ENEMY_PROJECTILE, projectileSequence, _SOUND_ENEMY_SHOOT, projectileShape, projectileOffsets, projectileVelocity, _PROJECTILE_SEQ_FRAMES, shootInterval, projectileLifetime, shootDelay),
        DespawnTimeoutBehaviour(game, this, despawnTimeout), mScore(score){};

  int OnProjectileCollision(CollisionEventType type, Projectile* projectile, cpArbiter* arb) {
    if(projectile->GetType() == _PLAYER_PROJECTILE) {
      OnHit(1);
    }
    return 0;
  }

  void OnDestroy() {
    if(!mDestroying) {
      if(GetHp() < 1) {
        getGameController(getGame())->AddScore(mScore);
      }
      cout << GetId() << " Before create explosion" << endl;
      auto explosion = new Effect(getGame(), _EXPLOSION1, GetCombinedTransform());
      cout << GetId() << " After create explosion" << endl;

      getGame()->GetStateManager()->DestroyObject(this);
      getGame()->GetStateManager()->DestroyVisualObject(this);
      getGame()->GetAudioController()->PlayOnce(_SOUND_EXPLOSION);
      mDestroying = true;
    }
  }

  void OnTick() {
    DestructibleBehaviour::OnTick();
    SequenceTransformBehaviour::OnTick();
    RepeatedShootBehaviour::OnTick();
    DespawnTimeoutBehaviour::OnTick();
  }

private:
  bool mDestroying = false;
  int mScore = 100;
};

PolygonShape<KinematicShapeDefinition>* getEnemyShape(GameBase* game) {
  static PolygonShape<KinematicShapeDefinition>* ret = nullptr;
  if(ret == nullptr) {
    auto verts = vector<cpVect>();
    verts.push_back(cpv(-85, -31));
    verts.push_back(cpv(84, -31));
    verts.push_back(cpv(76, -5));
    verts.push_back(cpv(0, 49));
    verts.push_back(cpv(-1, 49));
    verts.push_back(cpv(-77, -5));
    ret = ShapeFactory::CreateKinematicPolygonShape(game, verts, 0, 0);
  }
  return ret;
}

PolygonShape<KinematicShapeDefinition>* getBusterShape(GameBase* game) {
  static PolygonShape<KinematicShapeDefinition>* ret = nullptr;
  if(ret == nullptr) {
    auto verts = vector<cpVect>();
    verts.push_back(cpv(-135.0, -11));
    verts.push_back(cpv(-64.0, -21));
    verts.push_back(cpv(-63.0, -43));
    verts.push_back(cpv(62.0, -43));
    verts.push_back(cpv(64.0, -21));
    verts.push_back(cpv(134.0, -11));
    verts.push_back(cpv(10.0, 36));
    verts.push_back(cpv(-11, 36));
    ret = ShapeFactory::CreateKinematicPolygonShape(game, verts, 0, 0);
  }
  return ret;
}

PolygonShape<KinematicShapeDefinition>* getPlayerShape(GameBase* game) {
  static PolygonShape<KinematicShapeDefinition>* ret = nullptr;
  auto verts = vector<cpVect>();
  if(ret == nullptr) {
    verts.push_back(cpv(-62, -27.5));
    verts.push_back(cpv(61, -27.5));
    verts.push_back(cpv(61, 21.5));
    verts.push_back(cpv(4, 67.5));
    verts.push_back(cpv(-5, 67.5));
    verts.push_back(cpv(-62, 21.5));
    ret = ShapeFactory::CreateKinematicPolygonShape(game, verts, 0, 0);
  }
  return ret;
}

vector<SequenceTransformElement> createLeftRightSequence(int speed, int ticks, bool invert = false) {
  auto ret = vector<SequenceTransformElement>();
  ret.push_back({sf::Transform().translate(invert ? speed : -speed, 0), ticks});
  ret.push_back({sf::Transform().translate(invert ? speed : -speed, 0), ticks});
  ret.push_back({sf::Transform().translate(invert ? -speed : speed, 0), ticks});
  ret.push_back({sf::Transform().translate(invert ? -speed : speed, 0), ticks});
  return ret;
}

class GliderEnemyEntity : public EnemyEntity {
public:
  GliderEnemyEntity(GameBase* game,
                    int shootInterval = 150,
                    int shootDelay = 0,
                    int despawnTimeout = -1)
      : EnemyEntity(game,
                    _ENEMY_TEX,
                    getEnemyShape(game)->CopyTemplate(),
                    3,
                    _PROJECTILE_AM_RED,
                    ShapeFactory::CreateKinematicCircleShape(game, 5, 0, 0),
                    {sf::Vector2f(-15, 60), sf::Vector2f(15, 60)},
                    {sf::Vector2f(0, -300)},
                    100,
                    300,
                    shootInterval,
                    shootDelay,
                    despawnTimeout) {}
};

class BusterEnemyEntity : public EnemyEntity {
public:
  BusterEnemyEntity(GameBase* game,
                    int shootInterval = 150,
                    int shootDelay = 0)
      : EnemyEntity(game,
                    _ENEMY_BUSTER_TEX,
                    getBusterShape(game)->CopyTemplate(),
                    5,
                    _PROJECTILE_AM_YELLOW,
                    ShapeFactory::CreateKinematicCircleShape(game, 5, 0, 0),
                    {sf::Vector2f(-60, 60),
                     sf::Vector2f(-30, 60),
                     sf::Vector2f(0, 60),
                     sf::Vector2f(30, 60),
                     sf::Vector2f(60, 60)},
                    {sf::Vector2f(40, -200),
                     sf::Vector2f(20, -200),
                     sf::Vector2f(0, -200),
                     sf::Vector2f(-20, -200),
                     sf::Vector2f(-40, -200)},
                    500,
                    300,
                    shootInterval,
                    shootDelay) {}
};

void spawnHorizontalGlider(GameBase* game, sf::Vector2f pos, int time = 100, bool invert = false, int shootDelay = 0, int despawnTimeout = -1) {
  cout << "Spawning Horizontal Glider" << endl;
  auto glider = new GliderEnemyEntity(game, 150, shootDelay, despawnTimeout);
  glider->SetTransform(sf::Transform().translate(pos).rotate(180));
  glider->SetSequenceTransform(createLeftRightSequence(2, time, invert), 1, true);
  game->GetScene()->AddEntity(glider);
}

void spawnImmobileBuster(GameBase* game, sf::Vector2f pos, int shootDelay = 0) {
  cout << "Spawning Immobile Buster" << endl;
  auto glider = new BusterEnemyEntity(game, 300, shootDelay);
  glider->SetTransform(sf::Transform().translate(pos).rotate(180));
  game->GetScene()->AddEntity(glider);
}

class ScrollCamera : public DefaultCameraController, public Entity {
public:
  ScrollCamera(GameBase* game) : DefaultCameraController(game), Entity(_CAM_TYPE, game) {
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

class SpawnSequencer : public GameObject {
public:
  SpawnSequencer(GameBase* game) : GameObject(ObjectType::Unknown, game) {
    mTriggers.push(300);
    mTriggers.push(400);
    mTriggers.push(1300);
    mTriggers.push(1600);
  }

  void OnTick() {
    if(mCounter++ == mCurTrigger) {
      OnTrigger();
      if(mTriggers.size() > 0) {
        mCurTrigger = mTriggers.front();
        mTriggers.pop();
      };
    }
  }

  void OnTrigger() {
    auto game = getGame();
    switch(mCurTrigger) {
    case 300:
      spawnHorizontalGlider(game, sf::Vector2f(500, 1500), 100, false, 20, 1500);
      spawnHorizontalGlider(game, sf::Vector2f(1548, 1500), 100, true, 20, 1500);
      break;
    case 400:
      spawnHorizontalGlider(game, sf::Vector2f(1024, 1700), 50, true, 20, 1500);
      break;
    case 1300:
      spawnHorizontalGlider(game, sf::Vector2f(500, 2500), 50, false, 20, 1500);
      spawnHorizontalGlider(game, sf::Vector2f(1548, 2500), 50, true, 20, 1500);
      spawnHorizontalGlider(game, sf::Vector2f(700, 2700), 50, false, 20, 1500);
      spawnHorizontalGlider(game, sf::Vector2f(1348, 2700), 50, true, 20, 1500);
      break;
    case 1600:
      spawnImmobileBuster(game, sf::Vector2f(1024, 3000), 20);
    default:
      break;
    }
  }

private:
  int mCounter = 0;
  int mCurTrigger = 0;
  queue<int> mTriggers;
};

int prototype1() {
  // Create Keyboard Events
  auto spacePressed = new OnKeyPress(sf::Keyboard::Space);

  float aspectRatio = (float)sf::VideoMode::getDesktopMode().width / (float)sf::VideoMode::getDesktopMode().height;

  // Create game
  auto options = GameOptions{"Arcade Shooter Prototype", sf::Vector2i(1024, 1024 / aspectRatio), 0.5, 60, false, false};
  auto game = new Game(options);

  // Send Events to controller
  game->AddEvent(spacePressed);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/proto1/tilemap.json", "", "res/maps/proto1/tile_");
  game->SetWorld(world);

  auto cam = new ScrollCamera(game);
  cam->SetScroll(sf::Vector2f(0, 0.5));
  game->SetCameraController(cam);

  // auto enemyTex2 = AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_am_1B.png");
  auto playerShape = getPlayerShape(game);
  // auto playerShape = ShapeFactory::CreateKinematicRectangleShape(game, 124, 135, 0, 0);
  cout << "Creating Player" << endl;
  auto player = new Proto1PlayerEntity(game, _PLAYER_TEXTURE, playerShape, 5.0, spacePressed);
  cout << "After create Player" << endl;
  float offsetY = -(cam->GetBounds().y / 2.0) + 80;
  player->SetTransform(sf::Transform().translate(0, offsetY));

  cout << "Creating Scene Graph" << endl;
  // Layout entities in scene
  auto scene = new SceneGraph(game);
  int camId = scene->AddEntity(cam);
  scene->AddEntity(player, camId);
  game->SetScene(scene);

  cout << "Creating Gliders" << endl;

  cout << "After Glider spawn" << endl;

  game->GetAudioController()->PlayRepeated(AssetManager::GetAudio("res/audio/tgfcoder/FrozenJam.oga"));

  auto ctrl = getGameController(game);

  auto overlay = new OverlayDisplay(game);
  game->SetOverlayDisplay(overlay);

  ctrl->InitOverlay();

  game->GetStateManager()->AddObject(new SpawnSequencer(game));

  game->Run();
  return 0;
}