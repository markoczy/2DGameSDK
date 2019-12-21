#include <examples.h>

using namespace game;
using namespace std;
using namespace sf;

using Key = sf::Keyboard::Key;
using KinematicShape = game::Shape<KinematicShapeDefinition>;

int prototype2() {
  float aspectRatio = (float)sf::VideoMode::getDesktopMode().width / (float)sf::VideoMode::getDesktopMode().height;

  // Create game
  auto options = GameOptions{"Roleplay Prototype", /* Title */
                             sf::Vector2i(1024, 1024 / aspectRatio), /* Dim */
                             0.5, /* Scale */
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

  game->Run();
  return 0;
}