#include <2DGameSDK/world/GameWorld.h>

using namespace sf;

namespace game {
  GameWorld::GameWorld(Game* game, Tilemap* tilemap, MaterialMap* materialMap) : mGame(game), mTilemap(tilemap), mMaterialMap(materialMap) {
    // loadTilemap();
    mBounds.width = mTilemap->TileWidth * mTilemap->TilesWide;
    mBounds.height = mTilemap->TileHeight * mTilemap->TilesHigh;
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
  }

  sf::IntRect GameWorld::GetBounds() {
    return mBounds;
  }

  void GameWorld::loadTilemap() {
    // for(auto layer : mTilemap->Layers) {
    //   for(auto row : layer->Tiles) {
    //     for(auto tile : row) {
    //       mGame->GetStateManager()->AddObject(tile);
    //     }
    //   }
    // }

    // if(mTexture != nullptr) {
    //   delete mTexture;
    // }

    // mBounds.width = mTilemap->TileWidth * mTilemap->TilesWide;
    // mBounds.height = mTilemap->TileHeight * mTilemap->TilesHigh;
    // mTexture = new Texture();
    // if(!mTexture->create(mBounds.width, mBounds.height)) {
    //   throw std::runtime_error("Texture creation failed at load tilemap");
    // }

    // for(auto layer : mTilemap->Layers) {
    //   for(auto row : layer->Tiles) {
    //     for(auto tile : row) {
    //       if(tile->Texture != nullptr) {
    //         int x = tile->X * mTilemap->TileWidth;
    //         int y = tile->Y * mTilemap->TileHeight;
    //         mTexture->update(*tile->Texture, x, y);
    //       }
    //     }
    //   }
    // }
  }
} // namespace game