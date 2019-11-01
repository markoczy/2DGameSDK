
#include <2DGameSDK/scene/entity/AnimatedTransformableEntity.h>

namespace game {

  AnimatedTransformableEntity::AnimatedTransformableEntity(int type, Game* game, std::map<int, sf::Texture*> animationStates) : TransformableEntity(type, game), mAnimStates(animationStates) {
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
    ss << "Animation State " << state << " not found for Entity " << GetId();
    throw std::runtime_error(ss.str());
  }

} // namespace game
