#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode {
  public:
    sf::Transform GetAccumulatedTransform();
  };

  SpriteTransformableEntity::
      SpriteTransformableEntity(int type,
                                sf::Texture* texture,
                                b2World* world,
                                bool isCollidable,
                                sf::Transformable initialTransform) : TransformableEntity(type, isCollidable), mSprite(*texture), mTransformable(initialTransform) {
    if(mIsCollidable) {
      mCollisionMask = helpers::GrahicTools::GetRectBoundary(mSprite.getLocalBounds());

      b2BodyDef def;
      def.type = b2_dynamicBody;
      auto pos = mTransformable.getPosition();
      def.position.Set(pos.x, pos.y);

      b2FixtureDef fix;
      fix.shape = &helpers::Converters::SfmlVectorsToB2Polygon(mCollisionMask);
      fix.density = 1.0f;
      fix.friction = 0.3f;

      mBody = world->CreateBody(&def);
      mBody->CreateFixture(&fix);
    }
  }

  SpriteTransformableEntity::
      SpriteTransformableEntity(int type,
                                sf::Texture* texture,
                                std::vector<sf::Vector2f> collisionMask,
                                b2World* world,
                                sf::Transformable initialTransform) : TransformableEntity(type, true), mSprite(*texture), mCollisionMask(collisionMask), mTransformable(initialTransform) {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    auto pos = mTransformable.getPosition();
    def.position.Set(pos.x, pos.y);

    b2FixtureDef fix;
    fix.shape = &helpers::Converters::SfmlVectorsToB2Polygon(mCollisionMask);
    fix.density = 1.0f;
    fix.friction = 0.3f;

    mBody = world->CreateBody(&def);
    mBody->CreateFixture(&fix);
  }

  SpriteTransformableEntity::~SpriteTransformableEntity() {
  }

  void SpriteTransformableEntity::Tick() {}

  void SpriteTransformableEntity::Render(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mTransformable.getTransform();
    //* Note: The render states contain the accumulated transformation
    target->draw(mSprite, states);
  }

  sf::Transformable* SpriteTransformableEntity::GetTransformable() {
    return &mTransformable;
  }

  sf::FloatRect SpriteTransformableEntity::GetAABB() {
    return (mGraphNode->GetAccumulatedTransform() * mSprite.getTransform()).transformRect(mSprite.getLocalBounds());
  }

  std::vector<sf::Vector2f> SpriteTransformableEntity::GetCollisionMask() {
    auto localToWorld = mGraphNode->GetAccumulatedTransform() * mSprite.getTransform();

    return helpers::GrahicTools::TransformPoints(mCollisionMask, localToWorld);
  }

} // namespace game