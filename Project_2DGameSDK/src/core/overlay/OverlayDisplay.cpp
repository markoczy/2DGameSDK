#include <2DGameSDK/core/overlay/OverlayDisplay.h>

namespace game {
  static int counter = 0;

  OverlayDisplay::OverlayDisplay(GameBase* game) : mGame(game), mTexture(new sf::RenderTexture()) {}

  int OverlayDisplay::AddElement(sf::Drawable* elem, bool enabled) {
    mDrawables[counter] = std::make_tuple(elem, enabled);
    mStateChanged = true;
    return counter++;
  }

  void OverlayDisplay::Enable(int id) {
    std::get<1>(mDrawables[id]) = true;
    mStateChanged = true;
  }

  void OverlayDisplay::Disable(int id) {
    std::get<1>(mDrawables[id]) = false;
    mStateChanged = true;
  }

  void OverlayDisplay::OnTick() {
    if(!mStateChanged) return;

    auto bounds = mGame->GetOptions().ScreenDim;
    mTexture->create(bounds.x, bounds.y);
    mTexture->clear(sf::Color::Transparent);
    for(auto entry : mDrawables) {
      if(!std::get<1>(entry.second)) continue;
      mTexture->draw(*std::get<0>(entry.second));
    }
    mTexture->display();
    mSprite = sf::Sprite(mTexture->getTexture());
    mSprite.setOrigin(bounds.x / 2.0, bounds.y / 2.0);
    mStateChanged = false;
  }

  void OverlayDisplay::OnRender(sf::RenderTarget* target) {
    auto view = target->getView();
    float scale = view.getSize().x / mSprite.getLocalBounds().width;

    mSprite.setScale(scale, scale);
    mSprite.setPosition(view.getCenter());
    mSprite.setRotation(view.getRotation());
    target->draw(mSprite);
  }
} // namespace game
