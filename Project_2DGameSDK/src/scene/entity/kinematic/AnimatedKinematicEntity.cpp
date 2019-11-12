
#include <2DGameSDK/scene/entity/kinematic/AnimatedKinematicEntity.h>

namespace game {

  AnimatedKinematicEntity::AnimatedKinematicEntity(int type, Game* game, std::map<int, sf::Texture*> animationStates) : KinematicEntity(type, game), mAnimStates(animationStates) {
  }

  AnimatedKinematicEntity::~AnimatedKinematicEntity() {}

  void AnimatedKinematicEntity::OnTick() {}

  void AnimatedKinematicEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mCombinedTransform;
    target->draw(mCurState, states);
  }

  void AnimatedKinematicEntity::SetAnimState(int state) {
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
