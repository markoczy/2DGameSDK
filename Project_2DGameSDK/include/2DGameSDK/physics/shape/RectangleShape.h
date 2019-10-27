#ifndef __RECTANGLE_SHAPE_H__
#define __RECTANGLE_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/graphics/PointConverter.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>

namespace game {
  class GAMESDK_DLL RectangleShape : public Shape {
  public:
    RectangleShape(float width, float height);
    sf::Shape* GetDrawableShape(PointConverter* converter);

  protected:
    virtual cpShape* initShape(cpSpace* space, cpBody* body);
    float mWidth;
    float mHeight;
  };
} // namespace game

#endif