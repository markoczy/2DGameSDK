#ifndef __SPRITE_TRANSFORMABLE_ENTITY_H__
#define __SPRITE_TRANSFORMABLE_ENTITY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/TransformableEntity.h>
#include <SFML/Graphics.hpp>

namespace game {

  class GAMESDK_DLL SpriteTransformableEntity : public TransformableEntity {
  public:
    SpriteTransformableEntity(int type, sf::Texture* texture);
    ~SpriteTransformableEntity();

    virtual void Tick();
    void Render(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);
    sf::Transformable* GetTransformable();

  private:
    sf::Sprite* mSprite;
  };

} // namespace game

#endif