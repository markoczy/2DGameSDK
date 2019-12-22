#include <examples.h>

namespace proto2 {

  //************************* TYPEDEF / USING / HELPER  ***********************/

  using namespace game;
  using namespace std;
  using namespace sf;

  using Key = sf::Keyboard::Key;
  using KinematicShape = game::Shape<KinematicShapeDefinition>;
  using DynamicShape = game::Shape<DynamicShapeDefinition>;

  //***************************************************************************/

  //************************* CONSTANTS / PRELOADED ASSETS ********************/

  //*
  //* CONSTANTS
  //*---------------------------------------------------------------------------

  const int _PLAYER_TYPE = 200;

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

  //*
  //* SHAPES
  //*---------------------------------------------------------------------------

  DynamicShape* getPlayerShape(GameBase* game) {
    static PolygonShape<DynamicShapeDefinition>* ret = nullptr;
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

  template <class TEntity>
  class PlayerMoveBehaviour {
  public:
    PlayerMoveBehaviour(TEntity* base, float speed, Key forward, Key backward, Key left, Key right) : mBase(base), mSpeed(speed), mIncr(mSpeed / 10), mForward(forward), mBackward(backward), mLeft(left), mRight(right) {
      int i = 1;
    }

    void OnTick() {
      // Direction dir = Direction::DEFAULT;
      if(sf::Keyboard::isKeyPressed(mForward)) {
        mDv.y += mIncr;
        mLastDirection = Direction::UP;
      }
      if(sf::Keyboard::isKeyPressed(mBackward)) {
        mDv.y -= mIncr;
        mLastDirection = Direction::DOWN;
      }
      if(sf::Keyboard::isKeyPressed(mLeft)) {
        mDv.x -= mIncr;
        mLastDirection = Direction::LEFT;
      }
      if(sf::Keyboard::isKeyPressed(mRight)) {
        mDv.x += mIncr;
        mLastDirection = Direction::RIGHT;
      }

      if(mDv.x || mDv.y) {
        mWalking = true;
        cpVect curV = mBase->GetVelocity();
        mDv = cpv(curV.x + mDv.x, curV.y + mDv.y);
        float len = cpvlength(mDv);
        if(len > mSpeed) {
          float f = mSpeed / len;
          mDv = cpv(mDv.x * f, mDv.y * f);
        }

        mBase->SetVelocity(mDv);
        mDv = cpv(0, 0);
      } else {
        mWalking = false;
        mCurFrame = 0;
        mCurWalkAnim = 0;
        mBase->SetVelocity(cpv(0, 0));
      }

      if(mWalking) {
        setWalkingPos();
      } else {
        setIdlePos();
      }
    }

  protected:
    TEntity* mBase = nullptr;
    float mSpeed = 0;
    float mIncr = 0;
    Key mForward, mBackward, mLeft, mRight;
    Direction mLastDirection = Direction::UP;
    bool mWalking = false;
    cpVect mDv;
    int mCurFrame = 0;
    int mCurWalkAnim = 0;
    vector<int> mAnim;

    void setWalking(Direction dir) {
      mLastDirection = dir;
      if(!mWalking) {
        mCurFrame = 0;
        mCurWalkAnim = 0;
      }
      mWalking = true;
    }

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

  //***************************************************************************/

  //************************* HIGH LEVEL OBJECTS ******************************/

  class PlayerEntity : public AnimatedDynamicEntity, public PlayerMoveBehaviour<PlayerEntity> {
  public:
    PlayerEntity(GameBase* game)
        : AnimatedDynamicEntity(_PLAYER_TYPE,
                                game,
                                _PLAYER_ANIM,
                                {getPlayerShape(game)},
                                true,
                                10),
          PlayerMoveBehaviour(this,
                              7,
                              sf::Keyboard::Up,
                              sf::Keyboard::Down,
                              sf::Keyboard::Left,
                              sf::Keyboard::Right) {}

    void OnTick() {
      auto worlBounds = getGame()->GetWorld()->GetBounds();
      float pxToMeter = getGame()->GetOptions().MeterPerPixel;
      auto pos = cpBodyGetPosition(mBody);
      float y = worlBounds.height - (pos.y / pxToMeter) + 20;
      int yTile = 2 * ((int)(y / 32.0)) - 1;
      SetZIndex(yTile);

      PlayerMoveBehaviour::OnTick();
    }
  };

  //***************************************************************************/

  int demo() {
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

    // Create Game World
    auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/mage_city/tilemap.json", "res/maps/mage_city/materialmap.json", "res/maps/mage_city/tile_", 3);
    game->SetWorld(world);

    auto scene = new SceneGraph(game);
    game->SetScene(scene);

    auto player = new PlayerEntity(game);
    player->SetMoment(INFINITY);
    player->SetTransform(sf::Transform().translate(11, 5));
    scene->AddEntity(player);

    auto cam = new BoundedFollowCameraController(game, player);
    game->SetCameraController(cam);

    auto space = game->GetPhysicalWorld();
    cpSpaceSetGravity(space, cpv(0, 0));

    game->Run();
    return 0;
  }

} // namespace proto2

int prototype2() {
  return proto2::demo();
}