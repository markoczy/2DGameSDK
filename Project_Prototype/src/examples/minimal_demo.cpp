#include <examples.h>

using namespace std;
using namespace game;

// Type of player entity
const int _PLAYER_TYPE = 200;

/**
 * @brief Make an Entity that rotates on the Screen
 * 
 */
class RotatingEntity : public SpriteTransformableEntity {
public:
  RotatingEntity(sf::Texture* texture,
                 float rotPerTick,
                 sf::Vector2f pos = sf::Vector2f()) : SpriteTransformableEntity(1, texture), mRot(rotPerTick) {
    auto rect = mSprite.getTextureRect();
    mCenter = sf::Vector2f(rect.width / 2, rect.height / 2);

    SetTransform(sf::Transform().translate(pos));
  }

  void Tick() {
    Transform(sf::Transform().rotate(mRot, mCenter));
    auto pt = mTransform.transformPoint(sf::Vector2f());
    cout << "Transform: (" << pt.x << ", " << pt.x << ")" << endl;
    pt = mFullTransform.transformPoint(sf::Vector2f());
    cout << "Full Transform: (" << pt.x << ", " << pt.x << ")" << endl;
  }

private:
  float mRot;
  sf::Vector2f mCenter;
};

int minimalDemo() {
  cout << "Start minimalDemo" << endl;

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");
  cout << "GameWorld created." << endl;

  // Create Player entity and Rotating child entity
  auto tex = AssetManager::GetTexture("res/textures/discus.png");
  auto ent = new RotatingEntity(tex, 5.0, sf::Vector2f(50, 50));
  cout << "Entity created." << endl;
  // auto ent2 = new RotatingEntity(tex, 10.0);

  // Layout entities in scene
  auto scene = new SceneGraph();
  auto parent = scene->AddEntity(ent); //GetRoot()->AddChild(ent);
  cout << "Entity added." << endl;
  scene->AddEntity(ent, parent); //parent->AddChild(ent2);
  cout << "Child Entity added." << endl;

  // Create game
  GameOptions options{"My Game", sf::Vector2i(512, 512), 5.0, 50};
  auto app = new Game(options, scene, world);

  // Run Game
  cout << "Running App.." << endl;
  app->Run();

  return 0;
}