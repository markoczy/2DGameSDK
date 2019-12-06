#ifndef __CAMERA_CONTROLLER_H__
#define __CAMERA_CONTROLLER_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL CameraController {
  public:
    CameraController(GameBase* game);
    virtual ~CameraController();

    virtual sf::View GetView() = 0;
    virtual sf::Vector2f GetBounds() = 0;

    virtual void SetZoom(float zoom) = 0;
    virtual void SetCenter(sf::Vector2f center) = 0;

    virtual void OnTick() = 0;

  protected:
    GameBase* getGame();

  private:
    GameBase* mGame;
    sf::Vector2f mBounds;
  };

} // namespace game

#endif