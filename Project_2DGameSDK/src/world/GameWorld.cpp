#include <2DGameSDK/world/GameWorld.h>

using namespace sf;

namespace game {
  GameWorld::GameWorld(Game* game, Tilemap* tilemap, MaterialMap* materialMap) : mGame(game), mTilemap(tilemap), mMaterialMap(materialMap) {
    mBounds.width = mTilemap->TileWidth * mTilemap->TilesWide;
    mBounds.height = mTilemap->TileHeight * mTilemap->TilesHigh;
    loadTilemap();
  }

  GameWorld::~GameWorld() {
    helpers::safeDelete(mTilemap);
    helpers::safeDelete(mMaterialMap);
  }

  sf::IntRect GameWorld::GetBounds() {
    return mBounds;
  }

  void GameWorld::loadTilemap() {
    for(auto layer : mTilemap->Layers) {
      mGame->GetStateManager()->AddVisualObject(layer);
    }
  }
} // namespace game