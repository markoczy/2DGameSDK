#ifndef __GAME_CONVERTERS_H__
#define __GAME_CONVERTERS_H__

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace game::helpers {

  class Converters {
  public:
    static b2PolygonShape SfmlVectorsToB2Polygon(std::vector<sf::Vector2f> vectors);
  };

} // namespace game::helpers

#endif