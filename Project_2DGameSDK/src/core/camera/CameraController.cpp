#include <2DGameSDK/core/camera/CameraController.h>

namespace game {
  CameraController::CameraController(GameBase* game) : mGame(game) {}

  GameBase* CameraController::getGame() {
    return mGame;
  }

} // namespace game
