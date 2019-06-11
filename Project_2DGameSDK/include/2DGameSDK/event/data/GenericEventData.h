/**
 * @file GenericEventData.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Empty Event Data class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __GENERIC_EVENT_DATA_H__
#define __GENERIC_EVENT_DATA_H__

/**
 * @brief Event Data Object that can contain Data of any type
 * 
 * @tparam TData The Type of Data
 */
template <class TData>
struct GenericEventData {
  TData Data;
};

#endif