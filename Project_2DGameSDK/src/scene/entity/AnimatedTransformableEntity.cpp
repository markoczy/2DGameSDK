
#include <2DGameSDK/scene/entity/AnimatedTransformableEntity.h>

namespace game {

  AnimatedTransformableEntity::AnimatedTransformableEntity(int type, std::map<int, sf::Texture*> animationStates) : TransformableEntity(type), mAnimStates(animationStates) {
    mTransform = sf::Transformable();
  }

  AnimatedTransformableEntity::~AnimatedTransformableEntity() {}

  void AnimatedTransformableEntity::Tick() {}

  void AnimatedTransformableEntity::Render(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform *= mTransform.getTransform();
    target->draw(mCurState, states);
  }

  sf::Transformable* AnimatedTransformableEntity::GetTransformable() {
    return &mTransform;
  }

  void AnimatedTransformableEntity::SetAnimState(int state) {
    // TODO error state not found
    mCurState = sf::Sprite(*mAnimStates[state]);
  }

} // namespace game
