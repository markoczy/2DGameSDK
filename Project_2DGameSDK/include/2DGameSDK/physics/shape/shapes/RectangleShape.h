#ifndef __RECTANGLE_SHAPE_H__
#define __RECTANGLE_SHAPE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/ShapeType.h>

namespace game {
  template <class TDefinition>
  class GAMESDK_DLL RectangleShape : public Shape<TDefinition> {
  public:
    RectangleShape(Game* game, TDefinition* definition, float width, float height) : Shape<TDefinition>(ShapeType::Rectangle, game, definition), mWidth(width), mHeight(height) {
    }

    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) {
      auto visOrigin = Shape<TDefinition>::getVisualPosition();
      float rot = Shape<TDefinition>::getVisualRotation();
      auto shape = sf::RectangleShape(sf::Vector2f(mWidth, mHeight));
      shape.setOrigin(mWidth / 2, mHeight / 2);
      shape.setPosition(visOrigin);
      shape.setRotation(rot);
      shape.setOutlineColor(color);
      shape.setOutlineThickness(stroke);
      shape.setFillColor(sf::Color::Transparent);
      target->draw(shape);
    }

  protected:
    float mWidth;
    float mHeight;

    virtual cpShape* initShape(cpSpace*, cpBody* body) {
      auto shape = cpBoxShapeNew(body, mWidth, mHeight, 0);
      return shape;
    }
  };

} // namespace game

#endif
