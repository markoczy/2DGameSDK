#include <2DGameSDK/core/projectile/Projectile.h>

namespace game {
  Projectile::Projectile(GameBase* game, int type, RenderStrategy* renderer, Shape<KinematicShapeDefinition>* shape, sf::Transform start, sf::Vector2f velocity) : GameObject(ObjectType::Projectile, game), mType(type), mRenderer(renderer), mShape(shape) {
    auto space = game->GetPhysicalWorld();
    mBody = cpSpaceAddBody(space, cpBodyNewKinematic());
    game->GetPhysicalWorld();
    mShape->AttachToBody(space, mBody);

    auto pose = game->GetPoseConverter()->GetPhysicalPose(start);
    cpBodySetPosition(mBody, pose.origin);
    cpBodySetAngle(mBody, pose.angle);
    cpSpaceReindexShapesForBody(space, mBody);

    cpBodySetVelocity(mBody, cpv(velocity.x, velocity.y));
    cpBodySetUserData(mBody, new CollisionTarget(this, ObjectType::Projectile));

    game->GetStateManager()->AddVisualObject(this);
  }

  Projectile::~Projectile() {
    auto space = getGame()->GetPhysicalWorld();
    helpers::safeDelete(mShape);
    cpSpaceRemoveBody(space, mBody);
    cpBodyFree(mBody);
  }

  int Projectile::GetZIndex() {
    return mZIndex;
  }

  void Projectile::SetZIndex(int zIndex) {
    mZIndex = zIndex;
  }

  void Projectile::OnTick() {}

  void Projectile::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    auto physPose = Pose<cpVect>{
        cpBodyGetPosition(mBody),
        (float)cpBodyGetAngle(mBody)};
    auto visPose = getGame()->GetPoseConverter()->GetVisualPose(physPose);

    states.transform = states.transform * sf::Transform().translate(visPose.origin).rotate(visPose.angle);
    mRenderer->OnRender(target, states);
  }

  int Projectile::OnCollision(CollisionEventType, cpArbiter*) {
    if(!mDestroying) {
      getGame()->GetStateManager()->DestroyObject(this);
      getGame()->GetStateManager()->DestroyVisualObject(this);
      mDestroying = true;
    }
    return 0;
  }

} // namespace game
