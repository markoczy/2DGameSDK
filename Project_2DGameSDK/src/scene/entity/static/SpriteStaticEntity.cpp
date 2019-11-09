#include <2DGameSDK/scene/entity/static/SpriteStaticEntity.h>

namespace game {

  using namespace helpers;

  SpriteStaticEntity::SpriteStaticEntity(int type, Game* game, sf::Texture* texture, std::vector<StaticShape*> shapes, bool isCollidable) : StaticEntity(type, game, shapes, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);
  }

  SpriteStaticEntity::~SpriteStaticEntity() {
  }

  void SpriteStaticEntity::SetSize(sf::Vector2f size) {
    auto rect = mSprite.getTextureRect();
    mSprite.setScale(size.x / rect.width, size.y / rect.height);
  }

  void SpriteStaticEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    auto conv = getGame()->GetPointConverter();
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

  bool SpriteStaticEntity::setTransform(sf::Transform transform) {
    auto worldHeight = getGame()->GetWorld()->GetBounds().height;
    auto localOrigin = transform.transformPoint(sf::Vector2f());
    auto localXUnit = transform.transformPoint(sf::Vector2f(1, 0));
    auto localDir = localXUnit - localOrigin;
    auto physicalOrigin = GrahicTools::GetPhysicalPos(localOrigin, worldHeight);
    float angle = -atan2(localDir.y, localDir.x);

    LOGD("Body Pos: (" << physicalOrigin.x << ", " << physicalOrigin.y << "), angle: " << angle);
    cpBodySetPosition(mBody, physicalOrigin);
    cpBodySetAngle(mBody, angle);
    cpSpaceReindexShapesForBody(getGame()->GetPhysicalWorld(), mBody);
    return true;
  }

  void SpriteStaticEntity::OnTick() {}

} // namespace game
