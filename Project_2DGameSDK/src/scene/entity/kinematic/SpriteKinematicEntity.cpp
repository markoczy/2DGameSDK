#include <2DGameSDK/scene/entity/kinematic/SpriteKinematicEntity.h>

using namespace sf;
using namespace game::constants;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  using namespace helpers;

  SpriteKinematicEntity::SpriteKinematicEntity(int type, Game* game, sf::Texture* texture, std::vector<KinematicShape*> shapes, bool isCollidable) : KinematicEntity(type, game, shapes, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getLocalBounds();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);

    // if(isCollidable) {
    //   auto shape = new RectangleKinematicShape(getGame(), rect.width, rect.height);
    //   shape->AttachToBody(getGame()->GetPhysicalWorld(), mBody);
    //   mShapes.push_back(shape);
    // }
  }

  SpriteKinematicEntity::~SpriteKinematicEntity() {
  }

  void SpriteKinematicEntity::SetSize(sf::Vector2f size) {
    auto rect = mSprite.getLocalBounds();
    mSprite.setScale(size.x / rect.width, size.y / rect.height);
  }

  void SpriteKinematicEntity::OnTick() {}

  void SpriteKinematicEntity::OnTickEnded() {
    auto origin = GetCombinedTransform().transformPoint(sf::Vector2f());
    auto xUnit = GetCombinedTransform().transformPoint(sf::Vector2f(1, 0));
    auto dir = xUnit - origin;
    float angle = -atan2(dir.y, dir.x);

    LOGD("Body Pos: (" << origin.x << ", " << origin.y << "), angle: " << angle);
    cpBodySetPosition(mBody, cpv(origin.x, origin.y));
    cpBodySetAngle(mBody, angle);
  }

  void SpriteKinematicEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    auto origin = GetCombinedTransform().transformPoint(sf::Vector2f());
    auto xUnit = GetCombinedTransform().transformPoint(sf::Vector2f(1, 0));
    auto conv = getGame()->GetPoseConverter();
    auto visOrigin = conv->GetVisualPos(cpv(origin.x, origin.y));
    auto visXUnit = conv->GetVisualPos(cpv(xUnit.x, xUnit.y));
    auto visDir = visXUnit - visOrigin;
    float visAngle = conv->GetVisualAngle(-atan2(visDir.y, visDir.x));
    // float visAngle = atan2(visDir.y, visDir.x);

    states.transform = states.transform * sf::Transform().translate(visOrigin).rotate(visAngle);
    target->draw(mSprite, states);

    auto options = getGame()->GetOptions();
    if(!(options.RenderCollisionMask || options.RenderAABB)) return;

    for(auto shape : mShapes) {
      if(options.RenderCollisionMask) shape->Render(target, sf::Color::Red, 1.0 / options.InitialZoom);
      if(options.RenderAABB) shape->RenderAABB(target, sf::Color::Magenta, 1.0 / options.InitialZoom);
    }
  }

} // namespace game