/**
 * @file EmptyEventData.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Empty Event Data class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __EMPTY_EVENT_DATA_H__
#define __EMPTY_EVENT_DATA_H__

namespace game {

  /**
   * @brief Event Data Object that does not contain any Data
   * 
   */
  class EmptyEventData {};

  namespace constants {
    /**
     * @brief Constant of an EmptyEventData class
     * 
     */
    const EmptyEventData EMPTY_EVENT_DATA = EmptyEventData();
  } // namespace constants

} // namespace game

#endif