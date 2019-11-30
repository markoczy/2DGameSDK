#include <2DGameSDK/core/overlay/OverlayDisplay.h>

namespace game {
  static int counter = 0;

  OverlayDisplay::OverlayDisplay(GameBase* game) : mGame(game) {}

  int OverlayDisplay::AddElement(sf::Drawable* elem, bool enabled) {
    mDrawables[counter] = std::make_tuple(elem, enabled);
    return counter++;
  }

  void OverlayDisplay::Enable(int id) {
    std::get<1>(mDrawables[id]) = true;
  }

  void OverlayDisplay::Disable(int id) {
    std::get<1>(mDrawables[id]) = true;
  }

  void OverlayDisplay::OnTick() {
    if(!mStateChanged) return;

    auto bounds = mGame->GetWorld()->GetBounds();
    auto tex = sf::RenderTexture();
    tex.create(bounds.width, bounds.height);
    for(auto entry : mDrawables) {
      if(!std::get<1>(entry.second)) continue;
      tex.draw(*std::get<0>(entry.second));
    }
    mSprite = sf::Sprite(tex.getTexture());
    mSprite.setOrigin(bounds.width / 2.0, bounds.height / 2.0);
  }

  void OverlayDisplay::OnRender(sf::RenderTarget* target) {
    auto view = mGame->GetWindow()->getView();
    mSprite.setPosition(view.getCenter());
    mSprite.setRotation(view.getRotation());
    target->draw(mSprite);
  }
} // namespace game
