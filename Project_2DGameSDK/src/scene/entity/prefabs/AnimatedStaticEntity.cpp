#include <2DGameSDK/scene/entity/prefabs/AnimatedStaticEntity.h>

namespace game {

  AnimatedStaticEntity::AnimatedStaticEntity(int type, GameBase* game, std::map<int, sf::Texture*> animationStates, std::vector<Shape<StaticShapeDefinition>*> shapes, bool isCollidable, int initialState) : StaticEntity(type, game, nullptr, shapes, isCollidable) {
    mSpecificRenderer = new AnimatedRenderStrategy(game, animationStates, initialState);
    mRenderer = mSpecificRenderer;
  }

  void AnimatedStaticEntity::SetSize(sf::Vector2f size) {
    mSpecificRenderer->SetSize(size);
  }

  void AnimatedStaticEntity::SetSize(int state, sf::Vector2f size) {
    mSpecificRenderer->SetSize(state, size);
  }

  void AnimatedStaticEntity::SetAnimState(int state) {
    mSpecificRenderer->SetAnimState(state);
  }

} // namespace game