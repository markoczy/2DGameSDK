#include <2DGameSDK/core/camera/CameraController.h>

namespace game {
  CameraController::CameraController(GameBase* game) : mGame(game) {}

  CameraController::~CameraController() {}

  GameBase* CameraController::getGame() {
    return mGame;
  }

} // namespace game
