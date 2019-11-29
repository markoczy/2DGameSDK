#include <2DGameSDK/scene/entity/dynamic/SpriteDynamicEntity.h>

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  using namespace helpers;

  SpriteDynamicEntity::SpriteDynamicEntity(int type, Game* game, sf::Texture* texture, std::vector<Shape<DynamicShapeDefinition>*> shapes, bool isCollidable) : DynamicEntity(type, game, shapes, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);
  }

  SpriteDynamicEntity::~SpriteDynamicEntity() {
  }

  void SpriteDynamicEntity::SetSize(sf::Vector2f size) {
    auto rect = mSprite.getTextureRect();
    mSprite.setScale(getGame()->GetPoseConverter()->GetVisualScale(sf::Vector2f(rect.width, rect.height), size));
  }

  void SpriteDynamicEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    auto physPose = Pose<cpVect>{
        cpBodyGetPosition(mBody),
        (float)cpBodyGetAngle(mBody)};
    auto visPose = getGame()->GetPoseConverter()->GetVisualPose(physPose);

    LOGD("Pos: (" << visPose.origin.x << ", " << visPose.origin.y << "), Angle: " << visPose.angle);

    mSprite.setPosition(visPose.origin);
    mSprite.setRotation(visPose.angle);

    target->draw(mSprite, states);

    auto options = getGame()->GetOptions();
    if(!(options.RenderCollisionMask || options.RenderAABB)) return;

    for(auto shape : mShapes) {
      if(options.RenderCollisionMask) shape->Render(target, sf::Color::Red, 1.0 / options.InitialZoom);
      if(options.RenderAABB) shape->RenderAABB(target, sf::Color::Magenta, 1.0 / options.InitialZoom);
    }
  }

  void SpriteDynamicEntity::OnTick() {}

} // namespace game
