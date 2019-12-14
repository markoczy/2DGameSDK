#include <2DGameSDK/core/effect/Effect.h>

namespace game {

  Effect::Effect(GameBase* game, std::vector<sf::Texture*> sequence, sf::Transform transform, int framesPerSprite) : GameObject(ObjectType::Effect, game), mRenderer(new SimpleSequenceRenderStrategy(game, sequence, framesPerSprite, 0, false)) {
    SetTransform(transform);
    game->GetStateManager()->AddVisualObject(this);
  }

  Effect::~Effect() {
    // delete mRenderer;
  }

  int Effect::GetZIndex() { return mZIndex; }

  void Effect::SetZIndex(int zIndex) {
    mZIndex = zIndex;
  }

  void Effect::SetTransform(sf::Transform transform) {
    mTransform = getGame()->GetPoseConverter()->GetVisualTransform(transform);
  }

  void Effect::SetSize(sf::Vector2f size) {
    mRenderer->SetSize(size);
  }

  void Effect::SetSize(int idx, sf::Vector2f size) {
    mRenderer->SetSize(idx, size);
  }

  void Effect::OnTick() {
    if(mRenderer->IsFinished()) onDestroy();
  }

  void Effect::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mTransform;
    mRenderer->OnRender(target, states);
  }

  void Effect::onDestroy() {
    getGame()->GetStateManager()->DestroyObject(this);
    getGame()->GetStateManager()->DestroyVisualObject(this);
  }
} // namespace game
