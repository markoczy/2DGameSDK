#include <2DGameSDK/scene/entity/dynamic/SpriteDynamicEntity.h>

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  using namespace helpers;

  SpriteDynamicEntity::SpriteDynamicEntity(int type, Game* game, sf::Texture* texture, std::vector<DynamicShape*> shapes, bool isCollidable) : DynamicEntity(type, game, shapes, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);

    // if(isCollidable && shapes.size() == 0) {
    //   auto shape = new RectangleDynamicShape(getGame(), rect.width, rect.height);
    //   shape->AttachToBody(getGame()->GetPhysicalWorld(), mBody);
    //   mShapes.push_back(shape);
    // }
  }

  SpriteDynamicEntity::~SpriteDynamicEntity() {
  }

  void SpriteDynamicEntity::SetSize(sf::Vector2f size) {
    auto rect = mSprite.getTextureRect();
    mSprite.setScale(size.x / rect.width, size.y / rect.height);
  }

  void SpriteDynamicEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
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

  bool SpriteDynamicEntity::setTransform(sf::Transform transform) {
    auto origin = transform.transformPoint(sf::Vector2f());
    auto xUnit = transform.transformPoint(sf::Vector2f(1, 0));
    auto dir = xUnit - origin;
    float angle = atan2(dir.y, dir.x);

    LOGD("Body Pos: (" << origin.x << ", " << origin.y << "), angle: " << angle);
    cpBodySetPosition(mBody, cpv(origin.x, origin.y));
    cpBodySetAngle(mBody, angle);
    cpSpaceReindexShapesForBody(getGame()->GetPhysicalWorld(), mBody);
    return true;
  }

  void SpriteDynamicEntity::OnTick() {}

} // namespace game
