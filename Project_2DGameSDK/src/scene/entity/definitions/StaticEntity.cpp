#include <2DGameSDK/scene/entity/definitions/StaticEntity.h>

namespace game {
  StaticEntity::StaticEntity(int type, GameBase* game, std::vector<Shape<StaticShapeDefinition>*> shapes, bool isCollidable) : Entity(type, game), mIsCollidable(isCollidable), mShapes(shapes) {
    mBody = cpSpaceAddBody(game->GetPhysicalWorld(), cpBodyNewStatic());
    cpBodySetUserData(mBody, new CollisionTarget(this, ObjectType::Entity));

    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
  }

  StaticEntity::~StaticEntity() {}

  bool StaticEntity::IsKinematic() { return false; }

  bool StaticEntity::IsCollidable() { return mIsCollidable; }

  sf::Transform StaticEntity::GetTransform() {
    auto pos = cpBodyGetPosition(mBody);
    auto rot = GraphicTools::RadToDeg(cpBodyGetAngle(mBody));
    return sf::Transform().translate(pos.x, pos.y).rotate(rot);
  }

  sf::Transform StaticEntity::GetAccumulatedTransform() {
    return constants::SF_TRANSFORM_I;
  }

  sf::Transform StaticEntity::GetCombinedTransform() {
    return GetTransform();
  }

  int StaticEntity::OnCollision(CollisionEventType, Entity*, cpArbiter*) {
    return 1;
  }

  int StaticEntity::OnWorldCollision(CollisionEventType, Tile*, cpArbiter*) {
    return 1;
  }

  bool StaticEntity::setTransform(sf::Transform transform) {
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
} // namespace game
