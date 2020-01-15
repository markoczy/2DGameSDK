#include <2DGameSDK/scene/entity/definitions/StaticEntity.h>

namespace game {
  StaticEntity::StaticEntity(int type, GameBase* game, RenderStrategy* renderer, std::vector<Shape<StaticShapePhysics>*> shapes, bool isCollidable) : Entity(type, game), mRenderer(renderer), mIsCollidable(isCollidable), mShapes(shapes) {
    mBody = cpSpaceAddBody(game->GetPhysicalWorld(), cpBodyNewStatic());
    cpBodySetUserData(mBody, new CollisionTarget(this, ObjectType::Entity));

    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
  }

  StaticEntity::~StaticEntity() {
    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      helpers::safeDelete(shape);
    }
    cpSpaceRemoveBody(space, mBody);
    cpBodyFree(mBody);
  }

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

  RenderStrategy* StaticEntity::GetRenderer() {
    return mRenderer;
  }

  void StaticEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    if(mRenderer && mRenderer->IsRenderEnabled()) {
      auto physPose = Pose<cpVect>{
          cpBodyGetPosition(mBody),
          (float)cpBodyGetAngle(mBody)};
      auto visPose = getGame()->GetPoseConverter()->GetVisualPose(physPose);

      LOGD("Pos: (" << visPose.origin.x << ", " << visPose.origin.y << "), Angle:" << visPose.angle);

      states.transform = states.transform * sf::Transform().translate(visPose.origin).rotate(visPose.angle);
      mRenderer->OnRender(target, states);
    }
    auto options = getGame()->GetOptions();
    if(!(options.RenderCollisionMask || options.RenderAABB)) return;

    for(auto shape : mShapes) {
      if(options.RenderCollisionMask) shape->Render(target, sf::Color::Red, 1.0 / options.InitialZoom);
      if(options.RenderAABB) shape->RenderAABB(target, sf::Color::Magenta, 1.0 / options.InitialZoom);
    }
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
