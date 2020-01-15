/**
 * @file RectangleShape.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief RectangleShape class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __RECTANGLE_SHAPE_H__
#define __RECTANGLE_SHAPE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/ShapeType.h>

namespace game {
  /**
   * @brief A Rectangle Shape
   * 
   * @tparam TPhysics The Shape Physics type 
   */
  template <class TPhysics>
  class GAMESDK_DLL RectangleShape : public Shape<TPhysics> {
  public:
    /**
     * @brief Constructs a new Rectangle Shape
     * 
     * @param game the game
     * @param definition the physics strategy
     * @param width the rectangle width
     * @param height the rectangle height
     */
    RectangleShape(GameBase* game, TPhysics* definition, float width, float height) : Shape<TPhysics>(ShapeType::Rectangle, game, definition), mWidth(width), mHeight(height) {
    }

    /**
     * @brief Renders the shape
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) {
      auto visOrigin = Shape<TPhysics>::getVisualPosition();
      float rot = Shape<TPhysics>::getVisualRotation();
      auto conv = this->getGame()->GetPoseConverter();
      auto dim = sf::Vector2f(conv->GetVisualDimension(mWidth), conv->GetVisualDimension(mHeight));
      auto shape = sf::RectangleShape(dim);

      shape.setOrigin(dim.x * 0.5, dim.y * 0.5);
      shape.setPosition(visOrigin);
      shape.setRotation(rot);
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
      return new RectangleShape<TPhysics>(this->getGame(), this->getPhysics()->Copy(), mWidth, mHeight);
    }

  protected:
    float mWidth;
    float mHeight;

    /**
     * @brief Initalizes the shape
     * 
     * @param body the chipmunk body
     * @return cpShape* the chipmunk shape
     */
    virtual cpShape* initShape(cpSpace*, cpBody* body) {
      auto shape = cpBoxShapeNew(body, mWidth, mHeight, 0);
      return shape;
    }
  };

} // namespace game

#endif
