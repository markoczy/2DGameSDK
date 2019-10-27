#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/graphics/PointConverter.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/ShapeType.h>

namespace game {
  class GAMESDK_DLL Shape {
  public:
    Shape(ShapeType type);

    virtual sf::Shape* GetDrawableShape(PointConverter* converter) = 0;
    void AttachToBody(cpSpace* space, cpBody* body);

  protected:
    virtual cpShape* initShape(cpSpace* space, cpBody* body) = 0;

    cpSpace* getRefSpace();
    cpBody* getRefBody();
    cpShape* getRefShape();

  private:
    ShapeType mType;
    cpSpace* mSpace = nullptr;
    cpBody* mBody = nullptr;
    cpShape* mShape = nullptr;
  };
} // namespace game

#endif