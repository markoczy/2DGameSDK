#ifndef __GAME_GRAPHICTOOLS_H__
#define __GAME_GRAPHICTOOLS_H__

#include <vector>

#include <SFML/Graphics.hpp>

namespace game::helpers {

  class GrahicTools {
  public:
    static std::vector<sf::Vector2f> RectToVertexArray(sf::FloatRect rect);

    static std::vector<sf::Vector2f> TransformVertexArray(std::vector<sf::Vector2f>, sf::Transform transform);

  private:
    GrahicTools() {}
  };

} // namespace game::helpers

#endif