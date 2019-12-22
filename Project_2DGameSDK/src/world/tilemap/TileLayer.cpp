#include <2DGameSDK/world/tilemap/TileLayer.h>

namespace game {

  TileLayer::TileLayer(sf::Vector2i tileAmounts, sf::Vector2i tileBounds, int yOffset)
      : mTileAmounts(tileAmounts),
        mTileBounds(tileBounds),
        mTotalBounds(tileBounds.x * tileAmounts.x, tileBounds.y * tileAmounts.y),
        mYOffset(yOffset) {}

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
    if(!mTexture->create(mTotalBounds.x, mTotalBounds.y)) {
      throw std::runtime_error("Texture creation failed at load tilemap");
    }

    for(auto row : mTiles) {
      for(auto tile : row) {
        if(tile->Texture != nullptr) {
          int x = (tile->X % row.size()) * mTileBounds.x;
          int y = (tile->Y % mTiles.size()) * mTileBounds.y;
          mTexture->update(*tile->Texture, x, y);
        }
      }
    }
    mSprite = new sf::Sprite(*mTexture);
    mSprite->setPosition(0, mYOffset * mTileBounds.y);
  }

  std::vector<TileLayer*> TileLayer::CreateMultilayered() {
    auto ret = std::vector<TileLayer*>();
    for(unsigned y = 0; y < mTiles.size(); y++) {
      auto row = mTiles[y];
      bool hasRenderedTiles = false;
      unsigned x = 0;
      while(!hasRenderedTiles && x < row.size()) {
        auto tile = row[x];
        if(tile && tile->TileID != -1) hasRenderedTiles = true;
        x++;
      }

      if(hasRenderedTiles) {
        auto layer = new TileLayer(sf::Vector2i(mTileAmounts.x, 1), mTileBounds, y);
        layer->SetTiles({row});
        layer->SetZIndex(constants::DEFAULT_ZINDEX_WORLD + 2 * y);
        ret.push_back(layer);
      }
    }

    return ret;
  }

} // namespace game