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
  template <class TDefinition>
  class GAMESDK_DLL RectangleShape : public Shape<TDefinition> {
  public:
    RectangleShape(GameBase* game, TDefinition* definition, float width, float height) : Shape<TDefinition>(ShapeType::Rectangle, game, definition), mWidth(width), mHeight(height) {
    }

    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) {
      auto visOrigin = Shape<TDefinition>::getVisualPosition();
      float rot = Shape<TDefinition>::getVisualRotation();
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

    virtual Shape<TDefinition>* CopyTemplate() {
      return new RectangleShape<TDefinition>(this->getGame(), this->getDefinition()->Copy(), mWidth, mHeight);
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
