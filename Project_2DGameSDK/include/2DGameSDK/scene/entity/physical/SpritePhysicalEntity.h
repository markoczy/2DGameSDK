#ifndef __SPRITE_PHYSICAL_ENTITY_H__
#define __SPRITE_PHYSICAL_ENTITY_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/dynamic/RectangleDynamicShape.h>
#include <2DGameSDK/scene/entity/physical/PhysicalEntity.h>

namespace game {

  class GAMESDK_DLL SpritePhysicalEntity : public PhysicalEntity {
  private:
  public:
    SpritePhysicalEntity(int type,
                         Game* game,
                         sf::Texture* texture,
                         std::vector<DynamicShape*> shapes = std::vector<DynamicShape*>(),
                         bool isCollidable = false);
    ~SpritePhysicalEntity();

    void SetSize(sf::Vector2f size);

    void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    virtual void OnTick();

    // TODO better concept
    virtual void SetTransform(sf::Transform transform);

  protected:
    sf::Sprite mSprite;
  };

} // namespace game

#endif