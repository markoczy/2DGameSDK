#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/ShapeType.h>
#include <2DGameSDK/physics/shape/definitions/ShapeDefinition.h>

namespace game {
  // class Game;

  class GAMESDK_DLL Shape {
  public:
    Shape(ShapeType type, Game* game, ShapeDefinition* definition);

    void AttachToBody(cpSpace* space, cpBody* body);

    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) = 0;

    virtual void RenderAABB(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5);

    ShapeType GetType();
    cpSpace* GetRefSpace();
    cpBody* GetRefBody();
    cpShape* GetRefShape();

  protected:
    Game* getGame();
    sf::Vector2f getVisualPosition();
    float getVisualRotation();

    virtual cpShape* initShape(cpSpace* space, cpBody* body) = 0;

  private:
    ShapeType mType;
    Game* mGame = nullptr;
    ShapeDefinition* mDefinition = nullptr;
    cpSpace* mSpace = nullptr;
    cpBody* mBody = nullptr;
    cpShape* mShape = nullptr;
  };
} // namespace game

#endif