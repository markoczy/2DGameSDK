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

  template <class TDefinition>
  class GAMESDK_DLL PolygonShape : public Shape<TDefinition> {
  public:
    PolygonShape(GameBase* game, TDefinition* definition, std::vector<cpVect> vertices) : Shape<TDefinition>(ShapeType::Polygon, game, definition), mVertices(vertices) {}

    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) {
      auto conv = this->getGame()->GetPoseConverter();
      auto shape = sf::ConvexShape(mVertices.size());
      for(size_t i = 0; i < mVertices.size(); i++) {
        auto pt = sf::Vector2f(conv->GetVisualDimension(mVertices[i].x), conv->GetVisualDimension(-mVertices[i].y));
        shape.setPoint(i, pt);
      }

      shape.setPosition(Shape<TDefinition>::getVisualPosition());
      shape.setRotation(Shape<TDefinition>::getVisualRotation());
      shape.setOutlineColor(color);
      shape.setOutlineThickness(stroke);
      shape.setFillColor(sf::Color::Transparent);
      target->draw(shape);
    }

    virtual Shape<TDefinition>* CopyTemplate() {
      return new PolygonShape<TDefinition>(this->getGame(), this->getDefinition()->Copy(), mVertices);
    }

  protected:
    std::vector<cpVect> mVertices;

    virtual cpShape* initShape(cpSpace*, cpBody* body) {
      auto shape = cpPolyShapeNewRaw(body, mVertices.size(), &mVertices[0], 0);
      return shape;
    }
  };
} // namespace game

#endif
