#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/common/graphics/GraphicTools.h>
#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/VisualObject.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionEventType.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/KinematicShapeDefinition.h>

namespace game {
  class GAMESDK_DLL Projectile : public GameObject, public VisualObject {
  public:
    Projectile(GameBase* game, int type, RenderStrategy* renderer, Shape<KinematicShapeDefinition>* shapes, sf::Transform start, sf::Vector2f velocity);
    virtual ~Projectile();

    virtual int GetZIndex();

    virtual void SetZIndex(int zIndex);

    virtual void OnTick();

    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    virtual int OnCollision(CollisionEventType type, cpArbiter* arb);

  protected:
    int mType;
    RenderStrategy* mRenderer = nullptr;
    Shape<KinematicShapeDefinition>* mShape;
    int mZIndex = constants::DEFAULT_ZINDEX_PROJECTILE;
    cpBody* mBody;
    bool mDestroying = false;
  };
} // namespace game

#endif