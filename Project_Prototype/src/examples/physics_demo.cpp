#include <examples.h>

using namespace std;
using namespace game;

int physicsDemo() {
  cout << "Physics Demo" << endl;

  // Create game
  auto game = new Game();
  game->SetOptions(GameOptions{"My Game", sf::Vector2i(512, 512), 2.0, 50, false, true});

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");
  game->SetWorld(world);

  auto boxTx = AssetManager::GetTexture("res/textures/box/box.png");

  auto scene = new SceneGraph();

  auto groundShape = new RectangleDynamicShape(game, 200, 60);
  groundShape->SetElasticity(1);
  groundShape->SetFriction(0.3);
  auto ground = new SpriteStaticEntity(1, game, boxTx, {groundShape}, true);
  ground->SetSize(sf::Vector2f(200, 60));
  ground->SetTransform(sf::Transform().translate(100, 200));

  auto shape = new RectangleDynamicShape(game, 5, 5);
  shape->SetElasticity(1);
  shape->SetDensity(1);
  shape->SetFriction(0.3);
  auto box = new SpritePhysicalEntity(2, game, boxTx, {shape}, true);
  box->SetSize(sf::Vector2f(5, 5));
  box->SetTransform(sf::Transform().translate(100, 100).rotate(10));

  scene->AddEntity(ground);
  scene->AddEntity(box);
  game->SetScene(scene);

  auto space = game->GetPhysicalWorld();
  cpSpaceSetGravity(space, cpv(0, -10));

  // Run Game
  game->Run();

  return 0;
}