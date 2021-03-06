#ifndef __SPRITE_STATIC_ENTITY_H__
#define __SPRITE_STATIC_ENTITY_H__

#include <vector>

#include <SFML/Graphics.hpp>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/StaticShapeDefinition.h>
#include <2DGameSDK/scene/entity/definitions/StaticEntity.h>

namespace game {
  class GAMESDK_DLL SpriteStaticEntity : public StaticEntity {
  public:
    SpriteStaticEntity(int type,
                       Game* game,
                       sf::Texture* texture,
                       std::vector<Shape<StaticShapeDefinition>*> shapes = std::vector<Shape<StaticShapeDefinition>*>(),
                       bool isCollidable = false);

    ~SpriteStaticEntity();

    void SetSize(sf::Vector2f size);

    void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    virtual void OnTick();

  protected:
    sf::Sprite mSprite;
  };
} // namespace game

#endif