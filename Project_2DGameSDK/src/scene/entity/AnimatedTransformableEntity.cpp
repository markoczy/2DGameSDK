#ifndef __ANIMATED_TRANSFORMABLE_ENTITY_H__
#define __ANIMATED_TRANSFORMABLE_ENTITY_H__

#include <2DGameSDK/scene/entity/TransformableEntity.h>

namespace game {

  class AnimatedTransformableEntity : public TransformableEntity {
  public:
    AnimatedTransformableEntity(int type, std::map<int, sf::Texture*> animationStates);
    ~AnimatedTransformableEntity();

    virtual void Tick();

    virtual void Render(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);
    virtual sf::Transformable* GetTransformable();

  protected:
    std::map<int, sf::Texture*> mAnimStates;
    sf::Sprite mCurState;
  };

} // namespace game

#endif