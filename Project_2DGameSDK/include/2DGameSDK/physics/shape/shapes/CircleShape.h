/**
 * @file CircleShape.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief CircleShape class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
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
  /**
   * @brief Circle shape with center and radius
   * 
   * @tparam TPhysics The Shape Physics type
   */
  template <class TPhysics>
  class GAMESDK_DLL CircleShape : public Shape<TPhysics> {
  public:
    /**
     * @brief Constructs a new Circle Shape
     * 
     * @param game the game
     * @param definition the physics strategy
     * @param radius the radius
     * @param offset the circle center position
     */
    CircleShape(GameBase* game, TPhysics* definition, float radius, cpVect offset = cpv(0, 0)) : Shape<TPhysics>(ShapeType::Polygon, game, definition), mRadius(radius), mOffset(offset) {
    }

    /**
     * @brief Renders the shape
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) {
      auto shape = sf::CircleShape(mRadius);
      shape.setOrigin(sf::Vector2f(mRadius, mRadius));
      shape.setPosition(Shape<TPhysics>::getVisualPosition());
      shape.setRotation(Shape<TPhysics>::getVisualRotation());
      shape.setOutlineColor(color);
      shape.setOutlineThickness(stroke);
      shape.setFillColor(sf::Color::Transparent);
      target->draw(shape);
    }

    /**
     * @brief Creates a copy of the shape
     * 
     * @return Shape<TPhysics>* the copy
     */
    virtual Shape<TPhysics>* CopyTemplate() {
      return new CircleShape<TPhysics>(this->getGame(), this->getPhysics()->Copy(), mRadius, mOffset);
    }

  protected:
    float mRadius;
    cpVect mOffset;

    /**
     * @brief Initalizes the shape
     * 
     * @param body the chipmunk body
     * @return cpShape* the chipmunk shape
     */
    virtual cpShape* initShape(cpSpace*, cpBody* body) {
      auto shape = cpCircleShapeNew(body, mRadius, mOffset);
      return shape;
    }
  };

} // namespace game

#endif
