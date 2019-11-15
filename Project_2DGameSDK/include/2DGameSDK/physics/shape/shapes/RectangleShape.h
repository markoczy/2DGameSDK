#ifndef __RECTANGLE_SHAPE_H__
#define __RECTANGLE_SHAPE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/ShapeType.h>

namespace game {
  class GAMESDK_DLL RectangleShape : public Shape {
  public:
    RectangleShape(Game* game, ShapeDefinition* definition, float width, float height);

    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5);

  protected:
    float mWidth;
    float mHeight;

    virtual cpShape* initShape(cpSpace* space, cpBody* body);
  };

} // namespace game

#endif
