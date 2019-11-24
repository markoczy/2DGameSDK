#ifndef __CAMERA_CONTROLLER_H__
#define __CAMERA_CONTROLLER_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>

namespace game {

  class CameraController {
  public:
    CameraController(GameBase* game);
    virtual void OnTick() = 0;
    virtual sf::View GetView() = 0;

  protected:
    GameBase* getGame();

  private:
    GameBase* mGame;
  };

} // namespace game

#endif