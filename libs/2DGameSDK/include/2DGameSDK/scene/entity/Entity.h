#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/Graphics.hpp>

namespace game {

  class GAMESDK_DLL Entity {
  public:
    Entity(int type);
    ~Entity();

    int GetId();
    int GetType();

    virtual void Tick() = 0;
    virtual void Render(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default) = 0;

  protected:
    int mType;
    int mId;
  };

} // namespace game

#endif