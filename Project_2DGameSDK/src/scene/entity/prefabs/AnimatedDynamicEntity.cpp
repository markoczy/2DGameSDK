#include <2DGameSDK/scene/entity/prefabs/AnimatedDynamicEntity.h>

namespace game {

  AnimatedDynamicEntity::AnimatedDynamicEntity(int type, GameBase* game, std::map<int, sf::Texture*> animationStates, std::vector<Shape<DynamicShapePhysics>*> shapes, bool isCollidable, int initialState) : DynamicEntity(type, game, nullptr, shapes, isCollidable) {
    mSpecificRenderer = new AnimatedRenderStrategy(game, animationStates, initialState);
    mRenderer = mSpecificRenderer;
  }

  void AnimatedDynamicEntity::SetSize(sf::Vector2f size) {
    mSpecificRenderer->SetSize(size);
  }

  void AnimatedDynamicEntity::SetSize(int state, sf::Vector2f size) {
    mSpecificRenderer->SetSize(state, size);
  }

  void AnimatedDynamicEntity::SetAnimState(int state) {
    mSpecificRenderer->SetAnimState(state);
  }

} // namespace game