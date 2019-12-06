#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/graphics/GraphicTools.h>
#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/VisualObject.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/KinematicShapeDefinition.h>

namespace game {
  class GAMESDK_DLL Projectile : public VisualObject {
  public:
    Projectile(GameBase* game, int type, sf::Texture* texture, Shape<KinematicShapeDefinition>* shape, sf::Transform start, sf::Vector2f velocity);
    ~Projectile();

    virtual int GetZIndex();

    virtual void SetZIndex(int zIndex);

    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

  protected:
    GameBase* mGame;
    int mType;
    sf::Sprite mSprite;
    Shape<KinematicShapeDefinition>* mShape;
    int mZIndex = constants::DEFAULT_ZINDEX_PROJECTILE;
    cpBody* mBody;
  };
} // namespace game

#endif