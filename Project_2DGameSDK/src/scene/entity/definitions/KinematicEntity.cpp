#include <2DGameSDK/scene/entity/definitions/KinematicEntity.h>

namespace game {

  KinematicEntity::KinematicEntity(int type, GameBase* game, RenderStrategy* renderer, std::vector<Shape<KinematicShapePhysics>*> shapes, bool isCollidable) : Entity(type, game), mRenderer(renderer), mShapes(shapes), mIsCollidable(isCollidable) {
    mBody = cpSpaceAddBody(game->GetPhysicalWorld(), cpBodyNewKinematic());
    cpBodySetUserData(mBody, new CollisionTarget(this, ObjectType::Entity));

    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
  }

  KinematicEntity::~KinematicEntity() {
    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      helpers::safeDelete(shape);
    }
    cpSpaceRemoveBody(space, mBody);
    cpBodyFree(mBody);
  }

  bool KinematicEntity::IsKinematic() {
    return true;
  }

  bool KinematicEntity::IsCollidable() {
    return mIsCollidable;
  }

  sf::Transform KinematicEntity::GetTransform() {
    return mTransform;
  }

  sf::Transform KinematicEntity::GetAccumulatedTransform() {
    return mAccTransform;
  }

  sf::Transform KinematicEntity::GetCombinedTransform() {
    return mCombinedTransform;
  }

  RenderStrategy* KinematicEntity::GetRenderer() {
    return mRenderer;
  }

  void KinematicEntity::OnTickEnded() {
    auto pose = getGame()->GetPoseConverter()->GetPhysicalPose(GetCombinedTransform());

    LOGD("Body Pos: (" << pose.origin.x << ", " << pose.origin.y << "), angle: " << pose.angle);
    cpBodySetPosition(mBody, pose.origin);
    cpBodySetAngle(mBody, pose.angle);
  }

  void KinematicEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    if(mRenderer && mRenderer->IsRenderEnabled()) {
      auto visTransform = getGame()->GetPoseConverter()->GetVisualTransform(GetCombinedTransform());
      states.transform = states.transform * visTransform;
      mRenderer->OnRender(target, visTransform);
    }

    auto options = getGame()->GetOptions();
    if(!(options.RenderCollisionMask || options.RenderAABB)) return;

    for(auto shape : mShapes) {
      if(options.RenderCollisionMask) shape->Render(target, sf::Color::Red, 1.0 / options.InitialZoom);
      if(options.RenderAABB) shape->RenderAABB(target, sf::Color::Magenta, 1.0 / options.InitialZoom);
    }
  }

  bool KinematicEntity::setTransform(sf::Transform transform) {
    mTransform = transform;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

  bool KinematicEntity::transform(sf::Transform transform) {
    // local y is inverted in visual model, so we have to invert the transform
    auto origin = transform.transformPoint(sf::Vector2f());
    auto newT = transform.translate(0, -2 * origin.y);

    mTransform = mTransform * newT;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

  bool KinematicEntity::setAccumulatedTransform(sf::Transform accumulated) {
    mAccTransform = accumulated;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

} // namespace game