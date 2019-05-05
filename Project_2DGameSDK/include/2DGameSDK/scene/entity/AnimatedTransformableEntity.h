#ifndef __ANIMATED_TRANSFORMABLE_ENTITY_H__
#define __ANIMATED_TRANSFORMABLE_ENTITY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/TransformableEntity.h>

namespace game {

  class GAMESDK_DLL AnimatedTransformableEntity : public TransformableEntity {
  public:
    AnimatedTransformableEntity(int type, std::map<int, sf::Texture*> animationStates);
    ~AnimatedTransformableEntity();

    virtual void Tick();

    virtual void Render(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);
    virtual sf::Transformable* GetTransformable();

    void SetAnimState(int state);

  protected:
    std::map<int, sf::Texture*> mAnimStates;
    sf::Sprite mCurState;
    sf::Transformable mTransform;
  };

} // namespace game

#endif