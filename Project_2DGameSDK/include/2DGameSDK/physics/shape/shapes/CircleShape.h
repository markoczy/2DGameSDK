#ifndef __CIRCLE_SHAPE_H__
#define __CIRCLE_SHAPE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/ShapeType.h>
#include <2DGameSDK/physics/shape/physics/ShapePhysics.h>

namespace game {
  template <class TDefinition>
  class GAMESDK_DLL CircleShape : public Shape<TDefinition> {
  public:
    CircleShape(GameBase* game, TDefinition* definition, float radius, cpVect offset = cpv(0, 0)) : Shape<TDefinition>(ShapeType::Polygon, game, definition), mRadius(radius), mOffset(offset) {
    }

    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) {
      auto shape = sf::CircleShape(mRadius);
      shape.setOrigin(sf::Vector2f(mRadius, mRadius));
      shape.setPosition(Shape<TDefinition>::getVisualPosition());
      shape.setRotation(Shape<TDefinition>::getVisualRotation());
      shape.setOutlineColor(color);
      shape.setOutlineThickness(stroke);
      shape.setFillColor(sf::Color::Transparent);
      target->draw(shape);
    }

    virtual Shape<TDefinition>* CopyTemplate() {
      return new CircleShape<TDefinition>(this->getGame(), this->getDefinition()->Copy(), mRadius, mOffset);
    }

  protected:
    float mRadius;
    cpVect mOffset;

    virtual cpShape* initShape(cpSpace*, cpBody* body) {
      auto shape = cpCircleShapeNew(body, mRadius, mOffset);
      return shape;
    }
  };

} // namespace game

#endif
