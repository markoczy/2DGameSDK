#ifndef __ANIMATED_KINEMATIC_ENTITY_H__
#define __ANIMATED_KINEMATIC_ENTITY_H__

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/core/visual/AnimatedRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/definitions/KinematicEntity.h>

namespace game {

  class GAMESDK_DLL AnimatedKinematicEntity : public KinematicEntity {
  public:
    AnimatedKinematicEntity(int type,
                            GameBase* game,
                            std::map<int, sf::Texture*> animationStates,
                            std::vector<Shape<KinematicShapePhysics>*> shapes = std::vector<Shape<KinematicShapePhysics>*>(),
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
