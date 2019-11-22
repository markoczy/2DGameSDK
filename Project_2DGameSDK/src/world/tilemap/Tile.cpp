#include <2DGameSDK/world/tilemap/Tile.h>

namespace game {
  // Tile::Tile(GameBase* game, Tile::Definition definition) : GameObject(ObjectType::Tile, game), mDefinition(definition) {}

  // Tile::~Tile() {
  //   helpers::safeDelete(mSprite);
  // }

  // sf::Texture* Tile::GetTexture() {
  //   return mTexture;
  // }

  // Material* Tile::GetMaterial() {
  //   return mMaterial;
  // }

  // Tile::Definition* Tile::GetDefinition() {
  //   return &mDefinition;
  // }

  // void Tile::SetTexture(sf::Texture* texture) {
  //   mTexture = texture;
  //   mSprite = new sf::Sprite(*texture);
  //   auto bounds = mSprite->getLocalBounds();
  //   auto pos = sf::Vector2f(mDefinition.X * bounds.width, mDefinition.Y * bounds.height);
  //   LOGD("Position: (" << pos.x << ", " << pos.y << ")");
  //   mSprite->setPosition(pos);
  // }

  // void Tile::SetMaterial(Material* material) {
  //   mMaterial = material;
  // }

  // void Tile::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
  //   if(mSprite != nullptr) {
  //     target->draw(*mSprite, states);
  //   }
  // }
} // namespace game
