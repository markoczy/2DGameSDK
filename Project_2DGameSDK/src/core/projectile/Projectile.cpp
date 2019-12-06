#include <2DGameSDK/core/projectile/Projectile.h>

namespace game {
  Projectile::Projectile(GameBase* game, int type, sf::Texture* texture, Shape<KinematicShapeDefinition>* shape, sf::Transform start, sf::Vector2f velocity) : mGame(game), mType(type), mSprite(*texture), mShape(shape) {
    auto rect = mSprite.getLocalBounds();
    mSprite.setOrigin(rect.width / 2.0f, rect.height / 2.0f);

    auto space = game->GetPhysicalWorld();
    mBody = cpSpaceAddBody(space, cpBodyNewKinematic());
    game->GetPhysicalWorld();
    mShape->AttachToBody(space, mBody);

    auto pose = mGame->GetPoseConverter()->GetPhysicalPose(start);
    cpBodySetPosition(mBody, pose.origin);
    cpBodySetAngle(mBody, pose.angle);
    cpSpaceReindexShapesForBody(space, mBody);

    cpBodySetVelocity(mBody, cpv(velocity.x, velocity.y));
    cpBodySetUserData(mBody, new CollisionTarget(this, ObjectType::Projectile));

    game->GetStateManager()->AddVisualObject(this);
  }

  Projectile::~Projectile() {}

  int Projectile::GetZIndex() {
    return mZIndex;
  }

  void Projectile::SetZIndex(int zIndex) {
    mZIndex = zIndex;
  }

  void Projectile::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    auto physPose = Pose<cpVect>{
        cpBodyGetPosition(mBody),
        (float)cpBodyGetAngle(mBody)};
    auto visPose = mGame->GetPoseConverter()->GetVisualPose(physPose);

    mSprite.setPosition(visPose.origin);
    mSprite.setRotation(visPose.angle);

    target->draw(mSprite, states);
  }
} // namespace game
