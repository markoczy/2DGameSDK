#include <examples.h>

namespace proto2 {

  //************************* TYPEDEF / USING / HELPER  ***********************/

  using namespace game;
  using namespace std;
  using namespace sf;

  using Key = sf::Keyboard::Key;
  using KinematicShape = game::Shape<KinematicShapePhysics>;
  using DynamicShape = game::Shape<DynamicShapePhysics>;

  //***************************************************************************/

  //************************* CONSTANTS / PRELOADED ASSETS ********************/

  //*
  //* CONSTANTS
  //*---------------------------------------------------------------------------

  const int _NPC_TYPE = 100;
  const int _PLAYER_TYPE = 200;

  const float _WALK_SPEED = 3;
  const float _RUN_SPEED = 7;

  enum class Direction {
    DEFAULT = -1,
    UP = 0,
    RIGHT = 1,
    LEFT = 2,
    DOWN = 3
  };

  enum class IdleAnim {
    UP = 10,
    RIGHT = 7,
    LEFT = 4,
    DOWN = 1
  };

  std::vector<int> WalkDownAnim = {0, 1, 2};
  std::vector<int> WalkLeftAnim = {3, 4, 5};
  std::vector<int> WalkRightAnim = {6, 7, 8};
  std::vector<int> WalkUpAnim = {9, 10, 11};

  std::vector<string> _DIALOGS = {
      "Hello Player",
      "What's up?",
      "Wanna go\non a quest?"};

  //*
  //* ASSETS
  //*---------------------------------------------------------------------------

  sf::Texture* _PLAYER_TEXTURE = AssetManager::GetTexture("res/textures/rpghero/hero_10.png");

  std::map<int, sf::Texture*> _PLAYER_ANIM = {
      {0, AssetManager::GetTexture("res/textures/rpghero/hero_00.png")},
      {1, AssetManager::GetTexture("res/textures/rpghero/hero_01.png")},
      {2, AssetManager::GetTexture("res/textures/rpghero/hero_02.png")},
      {3, AssetManager::GetTexture("res/textures/rpghero/hero_03.png")},
      {4, AssetManager::GetTexture("res/textures/rpghero/hero_04.png")},
      {5, AssetManager::GetTexture("res/textures/rpghero/hero_05.png")},
      {6, AssetManager::GetTexture("res/textures/rpghero/hero_06.png")},
      {7, AssetManager::GetTexture("res/textures/rpghero/hero_07.png")},
      {8, AssetManager::GetTexture("res/textures/rpghero/hero_08.png")},
      {9, AssetManager::GetTexture("res/textures/rpghero/hero_09.png")},
      {10, AssetManager::GetTexture("res/textures/rpghero/hero_10.png")},
      {11, AssetManager::GetTexture("res/textures/rpghero/hero_11.png")}};

  std::map<int, sf::Texture*> _GIRL_ANIM = {
      {0, AssetManager::GetTexture("res/textures/rpggirl/girl_00.png")},
      {1, AssetManager::GetTexture("res/textures/rpggirl/girl_01.png")},
      {2, AssetManager::GetTexture("res/textures/rpggirl/girl_02.png")},
      {3, AssetManager::GetTexture("res/textures/rpggirl/girl_03.png")},
      {4, AssetManager::GetTexture("res/textures/rpggirl/girl_04.png")},
      {5, AssetManager::GetTexture("res/textures/rpggirl/girl_05.png")},
      {6, AssetManager::GetTexture("res/textures/rpggirl/girl_06.png")},
      {7, AssetManager::GetTexture("res/textures/rpggirl/girl_07.png")},
      {8, AssetManager::GetTexture("res/textures/rpggirl/girl_08.png")},
      {9, AssetManager::GetTexture("res/textures/rpggirl/girl_09.png")},
      {10, AssetManager::GetTexture("res/textures/rpggirl/girl_10.png")},
      {11, AssetManager::GetTexture("res/textures/rpggirl/girl_11.png")}};

  sf::Font* getFont() {
    auto font = new sf::Font();
    font->loadFromFile("res/fonts/Press_Start_2P/PressStart2P-Regular.ttf");
    return font;
  }

  sf::Font* _FONT = getFont();

  sf::SoundBuffer* _MUSIC_LEVEL = AssetManager::GetAudio("res/audio/Fantasy_Musica/Town 01.ogg");
  sf::SoundBuffer* _SOUND_INTERACT = AssetManager::GetAudio("res/audio/Blip_Select.wav");
  sf::SoundBuffer* _SOUND_INTERACT_2 = AssetManager::GetAudio("res/audio/Blip_Select2.wav");

  //*
  //* SHAPES
  //*---------------------------------------------------------------------------

  DynamicShape* getHumanoidShape(GameBase* game) {
    static PolygonShape<DynamicShapePhysics>* ret = nullptr;
    if(ret == nullptr) {
      auto verts = vector<cpVect>();
      verts.push_back(cpv(-0.6, -1.2));
      verts.push_back(cpv(-0.6, -2.3));
      verts.push_back(cpv(0.5, -2.3));
      verts.push_back(cpv(0.5, -1.2));
      ret = ShapeFactory::CreateDynamicPolygonShape(game, verts, 1, 1, 0);
    }
    return ret;
  }

  //***************************************************************************/

  //************************* BEHAVIOURS (GENERIC ENTITY LOGIC) ***************/

  class Dialog : public sf::Drawable {
  public:
    Dialog() : mText("", *_FONT, 20), mRect(sf::RectangleShape()) {
      mRect.setSize(sf::Vector2f(400, 200));
      mRect.setPosition(100, 100);
      mRect.setFillColor(sf::Color(50, 50, 255, 200));
      mRect.setOutlineColor(sf::Color(0, 0, 0, 200));
      mRect.setOutlineThickness(5);

      mText.setPosition(110, 110);
      mText.setFillColor(sf::Color(255, 255, 255, 200));
    }

    void SetText(string text) {
      mText.setString(text);
    }

  protected:
    sf::Text mText;
    sf::RectangleShape mRect;

    // Override Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
      target.draw(mRect, states);
      target.draw(mText, states);
    }
  };

  template <class TEntity>
  class AnimatedMoveBehaviour {
  public:
    AnimatedMoveBehaviour(TEntity* base, float speed) : mBase(base), mSpeed(speed), mIncr(speed / 10) {}

    void UpdateMove(cpVect dv) {
      if(mIsImmobile) {
        dv = cpv(0, 0);
      }

      auto dir = Direction::DEFAULT;
      if(dv.x > 0) {
        dir = Direction::RIGHT;
      } else if(dv.x < 0) {
        dir = Direction::LEFT;
      }
      if(dv.y > 0) {
        dir = Direction::UP;
      } else if(dv.y < 0) {
        dir = Direction::DOWN;
      }
      if(dir != Direction::DEFAULT) {
        mLastDirection = dir;
      }

      if(dv.x || dv.y) {
        cpVect curV = mBase->GetVelocity();
        dv = cpv(curV.x + (dv.x * mIncr), curV.y + (dv.y * mIncr));

        // throttle speed if necessary
        float len = cpvlength(dv);
        if(len > mSpeed) {
          float f = mSpeed / len;
          dv = cpv(dv.x * f, dv.y * f);
        }

        mBase->SetVelocity(dv);
        setWalkingPos();
      } else {
        mCurFrame = 0;
        mCurWalkAnim = 0;
        mBase->SetVelocity(cpv(0, 0));
        setIdlePos();
      }
    }

    void SetDirection(Direction dir) {
      mLastDirection = dir;
    }

    void SetImmobile(bool isImmobile) {
      mIsImmobile = isImmobile;
    }

  protected:
    TEntity* mBase = nullptr;
    float mSpeed = 0;
    float mIncr = 0;
    Direction mLastDirection = Direction::UP;
    int mCurFrame = 0;
    int mCurWalkAnim = 0;
    bool mIsImmobile = false;
    vector<int> mAnim;

    void setIdlePos() {
      switch(mLastDirection) {
      case Direction::UP:
        mBase->SetAnimState((int)IdleAnim::UP);
        break;
      case Direction::RIGHT:
        mBase->SetAnimState((int)IdleAnim::RIGHT);
        break;
      case Direction::DOWN:
        mBase->SetAnimState((int)IdleAnim::DOWN);
        break;
      case Direction::LEFT:
        mBase->SetAnimState((int)IdleAnim::LEFT);
        break;
      default:
        break;
      };
    }

    void setWalkingPos() {
      switch(mLastDirection) {
      case Direction::UP:
        mAnim = WalkUpAnim;
        break;
      case Direction::RIGHT:
        mAnim = WalkRightAnim;
        break;
      case Direction::DOWN:
        mAnim = WalkDownAnim;
        break;
      case Direction::LEFT:
        mAnim = WalkLeftAnim;
        break;
      default:
        break;
      };

      if(++mCurFrame > 10) {
        mCurFrame = 0;
        mCurWalkAnim = (mCurWalkAnim + 1) % mAnim.size();
      }
      mBase->SetAnimState(mAnim[mCurWalkAnim]);
    }
  };

  template <class TEntity>
  class PlayerMoveBehaviour : public AnimatedMoveBehaviour<TEntity> {
  public:
    PlayerMoveBehaviour(TEntity* base, float speed, Key forward, Key backward, Key left, Key right) : AnimatedMoveBehaviour<TEntity>(base, speed), mForward(forward), mBackward(backward), mLeft(left), mRight(right) {}

    void OnTick() {
      auto dv = cpv(0, 0);

      if(sf::Keyboard::isKeyPressed(mLeft)) {
        dv.x -= 1;
      }
      if(sf::Keyboard::isKeyPressed(mRight)) {
        dv.x += 1;
      }
      if(sf::Keyboard::isKeyPressed(mForward)) {
        dv.y += 1;
      }
      if(sf::Keyboard::isKeyPressed(mBackward)) {
        dv.y -= 1;
      }

      AnimatedMoveBehaviour<TEntity>::UpdateMove(dv);
    }

  protected:
    Key mForward, mBackward, mLeft, mRight;
  };

  template <class TEntity>
  class RandomMoveBehaviour : public AnimatedMoveBehaviour<TEntity> {
  public:
    RandomMoveBehaviour(TEntity* base, float speed) : AnimatedMoveBehaviour<TEntity>(base, speed) {}

    void OnTick() {
      if(mCurTick > mTicks) {
        mLastMove++;
        if(mLastMove > rand() % 15000) {
          mTicks = rand() % 30;
          mDv.x = rand() % 3 - 1;
          mDv.y = rand() % 3 - 1;
          mCurTick = 0;
          mLastMove = 0;
          this->UpdateMove(mDv);
        } else {
          this->UpdateMove(cpv(0, 0));
        }
      } else {
        mCurTick++;
        this->UpdateMove(mDv);
      }
    }

  protected:
    cpVect mDv;
    int mTicks = 0;
    int mCurTick = 0;
    int mLastMove = 0;
  }; // namespace proto2

  int getHumanZIndex(GameBase* game, cpVect pos) {
    auto worlBounds = game->GetWorld()->GetBounds();
    float pxToMeter = game->GetOptions().MeterPerPixel;
    float y = worlBounds.height - (pos.y / pxToMeter) + 20;
    int yTile = (10.0 * (y / 32.0)) - 10;
    return yTile;
  }

  //***************************************************************************/

  //************************* HIGH LEVEL OBJECTS ******************************/

  class PlayerEntity : public AnimatedDynamicEntity,
                       public PlayerMoveBehaviour<PlayerEntity> {
  public:
    PlayerEntity(GameBase* game)
        : AnimatedDynamicEntity(_PLAYER_TYPE,
                                game,
                                _PLAYER_ANIM,
                                {getHumanoidShape(game)},
                                true,
                                10),
          PlayerMoveBehaviour(this,
                              _RUN_SPEED,
                              sf::Keyboard::Up,
                              sf::Keyboard::Down,
                              sf::Keyboard::Left,
                              sf::Keyboard::Right) {
      // disable rotation
      SetMoment(INFINITY);
    }

    void OnTick() {
      PlayerMoveBehaviour::OnTick();
      int zIndex = getHumanZIndex(getGame(), cpBodyGetPosition(mBody));
      if(mLastZIndex != zIndex) {
        SetZIndex(zIndex);
        mLastZIndex = zIndex;
      }
    }

  protected:
    int mLastZIndex = 0;
    bool mIsImmobile = false;
  };

  class NPCEntity : public AnimatedDynamicEntity,
                    public RandomMoveBehaviour<NPCEntity> {
  public:
    NPCEntity(GameBase* game)
        : AnimatedDynamicEntity(_NPC_TYPE,
                                game,
                                _GIRL_ANIM,
                                {getHumanoidShape(game)},
                                true,
                                10),
          RandomMoveBehaviour(this,
                              _WALK_SPEED),
          mDialog(new Dialog()) {
      // disable rotation
      SetMoment(INFINITY);
      mDialogId = getGame()->GetOverlayDisplay()->AddElement(mDialog, false);
      mDialog->SetText(_DIALOGS[rand() % _DIALOGS.size()]);
    }

    void OnTick() {
      RandomMoveBehaviour::OnTick();
      int zIndex = getHumanZIndex(getGame(), cpBodyGetPosition(mBody));
      if(mLastZIndex != zIndex) {
        SetZIndex(zIndex);
        mLastZIndex = zIndex;
      }
    }

    int GetDialogId() {
      mDialog->SetText(_DIALOGS[rand() % _DIALOGS.size()]);
      return mDialogId;
    }

  protected:
    int mLastZIndex = 0;
    Dialog* mDialog = nullptr;
    int mDialogId = 0;
  };

  class GameController : public GameObject {
  public:
    GameController(GameBase* game) : GameObject(ObjectType::Unknown, game) {}

    void OnTick() {
      mCoolDown++;

      if(mCoolDown > 25 && sf::Keyboard::isKeyPressed(Key::Space)) {
        if(mOpenDialog) {
          mOpenDialog = false;
          mNPC->SetImmobile(false);
          mPlayer->SetImmobile(false);
          getGame()->GetOverlayDisplay()->Disable(mCurDialogId);
          getGame()->GetAudioController()->PlayOnce(_SOUND_INTERACT_2);
        } else {
          auto pt = mPlayer->GetCombinedTransform().transformPoint(sf::Vector2f());
          for(auto npc : mNpcs) {
            auto ptn = npc->GetCombinedTransform().transformPoint(sf::Vector2f());
            if(abs(pt.x - ptn.x) < 5 && abs(pt.y - ptn.y) < 5) {
              mCurDialogId = npc->GetDialogId();
              mOpenDialog = true;
              mNPC = npc;

              // Make npc look in player's direction
              float dx = pt.x - ptn.x;
              float dy = pt.y - ptn.y;
              Direction dir = Direction::DEFAULT;
              if(abs(dx) > abs(dy)) {
                if(dx > 0) {
                  dir = Direction::RIGHT;
                } else {
                  dir = Direction::LEFT;
                }
              } else {
                if(dy > 0) {
                  dir = Direction::UP;
                } else {
                  dir = Direction::DOWN;
                }
              }
              npc->SetDirection(dir);

              npc->SetImmobile(true);
              mPlayer->SetImmobile(true);
              getGame()->GetOverlayDisplay()->Enable(mCurDialogId);
              getGame()->GetAudioController()->PlayOnce(_SOUND_INTERACT);
            }
          }
        }
        mCoolDown = 0;
      }
    }

    void SetPlayer(PlayerEntity* player) {
      mPlayer = player;
    }

    void AddNPC(NPCEntity* npc) {
      mNpcs.push_back(npc);
    }

  protected:
    PlayerEntity* mPlayer = nullptr;
    NPCEntity* mNPC = nullptr;
    bool mOpenDialog = false;
    int mCurDialogId = -1;

    int mCoolDown = 0;

    std::vector<NPCEntity*> mNpcs;
  };

  GameController* getGameController(GameBase* game) {
    static GameController* ret = nullptr;
    if(ret == nullptr) {
      ret = new GameController(game);
    }
    return ret;
  }

  //***************************************************************************/

  int demo() {
    srand(time(NULL));
    float aspectRatio = (float)sf::VideoMode::getDesktopMode().width / (float)sf::VideoMode::getDesktopMode().height;

    // Create game
    auto options = GameOptions{"Roleplay Prototype", /* Title */
                               sf::Vector2i(1024, 1024 / aspectRatio), /* Dim */
                               2, /* Scale */
                               60, /* FPS */
                               false, /* Debug AABB */
                               false, /* Debug Shapes */
                               0.1, /* Pixel to Meter */
                               true /* Audio Enabled */};
    auto game = new Game(options);

    auto overlay = new OverlayDisplay(game);
    game->SetOverlayDisplay(overlay);

    // Create Game World
    auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/mage_city/tilemap.json", "res/maps/mage_city/materialmap.json", "res/maps/mage_city/tile_", 3);
    game->SetWorld(world);

    auto scene = new SceneGraph(game);
    game->SetScene(scene);

    auto player = new PlayerEntity(game);
    player->SetTransform(sf::Transform().translate(11, 5));
    scene->AddEntity(player);

    auto npc = new NPCEntity(game);
    npc->SetTransform(sf::Transform().translate(45, 35));
    scene->AddEntity(npc);

    auto ctrl = getGameController(game);
    ctrl->SetPlayer(player);
    ctrl->AddNPC(npc);
    game->GetStateManager()->AddObject(ctrl);

    auto cam = new BoundedFollowCameraController(game, player);
    game->SetCameraController(cam);

    auto space = game->GetPhysicalWorld();
    cpSpaceSetGravity(space, cpv(0, 0));

    game->GetAudioController()->PlayRepeated(_MUSIC_LEVEL);

    game->Run();
    return 0;
  }

} // namespace proto2

int prototype2() {
  return proto2::demo();
}