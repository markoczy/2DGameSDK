#include <2DGameSDK/common/graphics/GraphicTools.h>

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
    for(unsigned int i = 0; i < vertices.size(); i++) {
      ret[i] = transform.transformPoint(vertices[i]);
    }
    return ret;
  }

  sf::VertexArray GrahicTools::CreateUniformVertexArray(std::vector<sf::Vector2f> points, sf::PrimitiveType type, sf::Color color) {
    auto ret = sf::VertexArray(type, points.size());
    for(unsigned int i = 0; i < points.size(); i++) {
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
    for(unsigned int iA = 0; iA < shapeA.size() - 1; iA++) {
      for(unsigned int iB = 0; iB < shapeB.size() - 1; iB++) {
        auto res = LinesIntersect(shapeA[iA], shapeA[iA + 1], shapeB[iB], shapeB[iB + 1]);
        if(std::get<0>(res)) {
          return res;
        }
      }
    }
    return _NO_COLLISION;
  }

  sf::Transform GrahicTools::GetRotationAroundPoint(sf::Vector2f pt, float angleDeg) {
    float tx = pt.x;
    float ty = pt.y;
    float phi = constants::DEG_TO_RAD * angleDeg;
    return sf::Transform(cos(phi), sin(phi), cos(phi) * tx + sin(phi) * ty - tx,
                         -sin(phi), cos(phi), cos(phi) * ty - sin(phi) * tx - ty, 0, 0, 1);
  }

  cpVect GrahicTools::GetPhysicalPos(sf::Vector2f visualPos, float totalHeight) {
    return cpv(visualPos.x, totalHeight - visualPos.y);
  }

  sf::Vector2f GrahicTools::GetVisualPos(cpVect physicalPos, float totalHeight) {
    return sf::Vector2f(physicalPos.x, totalHeight - physicalPos.y);
  }
} // namespace game::helpers