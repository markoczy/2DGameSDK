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
    AudioController(GameBase* game);
    void OnTick();
    void PlayOnce(sf::SoundBuffer* sound, float volume = 100);
    int PlayRepeated(sf::SoundBuffer* sound, float volume = 100);
    void Stop(int id);

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