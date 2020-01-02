#include <examples.h>

using namespace std;
using namespace game;

using Key = sf::Keyboard::Key;

const int PLAYER_TYPE = 200;

class PlayerEntity : public SpriteKinematicEntity {
public:
  PlayerEntity(GameBase* game)
      : SpriteKinematicEntity(PLAYER_TYPE,
                              game,
                              AssetManager::GetTexture("res/textures/spaceships/scorpio/prefab_scorpio_1.png")) {}

  void OnTick() override {
    // 4 axis movement
    auto move = sf::Vector2f();
    if(sf::Keyboard::isKeyPressed(Key::Up)) {
      move.y += 5;
    }
    if(sf::Keyboard::isKeyPressed(Key::Down)) {
      move.y -= 5;
    }
    if(sf::Keyboard::isKeyPressed(Key::Left)) {
      move.x -= 5;
    }
    if(sf::Keyboard::isKeyPressed(Key::Right)) {
      move.x += 5;
    }
    SetTransform(GetTransform().translate(move));
  }
};

int playerDemo(float) {
  float aspectRatio = (float)sf::VideoMode::getDesktopMode().width / (float)sf::VideoMode::getDesktopMode().height;
  // create game
  auto game = new Game(GameOptions{"My Game Title", sf::Vector2i(1024, 1024 / aspectRatio)});

  // create scene graph
  auto scene = new SceneGraph(game);

  // create player
  auto player = new PlayerEntity(game);

  // add player
  scene->AddEntity(player);

  // set scene
  game->SetScene(scene);
  int i = 1;
  // create world
  auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/proto1/tilemap.json", "", "res/maps/proto1/tile_");
  // auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/space/tilemap.json", "", "res/maps/space/tile_");

  // create camera that follows the player
  auto cam = new BoundedFollowCameraController(game, player);

  // set camera
  game->SetCameraController(cam);

  // set world
  game->SetWorld(world);

  // run game :-)
  game->Run();

  return 0;
}