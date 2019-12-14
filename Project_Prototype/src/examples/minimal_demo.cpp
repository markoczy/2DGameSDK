#include <examples.h>

using namespace std;
using namespace game;

// Type of player entity
const int _PLAYER_TYPE = 200;

/**
 * @brief Make an Entity that rotates on the Screen
 * 
 */
class RotatingEntity : public SpriteKinematicEntity {
public:
  RotatingEntity(Game* game,
                 sf::Texture* texture,
                 float rotPerTick,
                 sf::Vector2f pos = sf::Vector2f()) : SpriteKinematicEntity(1, game, texture), mRot(rotPerTick) {
    // auto rect = mSprite.getTextureRect();
    // mCenter = sf::Vector2f(rect.width / 2, rect.height / 2);

    SetTransform(sf::Transform().translate(pos));
  }

  void OnTick() {
    Transform(sf::Transform().rotate(mRot));
    auto pt = mTransform.transformPoint(sf::Vector2f());
    cout << "Transform: (" << pt.x << ", " << pt.x << ")" << endl;
    pt = mCombinedTransform.transformPoint(sf::Vector2f());
    cout << "Full Transform: (" << pt.x << ", " << pt.x << ")" << endl;
  }

private:
  float mRot;
};

int minimalDemo() {
  cout << "Start minimalDemo" << endl;

  // Create game
  auto options = GameOptions{"My Game", sf::Vector2i(512, 512), 5.0, 50};
  auto game = new Game(options);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/simple_grass/tilemap.json", "", "res/maps/simple_grass/tile_");
  game->SetWorld(world);
  cout << "GameWorld created." << endl;

  // Create Player entity and Rotating child entity
  auto tex = AssetManager::GetTexture("res/textures/discus.png");
  auto ent = new RotatingEntity(game, tex, 5.0, sf::Vector2f(50, 50));
  cout << "Entity created." << endl;
  // auto ent2 = new RotatingEntity(tex, 10.0);

  // Layout entities in scene
  auto scene = new SceneGraph(game);
  auto parent = scene->AddEntity(ent); //GetRoot()->AddChild(ent);
  cout << "Entity added." << endl;
  scene->AddEntity(ent, parent); //parent->AddChild(ent2);
  game->SetScene(scene);
  cout << "Child Entity added." << endl;

  // Run Game
  cout << "Running App.." << endl;
  game->Run();

  return 0;
}