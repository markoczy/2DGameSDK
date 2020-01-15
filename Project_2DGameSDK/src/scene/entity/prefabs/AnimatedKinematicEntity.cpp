#include <2DGameSDK/scene/entity/prefabs/AnimatedKinematicEntity.h>

namespace game {

  AnimatedKinematicEntity::AnimatedKinematicEntity(int type, GameBase* game, std::map<int, sf::Texture*> animationStates, std::vector<Shape<KinematicShapePhysics>*> shapes, bool isCollidable, int initialState) : KinematicEntity(type, game, nullptr, shapes, isCollidable) {
    mSpecificRenderer = new AnimatedRenderStrategy(game, animationStates, initialState);
    mRenderer = mSpecificRenderer;
  }

  void AnimatedKinematicEntity::SetSize(sf::Vector2f size) {
    mSpecificRenderer->SetSize(size);
  }

  void AnimatedKinematicEntity::SetSize(int state, sf::Vector2f size) {
    mSpecificRenderer->SetSize(state, size);
  }

  void AnimatedKinematicEntity::SetAnimState(int state) {
    mSpecificRenderer->SetAnimState(state);
  }

} // namespace game