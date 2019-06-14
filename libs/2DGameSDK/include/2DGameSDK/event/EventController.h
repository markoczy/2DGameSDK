/**
 * @file EventController.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Event Controller class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __EVENT_CONTROLLER_H__
#define __EVENT_CONTROLLER_H__

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/observable/ObservableBase.h>
#include <map>
#include <string>

namespace game {
  /**
   * @brief Stores and updates the Game Events
   * 
   */
  class GAMESDK_DLL EventController {
  public:
    /**
     * @brief Creates the EventController
     * 
     */
    EventController();

    /**
     * @brief Destroys the EventController
     * 
     */
    ~EventController();

    /**
     * @brief Adds a new event to observe (ownership is transferred)
     * 
     * @param event The event to observe
     * 
     * @return The unique id of the Event
     */
    int AddEvent(ObservableBase* event);

    /**
     * @brief Retreives the Event. Should not be used for Game Logic as
     *        the casting to a specific Observable is inefficient
     * 
     * @param id The unique id of the Event
     * 
     * @return The Event
     */
    ObservableBase* GetEvent(int id);

    /**
     * @brief Updates all Events
     * 
     */
    void Tick();

  private:
    int mEventCounter = 0;
    std::map<int, ObservableBase*> mEvents;
  };

} // namespace game

#endif