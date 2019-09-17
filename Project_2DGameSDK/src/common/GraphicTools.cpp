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

  bool GrahicTools::LinesIntersect(sf::Vector2f a1, sf::Vector2f b1, sf::Vector2f a2, sf::Vector2f b2) {
    //TODO check parallel

    float n = ((a1.x * (a2.y - b2.y) - a1.y * (a2.x - b2.x) + a2.x * b2.y - a2.y * b2.x) / (a1.x * (a2.y - b2.y) - a1.y * (a2.x - b2.x) + a2.x * b1.y - a2.y * b1.x + b1.x * b2.y - b1.y * b2.x));
    if(n < 0 || n > 1) return false;

    float m = ((a1.x * (a2.y - b1.y) - a1.y * (a2.x - b1.x) + a2.x * b1.y - a2.y * b1.x) / (a1.x * (a2.y - b2.y) - a1.y * (a2.x - b2.x) + a2.x * b1.y - a2.y * b1.x + b1.x * b2.y - b1.y * b2.x));
    return (m >= 0 && m <= 1);
  }

  bool GrahicTools::ShapesIntersect(std::vector<sf::Vector2f> shapeA, std::vector<sf::Vector2f> shapeB) {
    for(int iA = 0; iA < shapeA.size() - 1; iA++) {
      for(int iB = 0; iB < shapeB.size() - 1; iB++) {
        if(LinesIntersect(shapeA[iA], shapeA[iA + 1], shapeB[iB], shapeB[iB + 1])) {
          return true;
        }
      }
    }
    return false;
  }

} // namespace game::helpers