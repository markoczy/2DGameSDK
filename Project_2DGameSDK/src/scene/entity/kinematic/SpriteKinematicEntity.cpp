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
    auto worldHeight = getGame()->GetWorld()->GetBounds().height;
    auto localOrigin = GetCombinedTransform().transformPoint(sf::Vector2f());
    auto localXUnit = GetCombinedTransform().transformPoint(sf::Vector2f(1, 0));
    auto localDir = localXUnit - localOrigin;
    auto physicalOrigin = GrahicTools::GetPhysicalPos(localOrigin, worldHeight);

    float angle = -atan2(localDir.y, localDir.x);

    LOGD("Body Pos: (" << physicalOrigin.x << ", " << physicalOrigin.y << "), angle: " << angle);
    cpBodySetPosition(mBody, physicalOrigin);
    cpBodySetAngle(mBody, angle);
  }

  void SpriteKinematicEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mCombinedTransform;
    target->draw(mSprite, states);

    auto origin = mCombinedTransform.transformPoint(sf::Vector2f());
    auto s = sf::CircleShape(3);
    s.setOrigin(3, 3);
    s.setFillColor(sf::Color::Green);
    s.setPosition(origin);
    target->draw(s);

    auto options = getGame()->GetOptions();
    if(!(options.RenderCollisionMask || options.RenderAABB)) return;

    for(auto shape : mShapes) {
      if(options.RenderCollisionMask) shape->Render(target, sf::Color::Red, 0.5);
      if(options.RenderAABB) shape->RenderAABB(target, sf::Color::Magenta, 0.5);
    }
  }

} // namespace game