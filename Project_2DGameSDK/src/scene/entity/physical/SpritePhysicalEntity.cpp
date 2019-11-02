#include <2DGameSDK/scene/entity/physical/SpritePhysicalEntity.h>

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  using namespace helpers;

  SpritePhysicalEntity::SpritePhysicalEntity(int type, Game* game, sf::Texture* texture, bool isCollidable) : PhysicalEntity(type, game, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);

    if(isCollidable) {
      auto shape = new RectangleDynamicShape(getGame(), rect.width, rect.height);
      shape->AttachToBody(getGame()->GetPhysicalWorld(), mBody);
      mShapes.push_back(shape);
    }
  }

  SpritePhysicalEntity::SpritePhysicalEntity(int type, Game* game, sf::Texture* texture, std::vector<DynamicShape*> shapes) : PhysicalEntity(type, game, true), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);

    mShapes = shapes;
    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
  }

  SpritePhysicalEntity::~SpritePhysicalEntity() {
  }

  void SpritePhysicalEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    auto conv = getGame()->GetPointConverter();
    auto pos = conv->GetVisualPos(cpBodyGetPosition(mBody));
    auto angle = -cpBodyGetAngle(mBody);

    mSprite.setPosition(pos);
    mSprite.setRotation(angle);

    target->draw(mSprite, states);

    auto options = getGame()->GetOptions();
    if(!(options.RenderCollisionMask || options.RenderAABB)) return;

    for(auto shape : mShapes) {
      if(options.RenderCollisionMask) shape->Render(target, sf::Color::Red, 0.5);
      if(options.RenderAABB) shape->RenderAABB(target, sf::Color::Magenta, 0.5);
    }
  }
} // namespace game
