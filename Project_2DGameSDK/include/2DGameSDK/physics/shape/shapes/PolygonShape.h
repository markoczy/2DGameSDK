/**
 * @file PolygonShape.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief PolygonShape class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __POLYGON_SHAPE_H__
#define __POLYGON_SHAPE_H__

#include <vector>

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
   * @brief A Polygon shape
   * 
   * @tparam TPhysics The Shape Physics type 
   */
  template <class TPhysics>
  class GAMESDK_DLL PolygonShape : public Shape<TPhysics> {
  public:
    /**
     * @brief Constructs a new Polygon Shape
     * 
     * @param game the game
     * @param definition the physics strategy
     * @param vertices the polygon vertices
     */
    PolygonShape(GameBase* game, TPhysics* definition, std::vector<cpVect> vertices) : Shape<TPhysics>(ShapeType::Polygon, game, definition), mVertices(vertices) {}

    /**
     * @brief Renders the shape
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) {
      auto conv = this->getGame()->GetPoseConverter();
      auto shape = sf::ConvexShape(mVertices.size());
      for(size_t i = 0; i < mVertices.size(); i++) {
        auto pt = sf::Vector2f(conv->GetVisualDimension(mVertices[i].x), conv->GetVisualDimension(-mVertices[i].y));
        shape.setPoint(i, pt);
      }

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
      return new PolygonShape<TPhysics>(this->getGame(), this->geTPhysics()->Copy(), mVertices);
    }

  protected:
    std::vector<cpVect> mVertices;

    /**
     * @brief Initalizes the shape
     * 
     * @param body the chipmunk body
     * @return cpShape* the chipmunk shape
     */
    virtual cpShape* initShape(cpSpace*, cpBody* body) {
      auto shape = cpPolyShapeNewRaw(body, mVertices.size(), &mVertices[0], 0);
      return shape;
    }
  };
} // namespace game

#endif
