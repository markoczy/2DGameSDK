#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/ShapeType.h>
#include <2DGameSDK/physics/shape/definitions/ShapeDefinition.h>

namespace game {
  // class Game;

  template <class TDefinition>
  class GAMESDK_DLL Shape {
  public:
    Shape(ShapeType type, GameBase* game, TDefinition* definition) : mType(type), mGame(game), mDefinition(definition) {}

    void AttachToBody(cpSpace* space, cpBody* body) {
      mSpace = space;
      mBody = body;

      mShape = initShape(space, body);
      mDefinition->InitProperties(space, body, mShape);
      cpSpaceAddShape(space, mShape);
    }

    ShapeType GetType() {
      return mType;
    }

    cpSpace* GetRefSpace() {
      return mSpace;
    }

    cpBody* GetRefBody() {
      return mBody;
    }

    cpShape* GetRefShape() {
      return mShape;
    }

    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) = 0;

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

    virtual Shape<TDefinition>* CopyTemplate() = 0;

  protected:
    GameBase* getGame() {
      return mGame;
    }

    TDefinition* getDefinition() {
      return mDefinition;
    }

    sf::Vector2f getVisualPosition() {
      auto converter = getGame()->GetPoseConverter();
      return converter->GetVisualPos(cpBodyGetPosition(mBody));
    }

    float getVisualRotation() {
      auto converter = getGame()->GetPoseConverter();
      return converter->GetVisualAngle(cpBodyGetAngle(mBody));
    }

    virtual cpShape* initShape(cpSpace* space, cpBody* body) = 0;

  private:
    ShapeType mType;
    GameBase* mGame = nullptr;
    TDefinition* mDefinition = nullptr;
    cpSpace* mSpace = nullptr;
    cpBody* mBody = nullptr;
    cpShape* mShape = nullptr;
  };

} // namespace game

#endif