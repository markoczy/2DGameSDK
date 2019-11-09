#ifndef __CIRCLE_SHAPE_H__
#define __CIRCLE_SHAPE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/ShapeType.h>

namespace game {
  class GAMESDK_DLL CircleShape : virtual public Shape {
  public:
    CircleShape(Game* game, float radius, cpVect offset = cpv(0, 0));

    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5);

  protected:
    float mRadius;
    cpVect mOffset;

    virtual cpShape* initShape(cpSpace* space, cpBody* body);
  };

} // namespace game

#endif
