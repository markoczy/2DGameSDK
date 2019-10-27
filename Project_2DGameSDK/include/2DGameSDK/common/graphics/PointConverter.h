#ifndef __POINT_CONVERTER_H__
#define __POINT_CONVERTER_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL PointConverter {
  public:
    PointConverter(float worldWidth, float worldHeight);
    cpVect GetPhysicalPos(sf::Vector2f visualPos);
    sf::Vector2f GetVisualPos(cpVect physicalPos);

  private:
    float mWidth;
    float mHeight;
  };
} // namespace game

#endif