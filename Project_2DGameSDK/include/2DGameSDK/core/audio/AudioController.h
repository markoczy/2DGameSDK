/**
 * @file AudioController.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief AudioController class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __AUDIO_CONTROLLER_H__
#define __AUDIO_CONTROLLER_H__

#include <map>

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/Audio.hpp>

namespace game {

  class GAMESDK_DLL AudioController {
  public:
    /**
     * @brief Constructs a new Audio Controller
     * 
     * @param game the game
     */
    AudioController(GameBase* game);

    /**
     * @brief Updates the Audio Controller
     * 
     */
    void OnTick();

    /**
     * @brief Play a sound once
     * 
     * @param sound the sound
     * @param volume the volume
     */
    void PlayOnce(sf::SoundBuffer* sound, float volume = 100);

    /**
     * @brief Play a sound on repeat
     * 
     * @param sound the sound
     * @param volume the volume
     * @return int the identifier (to stop the sound)
     */
    int PlayRepeated(sf::SoundBuffer* sound, float volume = 100);

    /**
     * @brief Stops a sound by id
     * 
     * @param id the sound id
     */
    void Stop(int id);

    /**
     * @brief Slowly stops a sound by fading out
     * 
     * @param id the sound id
     * @param ticks the time until sound stops
     */
    void FadeOut(int id, int ticks);

  private:
    GameBase* mGame = nullptr;

    std::map<int, sf::Sound*> mSounds;
    std::vector<std::tuple<int, float>> mFading;
    sf::Clock mCleanupTimer;
    int mCleanupIntervall = 5000;
  };

} // namespace game

#endif