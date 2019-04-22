#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "gamesdk_dll.h"
#include <SFML/Graphics.hpp>
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
    virtual void Render(sf::RenderTarget& target) = 0;

  protected:
    std::string mType;
  };

} // namespace game

#endif