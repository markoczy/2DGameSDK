#include <2DGameSDK/common/GraphicTools.h>

namespace game::helpers {

  const std::tuple<bool, sf::Vector2f> _NO_COLLISION = std::make_tuple(false, sf::Vector2f());

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

  std::tuple<bool, sf::Vector2f> GrahicTools::LinesIntersect(sf::Vector2f a1, sf::Vector2f b1, sf::Vector2f a2, sf::Vector2f b2) {
    //TODO check parallel

    float n = ((a1.x * (a2.y - b2.y) - a1.y * (a2.x - b2.x) + a2.x * b2.y - a2.y * b2.x) / (a1.x * (a2.y - b2.y) - a1.y * (a2.x - b2.x) + a2.x * b1.y - a2.y * b1.x + b1.x * b2.y - b1.y * b2.x));
    if(n < 0 || n > 1) return _NO_COLLISION;

    float m = ((a1.x * (a2.y - b1.y) - a1.y * (a2.x - b1.x) + a2.x * b1.y - a2.y * b1.x) / (a1.x * (a2.y - b2.y) - a1.y * (a2.x - b2.x) + a2.x * b1.y - a2.y * b1.x + b1.x * b2.y - b1.y * b2.x));
    if(m < 0 || m > 1) return _NO_COLLISION;

    return std::make_tuple(true, a1 + n * (b1 - a1));
  }

  std::tuple<bool, sf::Vector2f> GrahicTools::ShapesIntersect(std::vector<sf::Vector2f> shapeA, std::vector<sf::Vector2f> shapeB) {
    for(int iA = 0; iA < shapeA.size() - 1; iA++) {
      for(int iB = 0; iB < shapeB.size() - 1; iB++) {
        auto res = LinesIntersect(shapeA[iA], shapeA[iA + 1], shapeB[iB], shapeB[iB + 1]);
        if(std::get<0>(res)) {
          return res;
        }
      }
    }
    return _NO_COLLISION;
  }

} // namespace game::helpers