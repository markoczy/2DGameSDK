/**
 * @file OnKeyPress.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief On Key Press class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __ON_KEY_PRESS_H__
#define __ON_KEY_PRESS_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/data/EmptyEventData.h>
#include <2DGameSDK/event/observable/Observable.h>
#include <SFML/Window.hpp>
#include <tuple>

namespace game {

  /**
   * @brief Observable that triggers whenever a given Key is pressed
   * 
   */
  class GAMESDK_DLL OnKeyPress : public Observable<sf::Keyboard::Key> {
  public:
    /**
     * @brief Creates a new OnKeyPress Event
     * 
     * @param key The key identifier from SFML
     */
    OnKeyPress(sf::Keyboard::Key key);

  private:
    sf::Keyboard::Key mKey;

    /**
     * @brief Function that checks if the given key was pressed.
     * 
     * @return A tuple that specifies wether the key was pressed (value 0)
     *         event data (value 1) is always empty.
     */
    virtual std::tuple<bool, sf::Keyboard::Key> triggered();
  };
} // namespace game

#endif