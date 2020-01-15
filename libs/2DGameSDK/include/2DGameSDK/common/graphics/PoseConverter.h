/**
 * @file PoseConverter.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief PoseConverter class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __POINT_CONVERTER_H__
#define __POINT_CONVERTER_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/types/Pose.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  /**
   * @brief Converts pose (position + rotation) between the physical and
   *        the visual coordinate system.
   * 
   */
  class GAMESDK_DLL PoseConverter {
  public:
    /**
     * @brief Construct a new Pose Converter object
     * 
     * @param worldWidth the world's width
     * @param worldHeight the world's height
     * @param meterPerPixel the scale value
     */
    PoseConverter(float worldWidth, float worldHeight, float meterPerPixel);

    /**
     * @brief Converts visual position to physical position
     * 
     * @param visualPos the visual position
     * @return cpVect the physical position
     */
    cpVect GetPhysicalPos(sf::Vector2f visualPos);

    /**
     * @brief Converts physical position to visual position
     * 
     * @param physicalPos the physical position
     * @return sf::Vector2f the visual position
     */
    sf::Vector2f GetVisualPos(cpVect physicalPos);

    /**
     * @brief Converts visual angle to physical angle
     * 
     * @param visualAngle the visual angle
     * @return float the physical angle
     */
    float GetPhysicalAngle(float visualAngle);

    /**
     * @brief Converts physical angle to visual angle
     * 
     * @param physicalAngle the physical angle
     * @return float the visual angle
     */
    float GetVisualAngle(float physicalAngle);

    /**
     * @brief Converts physical dimension to visual dimension
     * 
     * @param physicalDim the physical dimension
     * @return float the visual dimension
     */
    float GetVisualDimension(float physicalDim);

    /**
     * @brief Converts visual dimension to physical dimension
     * 
     * @param visualDim the visual dimension
     * @return float the physical dimension
     */
    float GetPhysicalDimension(float visualDim);

    /**
     * @brief Converts visual pose (position + rotation) to physical pose
     * 
     * @param visualPose the visual pose
     * @return Pose<cpVect> the physical pose
     */
    Pose<cpVect> GetPhysicalPose(Pose<sf::Vector2f> visualPose);

    /**
     * @brief Converts physical transformation to physical pose
     * 
     * @param physicalTransform the transformation
     * @return Pose<cpVect> the pose
     */
    Pose<cpVect> GetPhysicalPose(sf::Transform physicalTransform);

    /**
     * @brief Converts physical pose to visual pose
     * 
     * @param physicalPose the physical pose
     * @return Pose<sf::Vector2f> the visual pose
     */
    Pose<sf::Vector2f> GetVisualPose(Pose<cpVect> physicalPose);

    /**
     * @brief Converts physical transformation to visual transformation
     * 
     * @param physicalTransform the physical transformation
     * @return sf::Transform the visual transformation
     */
    sf::Transform GetVisualTransform(sf::Transform physicalTransform);

    /**
     * @brief Returns visual scale vector from given physical size
     * 
     * @param textureSize the visual texture size
     * @param requiredPhysicalSize the desired physical size
     * @return sf::Vector2f the scale vector
     */
    sf::Vector2f GetVisualScale(sf::Vector2f textureSize, sf::Vector2f requiredPhysicalSize);

  private:
    float mWidth;
    float mHeight;
    float mPxToMeter;
  };
} // namespace game

#endif