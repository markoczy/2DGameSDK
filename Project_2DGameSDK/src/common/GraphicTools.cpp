#include <2DGameSDK/common/GraphicTools.h>

namespace game::helpers {

  std::vector<sf::Vector2f> GrahicTools::GetRectBoundary(sf::FloatRect rect) {
    auto ret = std::vector<sf::Vector2f>(4);
    ret[0] = sf::Vector2f(rect.left, rect.top);
    ret[1] = sf::Vector2f(rect.left, rect.top + rect.height);
    ret[2] = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
    ret[3] = sf::Vector2f(rect.left + rect.width, rect.top);
    return ret;
  }

  std::vector<sf::Vector2f> GrahicTools::TransformPoints(std::vector<sf::Vector2f> vertices, sf::Transform transform) {
    auto ret = std::vector<sf::Vector2f>(vertices.size());
    for(int i = 0; i < vertices.size(); i++) {
      ret[i] = transform.transformPoint(vertices[i]);
    }
    return ret;
  }

  sf::VertexArray GrahicTools::CreateUniformVertexArray(std::vector<sf::Vector2f> points, sf::PrimitiveType type, sf::Color color) {
    auto ret = sf::VertexArray(type, points.size());
    for(int i = 0; i < points.size(); i++) {
      ret[i].position = points[i];
      ret[i].color = color;
    }
    return ret;
  }

} // namespace game::helpers