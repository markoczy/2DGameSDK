#ifndef __AUDIO_CONTROLLER_H__
#define __AUDIO_CONTROLLER_H__

#include <map>

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/Audio.hpp>

namespace game {

  class GAMESDK_DLL AudioController {
  public:
    int AddSound(sf::SoundBuffer* sound);
    void PlayOnce(int id, float volume = 100);
    int PlayRepeated(int id, float volume = 100);
    void Stop(int id);
    void Delete(int id);

  private:
    std::map<int, sf::Sound*> mSounds;
  };

} // namespace game

#endif