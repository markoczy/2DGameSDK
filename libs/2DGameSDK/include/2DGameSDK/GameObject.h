#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "gamesdk_dll.h"
#include <string>

namespace game {

  class SingleTextureVisual {
    virtual void Render();
  };

  // Represents any game object
  class GameObject {
  public:
    GameObject(const std::string& type);
    virtual void Tick() = 0;
    virtual void Render() = 0;

  protected:
    std::string mType;
  };

} // namespace game

#endif