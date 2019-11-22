#include <2DGameSDK/world/tilemap/TileLayer.h>

namespace game {

  TileLayer::TileLayer(sf::IntRect worldBounds, sf::IntRect tileBounds) : mWorldBounds(worldBounds), mTileBounds(tileBounds) {}

  TileLayer::~TileLayer() {
    helpers::safeDelete(mSprite);
    helpers::safeDelete(mTexture);
  }

  int TileLayer::GetZIndex() {
    return mZIndex;
  }

  int TileLayer::GetNumber() {
    return mNumber;
  }

  std::string TileLayer::GetName() {
    return mName;
  }

  void TileLayer::SetZIndex(int zIndex) {
    mZIndex = zIndex;
  }

  void TileLayer::SetNumber(int number) {
    mNumber = number;
  }

  void TileLayer::SetName(std::string name) {
    mName = name;
  }

  void TileLayer::SetTiles(std::vector<std::vector<Tile*>> tiles) {
    mTiles = tiles;
  }

  std::vector<std::vector<Tile*>> TileLayer::GetTiles() {
    return mTiles;
  }

  void TileLayer::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    LOGD("Rendering layer");
    target->draw(*mSprite, states);
  }

  void TileLayer::OnTexturesLoaded() {
    mTexture = new sf::Texture();
    if(!mTexture->create(mWorldBounds.width, mWorldBounds.height)) {
      throw std::runtime_error("Texture creation failed at load tilemap");
    }

    for(auto row : mTiles) {
      for(auto tile : row) {
        if(tile->Texture != nullptr) {
          int x = tile->X * mTileBounds.width;
          int y = tile->Y * mTileBounds.height;
          mTexture->update(*tile->Texture, x, y);
        }
      }
    }
    mSprite = new sf::Sprite(*mTexture);
  }
} // namespace game