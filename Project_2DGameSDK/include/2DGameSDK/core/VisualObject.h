/**
 * @file VisualObject.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief VisualObject class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __VISUAL_OBJECT_H__
#define __VISUAL_OBJECT_H__

#include <SFML/Graphics.hpp>

namespace game {
  /**
   * @brief An object that can be rendered
   * 
   */
  class VisualObject {
  public:
    /**
     * @brief Renders the object
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default) = 0;

    /**
     * @brief Retreives the Z Index
     * 
     * @return int the Z Index
     */
    virtual int GetZIndex() = 0;

    /**
     * @brief Compares visual objects for sort
     * 
     * @param a object a
     * @param b object b
     * @return bool compare return value
     */
    static bool SortByZOrder(VisualObject* a, VisualObject* b) {
      return a->GetZIndex() < b->GetZIndex();
    }
  };
} // namespace game

#endif