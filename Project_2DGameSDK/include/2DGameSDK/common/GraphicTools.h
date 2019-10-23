#ifndef __GAME_GRAPHICTOOLS_H__
#define __GAME_GRAPHICTOOLS_H__

#include <cmath>
#include <tuple>
#include <vector>

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game::helpers {

  class GAMESDK_DLL GrahicTools {
  public:
    static std::vector<sf::Vector2f> GetRectBoundary(sf::FloatRect rect);

    static std::vector<sf::Vector2f> TransformPoints(std::vector<sf::Vector2f> points, sf::Transform transform);

    static sf::VertexArray CreateUniformVertexArray(std::vector<sf::Vector2f> points, sf::PrimitiveType type, sf::Color color);

    static std::tuple<bool, sf::Vector2f> LinesIntersect(sf::Vector2f a1, sf::Vector2f b1, sf::Vector2f a2, sf::Vector2f b2);

    static std::tuple<bool, sf::Vector2f> ShapesIntersect(std::vector<sf::Vector2f> shapeA, std::vector<sf::Vector2f> shapeB);

    static sf::Transform GetRotationAroundPoint(sf::Vector2f pt, float angleDeg);

    static sf::Transform GetTransformVisualToPhysical(sf::Vector2f visual, sf::FloatRect objectBounds, sf::FloatRect worldBounds);

    static sf::Transform GetTransformPhysicalToVisual(sf::Vector2f physical, sf::FloatRect objectBounds, sf::FloatRect worldBounds);

  private:
    GrahicTools() {}
  };

} // namespace game::helpers

#endif