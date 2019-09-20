#include <2DGameSDK/common/Converters.h>

namespace game::helpers {

  b2PolygonShape Converters::SfmlVectorsToB2Polygon(std::vector<sf::Vector2f> vectors) {
    b2Vec2 vertices[vectors.size()];
    for(unsigned int i = 0; i < vectors.size(); i++) {
      auto vec = vectors[i];
      vertices[i].Set(vec.x, vec.y);
    }
    b2PolygonShape polygon;
    polygon.Set(vertices, vectors.size());
  }

} // namespace game::helpers