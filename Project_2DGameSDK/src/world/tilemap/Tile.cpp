#include <2DGameSDK/world/tilemap/Tile.h>

namespace game {
  Tile::Tile(Game* game) : GameObject(ObjectType::Tile, game) {}

  Tile::~Tile() {}
} // namespace game
