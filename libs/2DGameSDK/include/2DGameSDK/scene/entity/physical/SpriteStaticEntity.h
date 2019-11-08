#ifndef __SPRITE_STATIC_ENTITY_H__
#define __SPRITE_STATIC_ENTITY_H__

#include <vector>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/physical/StaticEntity.h>

namespace game {
  class GAMESDK_DLL SpriteStaticEntity : public StaticEntity {
  public:
    SpriteStaticEntity(int type,
                       Game* game,
                       sf::Texture* texture,
                       std::vector<Shape*> shapes = std::vector<Shape*>(),
                       bool isCollidable = false);

    ~SpriteStaticEntity();

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