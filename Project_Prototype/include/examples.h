#ifndef __EXAMPLES_H__
#define __EXAMPLES_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/Common.h>
#include <2DGameSDK/Core.h>
#include <2DGameSDK/Event.h>
#include <2DGameSDK/Physics.h>
#include <2DGameSDK/Scene.h>
#include <2DGameSDK/World.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <tuple>

/**
 * @brief Creates two rotating Entities where the second is child of the first
 * 
 * @return int success state
 */
int minimalDemo();

/**
 * @brief Creates a ball that is controllable by the player
 * 
 * @param zoom The initial zoom (2 or more recommended)
 * @return int success state
 */
int playerDemo(float zoom = 2.0);

/**
 * @brief Creates a simple GTA2-like character controller
 * 
 * @param zoom The initial zoom (2 or more recommended)
 * @return int success state
 */
int playerDemoGTA2(float zoom = 2.0);

/**
 * @brief Creates a grass surface with a flying chopper (heli)
 * 
 * @return int success state
 */
int chopperDemo();

int physicsDemo();

int prototype1();

#endif