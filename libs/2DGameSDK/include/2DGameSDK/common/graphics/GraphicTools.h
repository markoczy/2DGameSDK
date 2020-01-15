/**
 * @file GraphicTools.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief GraphicTools class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 */
#ifndef __GAME_GRAPHICTOOLS_H__
#define __GAME_GRAPHICTOOLS_H__

#include <cmath>
#include <tuple>
#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  /**
   * @brief GraphicTools provides Helper functions for graphics operations.
   */
  class GAMESDK_DLL GraphicTools {
  public:
    /**
     * @brief Converts degree value to radian
     * 
     * @param deg degree value
     * @return float radian value
     */
    static float DegToRad(float deg);

    /**
     * @brief Converts radian value to degree
     * 
     * @param rad radian value
     * @return float degree value
     */
    static float RadToDeg(float rad);

    /**
     * @brief Get the Boundary of a given rectangle as vector array.
     * 
     * @param rect the rectangle
     * @return std::vector<sf::Vector2f> the boundary
     */
    static std::vector<sf::Vector2f> GetRectBoundary(sf::FloatRect rect);

    /**
     * @brief Transforms points by a given transformation matrix
     * 
     * @param points the points to transform
     * @param transform the transform matrix 
     * @return std::vector<sf::Vector2f>  the transformed points
     */
    static std::vector<sf::Vector2f> TransformPoints(std::vector<sf::Vector2f> points, sf::Transform transform);

    /**
     * @brief Create a Uniform Vertex Array from a given set of points
     * 
     * @param points the points (locations)
     * @param type the SFML primitive type (triangles, quads, etc.)
     * @param color the desired color
     * @return sf::VertexArray 
     */
    static sf::VertexArray CreateUniformVertexArray(std::vector<sf::Vector2f> points, sf::PrimitiveType type, sf::Color color);

    /**
     * @brief Checks if two lines intersect
     * 
     * @param a1 start point 1
     * @param b1 end point 1
     * @param a2 start point 2
     * @param b2 end point 2
     * @return std::tuple<bool, sf::Vector2f> 
     */
    static std::tuple<bool, sf::Vector2f> LinesIntersect(sf::Vector2f a1, sf::Vector2f b1, sf::Vector2f a2, sf::Vector2f b2);

    /**
     * @brief Checks if two shapes intersect
     * 
     * @param shapeA first shape
     * @param shapeB second shape
     * @return std::tuple<bool, sf::Vector2f> 
     */
    static std::tuple<bool, sf::Vector2f> ShapesIntersect(std::vector<sf::Vector2f> shapeA, std::vector<sf::Vector2f> shapeB);

    /**
     * @brief Transforms visual position to physical position
     * 
     * @param visualPos the visual position
     * @param totalHeight the total (world-) height
     * @return cpVect the physical position
     */
    static cpVect GetPhysicalPos(sf::Vector2f visualPos, float totalHeight);

    /**
     * @brief Transforms physical position to visual position
     * 
     * @param physicalPos 
     * @param totalHeight 
     * @return sf::Vector2f 
     */
    static sf::Vector2f GetVisualPos(cpVect physicalPos, float totalHeight);

  private:
    /**
     * @brief Construct a new Graphic Tools object
     * 
    */
    GraphicTools() {}
  };

} // namespace game

#endif