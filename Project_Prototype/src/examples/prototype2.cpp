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

  //*
  //* ASSETS
  //*---------------------------------------------------------------------------

  sf::Texture* _PLAYER_TEXTURE = AssetManager::GetTexture("res/textures/rpghero/hero_10.png");

  //*
  //* SHAPES
  //*---------------------------------------------------------------------------

  DynamicShape* getPlayerShape(GameBase* game) {
    static PolygonShape<DynamicShapeDefinition>* ret = nullptr;
    if(ret == nullptr) {
      auto verts = vector<cpVect>();
      verts.push_back(cpv(-6, -16));
      verts.push_back(cpv(-6, -23));
      verts.push_back(cpv(5, -23));
      verts.push_back(cpv(5, -16));
      ret = ShapeFactory::CreateDynamicPolygonShape(game, verts, 1, 1, 0);
    }
    return ret;
  }

  //***************************************************************************/

  //************************* BEHAVIOURS (GENERIC ENTITY LOGIC) ***************/

  template <class TEntity>
  class PlayerMoveBehaviour {
  public:
    PlayerMoveBehaviour(TEntity* base, float speed, Key forward, Key backward, Key left, Key right) : mBase(base), mSpeed(speed), mForward(forward), mBackward(backward), mLeft(left), mRight(right) {
      cout << "PlayerMove Constructor" << endl;
    }

    void OnTick() {
      std::cout << "OnTick.." << std::endl;
      if(sf::Keyboard::isKeyPressed(mForward)) {
        mDv.y += mSpeed;
      }
      if(sf::Keyboard::isKeyPressed(mBackward)) {
        mDv.y -= mSpeed;
      }
      if(sf::Keyboard::isKeyPressed(mLeft)) {
        mDv.x -= mSpeed;
      }
      if(sf::Keyboard::isKeyPressed(mRight)) {
        mDv.x += mSpeed;
      }

      mBase->SetVelocity(mDv);
      mDv = cpv(0, 0);

      // if(mDt.x != 0 || mDt.y != 0) {
      //   // mBase->OnMove(mDt);
      //   mBase->Transform(sf::Transform().translate(mDt));
      // }
      // mDt = sf::Vector2f();
    }

  protected:
    TEntity* mBase = nullptr;
    float mSpeed = 0;
    Key mForward, mBackward, mLeft, mRight;

    cpVect mDv;
  };

  //***************************************************************************/

  //************************* HIGH LEVEL OBJECTS ******************************/

  class PlayerEntity : public SpriteDynamicEntity, public PlayerMoveBehaviour<PlayerEntity> {
  public:
    PlayerEntity(GameBase* game) : SpriteDynamicEntity(_PLAYER_TYPE, game, _PLAYER_TEXTURE, {getPlayerShape(game)}), PlayerMoveBehaviour(this, 35, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right) {}

    void OnTick() {
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
                               true, /* Debug Shapes */
                               1.0, /* Pixel to Meter */
                               true /* Audio Enabled */};
    auto game = new Game(options);

    // Create Game World
    auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/mage_city/tilemap.json", "", "res/maps/mage_city/tile_", 3);
    game->SetWorld(world);

    auto scene = new SceneGraph(game);
    game->SetScene(scene);

    auto player = new PlayerEntity(game);
    player->SetTransform(sf::Transform().translate(50, 600));
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