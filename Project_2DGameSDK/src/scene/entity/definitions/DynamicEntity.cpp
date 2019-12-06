#include <2DGameSDK/scene/entity/definitions/DynamicEntity.h>

namespace game {
  DynamicEntity::DynamicEntity(int type, GameBase* game, std::vector<Shape<DynamicShapeDefinition>*> shapes, bool isCollidable) : Entity(type, game), mIsCollidable(isCollidable), mShapes(shapes) {
    mBody = cpSpaceAddBody(game->GetPhysicalWorld(), cpBodyNew(0, 0));
    cpBodySetUserData(mBody, new CollisionTarget(this, ObjectType::Entity));

    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
  }

  DynamicEntity::~DynamicEntity() {}

  bool DynamicEntity::IsKinematic() {
    return false;
  }

  bool DynamicEntity::IsCollidable() {
    return mIsCollidable;
  }

  sf::Transform DynamicEntity::GetTransform() {
    auto pos = cpBodyGetPosition(mBody);

    auto rot = GraphicTools::RadToDeg(cpBodyGetAngle(mBody));
    return sf::Transform().translate(pos.x, pos.y).rotate(rot);
  }

  sf::Transform DynamicEntity::GetAccumulatedTransform() {
    return constants::SF_TRANSFORM_I;
  }

  sf::Transform DynamicEntity::GetCombinedTransform() {
    return GetTransform();
  }

  void DynamicEntity::SetMass(float mass) {
    cpBodySetMass(mBody, mass);
  }

  void DynamicEntity::SetMoment(float moment) {
    cpBodySetMoment(mBody, moment);
  }

  void DynamicEntity::SetVelocity(cpVect velocity) {
    cpBodySetVelocity(mBody, velocity);
  }

  void DynamicEntity::SetForce(cpVect force) {
    cpBodySetForce(mBody, force);
  }

  void DynamicEntity::SetAngularVelocity(float angularVelocity) {
    cpBodySetAngularVelocity(mBody, angularVelocity);
  }

  void DynamicEntity::SetTorque(float torque) {
    cpBodySetTorque(mBody, torque);
  }

  int DynamicEntity::OnCollision(CollisionEventType, Entity*, cpArbiter*) {
    return 1;
  }

  int DynamicEntity::OnWorldCollision(CollisionEventType, Tile*, cpArbiter*) {
    return 1;
  }

  bool DynamicEntity::setTransform(sf::Transform transform) {
    auto pose = getGame()->GetPoseConverter()->GetPhysicalPose(transform);

    LOGD("Body Pos: (" << pose.origin.x << ", " << pose.origin.y << "), angle: " << pose.angle);
    cpBodySetPosition(mBody, pose.origin);
    cpBodySetAngle(mBody, pose.angle);
    cpSpaceReindexShapesForBody(getGame()->GetPhysicalWorld(), mBody);
    return true;
  }

} // namespace game
