
#include <2DGameSDK/scene/entity/AnimatedTransformableEntity.h>

namespace game {

  AnimatedTransformableEntity::AnimatedTransformableEntity(int type, std::map<int, sf::Texture*> animationStates) : TransformableEntity(type), mAnimStates(animationStates) {
  }

  AnimatedTransformableEntity::~AnimatedTransformableEntity() {}

  void AnimatedTransformableEntity::OnTick() {}

  void AnimatedTransformableEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mCombinedTransform;
    target->draw(mCurState, states);
  }

  void AnimatedTransformableEntity::SetAnimState(int state) {
    auto animState = mAnimStates.find(state);
    if(animState != mAnimStates.end()) {
      mCurState = sf::Sprite(*animState->second);
      return;
    }

    std::stringstream ss;
    ss << "Animation State " << state << " not found for Entity " << mId;
    throw std::runtime_error(ss.str());
  }

  sf::FloatRect AnimatedTransformableEntity::GetAABB() {
    return mAABB;
  }

  std::vector<sf::Vector2f> AnimatedTransformableEntity::GetCollisionMask() {
    return mTransformedCollisionMask;
  }

  void AnimatedTransformableEntity::OnParentTransformed(sf::Transform accumulated) {
    TransformableEntity::OnParentTransformed(accumulated);

    mCombinedTransform = GetAccumulatedTransform() * GetTransform();
    updateAABB();
    updateCollisionMask();
  }

  void AnimatedTransformableEntity::updateAABB() {
    mAABB = mCombinedTransform.transformRect(mCurState.getLocalBounds());
  }

  void AnimatedTransformableEntity::updateCollisionMask() {
    // TODO collision masks anim entity
    mTransformedCollisionMask = std::vector<sf::Vector2f>();
  }

} // namespace game
