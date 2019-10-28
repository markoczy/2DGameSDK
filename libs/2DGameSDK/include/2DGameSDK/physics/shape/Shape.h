#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/graphics/PointConverter.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/ShapeType.h>

namespace game {
  class Game;

  class GAMESDK_DLL Shape {
  public:
    Shape(ShapeType type);

    void AttachToBody(cpSpace* space, cpBody* body);

    virtual void Render(sf::RenderTarget* target, PointConverter* converter, sf::Color color = sf::Color::Black, float stroke = 0.5) = 0;

    cpSpace* GetRefSpace();
    cpBody* GetRefBody();
    cpShape* GetRefShape();

  protected:
    virtual cpShape* initShape(cpSpace* space, cpBody* body) = 0;

  private:
    ShapeType mType;
    cpSpace* mSpace = nullptr;
    cpBody* mBody = nullptr;
    cpShape* mShape = nullptr;
  };
} // namespace game

#endif