#ifndef __GAME_GRAPHICTOOLS_H__
#define __GAME_GRAPHICTOOLS_H__

#include <vector>

#include <SFML/Graphics.hpp>

namespace game::helpers {

  class GrahicTools {
  public:
    static std::vector<sf::Vector2f> GetRectBoundary(sf::FloatRect rect);

    static std::vector<sf::Vector2f> TransformPoints(std::vector<sf::Vector2f>, sf::Transform transform);

    static sf::VertexArray CreateUniformVertexArray(std::vector<sf::Vector2f> points, sf::PrimitiveType type, sf::Color color);

  private:
    GrahicTools() {}
  };

} // namespace game::helpers

#endif