#include <2DGameSDK/scene/entity/kinematic/SpriteKinematicEntity.h>

using namespace sf;
using namespace game::constants;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  using namespace helpers;

  SpriteKinematicEntity::SpriteKinematicEntity(int type, Game* game, sf::Texture* texture, std::vector<Shape<KinematicShapeDefinition>*> shapes, bool isCollidable) : KinematicEntity(type, game, shapes, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getLocalBounds();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);
  }

  SpriteKinematicEntity::~SpriteKinematicEntity() {
  }

  void SpriteKinematicEntity::SetSize(sf::Vector2f size) {
    auto rect = mSprite.getTextureRect();
    mSprite.setScale(getGame()->GetPoseConverter()->GetVisualScale(sf::Vector2f(rect.width, rect.height), size));
  }

  void SpriteKinematicEntity::OnTick() {}

  void SpriteKinematicEntity::OnTickEnded() {
    auto pose = getGame()->GetPoseConverter()->GetPhysicalPose(GetCombinedTransform());

    LOGD("Body Pos: (" << pose.origin.x << ", " << pose.origin.y << "), angle: " << pose.angle);
    cpBodySetPosition(mBody, pose.origin);
    cpBodySetAngle(mBody, pose.angle);
  }

  void SpriteKinematicEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    auto visTransform = getGame()->GetPoseConverter()->GetVisualTransform(GetCombinedTransform());
    states.transform = states.transform * visTransform;
    target->draw(mSprite, states);

    auto options = getGame()->GetOptions();
    if(!(options.RenderCollisionMask || options.RenderAABB)) return;

    for(auto shape : mShapes) {
      if(options.RenderCollisionMask) shape->Render(target, sf::Color::Red, 1.0 / options.InitialZoom);
      if(options.RenderAABB) shape->RenderAABB(target, sf::Color::Magenta, 1.0 / options.InitialZoom);
    }
  }

} // namespace game