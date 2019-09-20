#include <2DGameSDK/world/GameWorld.h>

using namespace sf;

namespace game {
  GameWorld::GameWorld(Tilemap* tilemap, MaterialMap* materialMap) : mTilemap(tilemap), mMaterialMap(materialMap) {
    loadTilemap();
  }

  GameWorld::~GameWorld() {
    // Cleanup Tilemap
    for(auto layer : mTilemap->Layers) {
      for(auto row : layer->Tiles) {
        for(auto tile : row) {
          helpers::safeDelete(tile);
        }
      }
      helpers::safeDelete(layer);
    }

    helpers::safeDelete(mTilemap);
    helpers::safeDelete(mMaterialMap);
    helpers::safeDelete(mPhysicsWorld);
  }

  void GameWorld::Tick() {
    // TODO foreach tile -> tick
  }

  void GameWorld::Render(sf::RenderTarget* target) {
    Sprite sprite(*mTexture);
    target->draw(sprite);
  }

  void GameWorld::loadTilemap() {
    if(mTexture != nullptr) {
      delete mTexture;
    }

    int mWidth = mTilemap->TileWidth * mTilemap->TilesWide;
    int mHeight = mTilemap->TileHeight * mTilemap->TilesHigh;
    mTexture = new Texture();
    if(!mTexture->create(mWidth, mHeight)) {
      throw std::runtime_error("Texture creation failed at load tilemap");
    }

    for(auto layer : mTilemap->Layers) {
      for(auto row : layer->Tiles) {
        for(auto tile : row) {
          if(tile->Texture != nullptr) {
            int x = tile->X * mTilemap->TileWidth;
            int y = tile->Y * mTilemap->TileHeight;
            mTexture->update(*tile->Texture, x, y);
          }
        }
      }
    }
  }
} // namespace game