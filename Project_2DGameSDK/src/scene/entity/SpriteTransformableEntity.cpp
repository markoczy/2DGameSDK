#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;
using namespace game::constants;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  using namespace helpers;

  SpriteTransformableEntity::SpriteTransformableEntity(int type, Game* game, sf::Texture* texture, bool isCollidable) : TransformableEntity(type, game, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);

    if(isCollidable) {
      auto shape = new RectangleSensorShape(getGame(), rect.width, rect.height);
      shape->AttachToBody(getGame()->GetPhysicalWorld(), mBody);
      mShapes.push_back(shape);
    }
  }

  SpriteTransformableEntity::SpriteTransformableEntity(int type, Game* game, sf::Texture* texture, std::vector<SensorShape*> shapes) : TransformableEntity(type, game, true), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);

    mShapes = shapes;
    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
  }

  SpriteTransformableEntity::~SpriteTransformableEntity() {
  }

  void SpriteTransformableEntity::OnTick() {}

  void SpriteTransformableEntity::OnTickEnded() {
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

  void SpriteTransformableEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mCombinedTransform;
    target->draw(mSprite, states);

    auto options = getGame()->GetOptions();
    if(!(options.RenderCollisionMask || options.RenderAABB)) return;

    for(auto shape : mShapes) {
      if(options.RenderCollisionMask) shape->Render(target, sf::Color::Red, 0.5);
      if(options.RenderAABB) shape->RenderAABB(target, sf::Color::Magenta, 0.5);
    }
  }

} // namespace game