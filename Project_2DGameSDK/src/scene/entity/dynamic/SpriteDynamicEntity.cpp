#include <2DGameSDK/scene/entity/dynamic/SpriteDynamicEntity.h>

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  using namespace helpers;

  SpriteDynamicEntity::SpriteDynamicEntity(int type, Game* game, sf::Texture* texture, std::vector<Shape*> shapes, bool isCollidable) : DynamicEntity(type, game, shapes, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);
  }

  SpriteDynamicEntity::~SpriteDynamicEntity() {
  }

  void SpriteDynamicEntity::SetSize(sf::Vector2f size) {
    auto rect = mSprite.getTextureRect();
    mSprite.setScale(size.x / rect.width, size.y / rect.height);
  }

  void SpriteDynamicEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    auto physPose = Pose<cpVect>{
        cpBodyGetPosition(mBody),
        (float)cpBodyGetAngle(mBody)};
    auto visPose = getGame()->GetPoseConverter()->GetVisualPose(physPose);

    LOGD("Pos: (" << visPose.origin.x << ", " << visPose.origin.y << "), Angle: " << visPose.angle);

    mSprite.setPosition(visPose.origin);
    mSprite.setRotation(visPose.angle);

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
