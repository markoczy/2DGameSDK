#ifndef __POINT_CONVERTER_H__
#define __POINT_CONVERTER_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/types/Pose.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL PoseConverter {
  public:
    PoseConverter(float worldWidth, float worldHeight, float meterPerPixel);

    cpVect GetPhysicalPos(sf::Vector2f visualPos);
    sf::Vector2f GetVisualPos(cpVect physicalPos);

    float GetPhysicalAngle(float visualAngle);
    float GetVisualAngle(float physicalAngle);

    float GetVisualDimension(float physicalDim);
    float GetPhysicalDimension(float visualDim);

    Pose<cpVect> GetPhysicalPose(Pose<sf::Vector2f> visualPose);
    Pose<cpVect> GetPhysicalPose(sf::Transform physicalTransform);
    Pose<sf::Vector2f> GetVisualPose(Pose<cpVect> physicalPose);
    sf::Transform GetVisualTransform(sf::Transform physicalTransform);

    sf::Vector2f GetVisualScale(sf::Vector2f textureSize, sf::Vector2f requiredPhysicalSize);

  private:
    float mWidth;
    float mHeight;
    float mPxToMeter;
  };
} // namespace game

#endif