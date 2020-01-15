#ifndef __ANIMATED_DYNAMIC_ENTITY_H__
#define __ANIMATED_DYNAMIC_ENTITY_H__

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/core/visual/AnimatedRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/definitions/DynamicEntity.h>

namespace game {

  class GAMESDK_DLL AnimatedDynamicEntity : public DynamicEntity {
  public:
    AnimatedDynamicEntity(int type,
                          GameBase* game,
                          std::map<int, sf::Texture*> animationStates,
                          std::vector<Shape<DynamicShapePhysics>*> shapes = std::vector<Shape<DynamicShapePhysics>*>(),
                          bool isCollidable = false,
                          int initialState = constants::DEFAULT_ANIMATION_START);

    void SetSize(sf::Vector2f size);
    void SetSize(int state, sf::Vector2f size);

    void SetAnimState(int state);

  private:
    AnimatedRenderStrategy* mSpecificRenderer = nullptr;
  };

} // namespace game

#endif
