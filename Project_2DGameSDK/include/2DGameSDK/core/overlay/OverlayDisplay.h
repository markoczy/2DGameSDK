#ifndef __OVERLAY_DISPLAY_H__
#define __OVERLAY_DISPLAY_H__

#include <map>

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/world/GameWorld.h>

namespace game {
  class GAMESDK_DLL OverlayDisplay {
  public:
    OverlayDisplay(GameBase* game);
    int AddElement(sf::Drawable* elem, bool enabled = false);
    void Enable(int id);
    void Disable(int id);

    void OnTick();
    void OnRender(sf::RenderTarget* target);

  private:
    GameBase* mGame = nullptr;
    std::map<int, std::tuple<sf::Drawable*, bool>> mDrawables;
    bool mStateChanged = true;
    sf::Sprite mSprite;
    // sf::RenderTexture* mTexture = nullptr;
  };

} // namespace game

#endif