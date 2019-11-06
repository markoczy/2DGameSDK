#include <examples.h>

using namespace std;
using namespace game;

int physicsDemo() {
  cout << "Physics Demo" << endl;

  // Create game
  auto game = new Game();
  game->SetOptions(GameOptions{"My Game", sf::Vector2i(512, 512), 2.0, 50, true, true});

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");
  game->SetWorld(world);

  auto boxTx = AssetManager::GetTexture("res/textures/box/box.png");

  auto scene = new SceneGraph();
  auto ground = new SpriteStaticEntity(1, game, boxTx, {new RectangleDynamicShape(game, 200, 60)}, true);
  ground->SetSize(sf::Vector2f(200, 60));
  ground->SetTransform(sf::Transform().translate(100, 200));
  auto box = new SpritePhysicalEntity(1, game, boxTx, {new RectangleDynamicShape(game, boxTx->getSize().x, boxTx->getSize().y)}, true);
  box->SetTransform(sf::Transform().translate(100, 100));
  box->SetMass(2000);
  box->SetMoment(cpMomentForBox(1000, 20, 20));

  scene->AddEntity(ground);
  scene->AddEntity(box);
  game->SetScene(scene);

  auto space = game->GetPhysicalWorld();
  cpSpaceSetGravity(space, cpv(0, -10));

  // Run Game
  game->Run();

  return 0;
}