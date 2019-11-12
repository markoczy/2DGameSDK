#ifndef __POINT_CONVERTER_H__
#define __POINT_CONVERTER_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL PoseConverter {
  public:
    PoseConverter(float worldWidth, float worldHeight, float meterPerPixel);
    cpVect GetPhysicalPos(sf::Vector2f visualPos);
    sf::Vector2f GetVisualPos(cpVect physicalPos);

    float GetVisualAngle(float physicalAngle);
    float GetPhysicalAngle(float visualAngle);

    float GetVisualDimension(float physicalDim);
    float GetPhysicalDimension(float visualDim);

  private:
    float mWidth;
    float mHeight;
    float mPxToMeter;
  };
} // namespace game

#endif