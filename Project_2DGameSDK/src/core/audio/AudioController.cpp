#include <2DGameSDK/core/audio/AudioController.h>

using namespace std;

namespace game {
  int _counter = 0;

  void AudioController::OnTick() {
    int elapsed = mCleanupTimer.getElapsedTime().asMilliseconds();
    if(elapsed < mCleanupIntervall) return;

    for(auto it = mSounds.begin(); it != mSounds.end(); it = next(it)) {
      if(it->second->getStatus() == sf::Sound::Status::Stopped) {
        helpers::safeDelete(it->second);
        mSounds.erase(it);
      }
    }
  }

  void AudioController::PlayOnce(sf::SoundBuffer* sound, float volume) {
    auto snd = new sf::Sound(*sound);
    snd->setVolume(volume);
    snd->play();
    mSounds[_counter] = snd;
    _counter++;
  }

  int AudioController::PlayRepeated(sf::SoundBuffer* sound, float volume) {
    auto snd = new sf::Sound(*sound);
    snd->setLoop(true);
    snd->setVolume(volume);
    snd->play();
    mSounds[_counter] = snd;
    return _counter++;
  }

  void AudioController::Stop(int id) {
    auto sound = mSounds[id];
    if(sound != nullptr) {
      sound->stop();
      helpers::safeDelete(sound);
    }
    mSounds.erase(id);
  }
} // namespace game
