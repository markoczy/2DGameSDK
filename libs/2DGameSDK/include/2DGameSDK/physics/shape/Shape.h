/**
 * @file Shape.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Shape class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/ShapeType.h>
#include <2DGameSDK/physics/shape/physics/ShapePhysics.h>

namespace game {
  /**
   * @brief Generic Shape class
   * 
   * @tparam TPhysics 
   */
  template <class TPhysics>
  class GAMESDK_DLL Shape {
  public:
    /**
     * @brief Constructs a new Shape
     * 
     * @param type the shape type
     * @param game the game
     * @param definition the physics type
     */
    Shape(ShapeType type, GameBase* game, TPhysics* definition) : mType(type), mGame(game), mDefinition(definition) {}

    /**
     * @brief Destroys the Shape
     * 
     */
    virtual ~Shape() {
      if(mShape) {
        cpSpaceRemoveShape(mSpace, mShape);
        cpShapeFree(mShape);
      }
    }

    /**
     * @brief Assigns shape to a chipmunk body
     * 
     * @param space the chipmunk space
     * @param body the chipmunk body
     */
    void AttachToBody(cpSpace* space, cpBody* body) {
      mSpace = space;
      mBody = body;

      mShape = initShape(space, body);
      mDefinition->InitProperties(space, body, mShape);
      cpSpaceAddShape(space, mShape);
    }

    /**
     * @brief Retreives the shape Type
     * 
     * @return ShapeType the type
     */
    ShapeType GetType() {
      return mType;
    }

    /**
     * @brief Retreives the chipmunk Space
     * 
     * @return cpSpace* the space
     */
    cpSpace* GetRefSpace() {
      return mSpace;
    }

    /**
     * @brief Retreives the chipmunk Body
     * 
     * @return cpBody* the body
     */
    cpBody* GetRefBody() {
      return mBody;
    }

    /**
     * @brief Retreives the chipmunk Shape
     * 
     * @return cpShape* the shape
     */
    cpShape* GetRefShape() {
      return mShape;
    }

    /**
     * @brief Renders the shape
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) = 0;

    /**
     * @brief Renders the shape's axis aligned bounding box
     * 
     * @param target the render target
     * @param color the color
     * @param stroke the stroke width
     */
    virtual void RenderAABB(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) {
      auto bb = cpShapeCacheBB(mShape);

      auto conv = getGame()->GetPoseConverter();
      auto topLeftVis = conv->GetVisualPos(cpv(bb.l, bb.t));
      auto bottomRightVis = conv->GetVisualPos(cpv(bb.r, bb.b));
      auto visBB = sf::FloatRect(topLeftVis.x,
                                 topLeftVis.y,
                                 bottomRightVis.x - topLeftVis.x,
                                 bottomRightVis.y - topLeftVis.y);

      auto rect = sf::RectangleShape(sf::Vector2f(visBB.width, visBB.height));
      rect.setPosition(visBB.left, visBB.top);
      rect.setOutlineColor(color);
      rect.setOutlineThickness(stroke);
      rect.setFillColor(sf::Color::Transparent);
      target->draw(rect);
    }

    /**
     * @brief Creates a copy of the shape
     * 
     * @return Shape<TPhysics>* the copy
     */
    virtual Shape<TPhysics>* CopyTemplate() = 0;

  protected:
    /**
     * @brief Retreives the Game
     * 
     * @return GameBase* the game
     */
    GameBase* getGame() {
      return mGame;
    }

    /**
     * @brief Retreives the Physics strategy
     * 
     * @return TPhysics* the physics strategy
     */
    TPhysics* getPhysics() {
      return mDefinition;
    }

    /**
     * @brief Retreives the current Visual Position
     * 
     * @return sf::Vector2f the position
     */
    sf::Vector2f getVisualPosition() {
      auto converter = getGame()->GetPoseConverter();
      return converter->GetVisualPos(cpBodyGetPosition(mBody));
    }

    /**
     * @brief Retreives the current Visual Rotation
     * 
     * @return float the rotation
     */
    float getVisualRotation() {
      auto converter = getGame()->GetPoseConverter();
      return converter->GetVisualAngle(cpBodyGetAngle(mBody));
    }

    /**
     * @brief Initalizes the shape
     * 
     * @param body the chipmunk body
     * @return cpShape* the chipmunk shape
     */
    virtual cpShape* initShape(cpSpace* space, cpBody* body) = 0;

  private:
    ShapeType mType;
    GameBase* mGame = nullptr;
    TPhysics* mDefinition = nullptr;
    cpSpace* mSpace = nullptr;
    cpBody* mBody = nullptr;
    cpShape* mShape = nullptr;
  };

} // namespace game

#endif