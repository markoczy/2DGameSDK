#ifndef __SPRITE_DYNAMIC_ENTITY_H__
#define __SPRITE_DYNAMIC_ENTITY_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/DynamicShapeDefinition.h>
#include <2DGameSDK/scene/entity/definitions/DynamicEntity.h>

namespace game {

  class GAMESDK_DLL SpriteDynamicEntity : public DynamicEntity {
  public:
    SpriteDynamicEntity(int type,
                        Game* game,
                        sf::Texture* texture,
                        std::vector<Shape<DynamicShapeDefinition>*> shapes = std::vector<Shape<DynamicShapeDefinition>*>(),
                        bool isCollidable = false);
    ~SpriteDynamicEntity();

    void SetSize(sf::Vector2f size);

    void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    virtual void OnTick();

  protected:
    sf::Sprite mSprite;

    // TODO better concept
    virtual bool setTransform(sf::Transform transform);
  };

} // namespace game

#endif