#include <2DGameSDK/scene/entity/static/SpriteStaticEntity.h>

namespace game {

  using namespace helpers;

  SpriteStaticEntity::SpriteStaticEntity(int type, Game* game, sf::Texture* texture, std::vector<Shape<StaticShapeDefinition>*> shapes, bool isCollidable) : StaticEntity(type, game, shapes, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);
  }

  SpriteStaticEntity::~SpriteStaticEntity() {
  }

  void SpriteStaticEntity::SetSize(sf::Vector2f size) {
    auto rect = mSprite.getTextureRect();
    mSprite.setScale(getGame()->GetPoseConverter()->GetVisualScale(sf::Vector2f(rect.width, rect.height), size));
  }

  void SpriteStaticEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    auto conv = getGame()->GetPoseConverter();
    auto pos = conv->GetVisualPos(cpBodyGetPosition(mBody));
    auto angle = conv->GetVisualAngle(cpBodyGetAngle(mBody));
    LOGD("Pos: (" << pos.x << ", " << pos.y << "), Angle: " << angle);

    mSprite.setPosition(pos);
    mSprite.setRotation(angle);

    target->draw(mSprite, states);

    auto options = getGame()->GetOptions();
    if(!(options.RenderCollisionMask || options.RenderAABB)) return;

    for(auto shape : mShapes) {
      if(options.RenderCollisionMask) shape->Render(target, sf::Color::Red, 1.0 / options.InitialZoom);
      if(options.RenderAABB) shape->RenderAABB(target, sf::Color::Magenta, 1.0 / options.InitialZoom);
    }
  }

  void SpriteStaticEntity::OnTick() {}

} // namespace game
