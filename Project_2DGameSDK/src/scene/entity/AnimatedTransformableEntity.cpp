
#include <2DGameSDK/scene/entity/AnimatedTransformableEntity.h>

namespace game {

  // SceneGraphNode forward Declaration
  // class SceneGraphNode {
  // public:
  //   sf::Transform GetAccumulatedTransform();
  // };

  AnimatedTransformableEntity::AnimatedTransformableEntity(int type, std::map<int, sf::Texture*> animationStates) : TransformableEntity(type), mAnimStates(animationStates) {
  }

  AnimatedTransformableEntity::~AnimatedTransformableEntity() {}

  void AnimatedTransformableEntity::Tick() {}

  void AnimatedTransformableEntity::Render(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mFullTransform;
    target->draw(mCurState, states);
  }

  // sf::Transformable* AnimatedTransformableEntity::GetTransformable() {
  //   return &mTransform;
  // }

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

    mFullTransform = GetAccumulatedTransform() * GetTransform();
    updateAABB();
    updateCollisionMask();
  }

  void AnimatedTransformableEntity::updateAABB() {
    mAABB = mFullTransform.transformRect(mCurState.getLocalBounds());
  }

  void AnimatedTransformableEntity::updateCollisionMask() {
    // mTransformedCollisionMask = helpers::GrahicTools::TransformPoints(mCollisionMask, mFullTransform);

    // TODO collision masks anim entity
    mTransformedCollisionMask = std::vector<sf::Vector2f>();
  }

} // namespace game
