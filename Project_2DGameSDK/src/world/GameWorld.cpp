#include <2DGameSDK/world/GameWorld.h>

using namespace sf;

namespace game {
  GameWorld::GameWorld(Tilemap* tilemap, MaterialMap* materialMap) : mTilemap(tilemap), mMaterialMap(materialMap) {}

  GameWorld::~GameWorld() {
    delete mTilemap;
    delete mMaterialMap;
  }

  void GameWorld::Tick() {
    // TODO foreach tile -> tick
  }

  void GameWorld::Render(sf::RenderTarget* target) {
    for(auto layer : mTilemap->Layers) {
      for(auto row : layer.Tiles) {
        for(auto tile : row) {
          if(tile.Texture != nullptr) {
            Sprite sprite(*tile.Texture);
            sprite.setPosition(tile.X * mTilemap->TileWidth, tile.Y * mTilemap->TileHeight);
            target->draw(sprite);
          }
        }
      }
    }
  }
} // namespace game