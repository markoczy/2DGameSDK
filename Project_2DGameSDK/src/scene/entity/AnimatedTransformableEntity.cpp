
#include <2DGameSDK/scene/entity/AnimatedTransformableEntity.h>

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode {
  public:
    sf::Transform GetAccumulatedTransform();
  };

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
    return (mGraphNode->GetAccumulatedTransform() * mTransform.getTransform()).transformRect(mCurState.getLocalBounds());
  }

  std::vector<sf::Vector2f> AnimatedTransformableEntity::GetCollisionShape() {
    auto localBounds = mCurState.getLocalBounds();
    }

} // namespace game
