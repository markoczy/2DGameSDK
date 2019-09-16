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
    // Set origin to center of the Texture
    GetTransformable()->setOrigin(float(rect.width) / 2.0, float(rect.height) / 2.0);
    GetTransformable()->setPosition(pos);
  }

  void Tick() {
    GetTransformable()->rotate(mRot);
  }

private:
  float mRot;
};

int minimalDemo() {
  cout << "Start minimalDemo" << endl;

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/simple_grass/tilemap.json", "", "res/simple_grass/tile_");

  // Create Player entity and Rotating child entity
  auto tex = AssetManager::GetTexture("res/textures/discus.png");
  auto ent = new RotatingEntity(tex, 5.0, sf::Vector2f(50, 50));
  auto ent2 = new RotatingEntity(tex, 10.0);

  // Layout entities in scene
  auto scene = new SceneGraph();
  auto parent = scene->AddEntity(ent); //GetRoot()->AddChild(ent);
  auto child = scene->AddEntity(ent, parent); //parent->AddChild(ent2);

  // Create game
  GameOptions options{"My Game", sf::Vector2i(512, 512), 5.0, 50};
  auto app = new Game(options, scene, world);

  // Run Game
  app->Run();
}