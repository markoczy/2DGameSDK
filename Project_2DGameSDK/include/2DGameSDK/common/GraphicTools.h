#ifndef __GAME_GRAPHICTOOLS_H__
#define __GAME_GRAPHICTOOLS_H__

#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

namespace game::helpers {

  class GrahicTools {
  public:
    static std::vector<sf::Vector2f> GetRectBoundary(sf::FloatRect rect);

    static std::vector<sf::Vector2f> TransformPoints(std::vector<sf::Vector2f> points, sf::Transform transform);

    static sf::VertexArray CreateUniformVertexArray(std::vector<sf::Vector2f> points, sf::PrimitiveType type, sf::Color color);

    static bool LinesIntersect(sf::Vector2f a1, sf::Vector2f b1, sf::Vector2f a2, sf::Vector2f b2);

    static bool ShapesIntersect(std::vector<sf::Vector2f> shapeA, std::vector<sf::Vector2f> shapeB);

  private:
    GrahicTools() {}
  };

} // namespace game::helpers

#endif