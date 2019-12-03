#include <2DGameSDK/core/audio/AudioController.h>

namespace game {
  int _counter = 0;

  int AudioController::AddSound(sf::SoundBuffer* sound) {
    mSounds[_counter] = new sf::Sound(*sound);
    return _counter++;
  }

  void AudioController::PlayOnce(int id, float volume) {
    auto snd = mSounds[id];
    snd->setLoop(false);
    snd->setVolume(volume);
    snd->play();
    mSounds[_counter] = snd;
    _counter++;
  }

  int AudioController::PlayRepeated(int id, float volume) {
    auto snd = mSounds[id];
    snd->setLoop(true);
    snd->setVolume(volume);
    snd->play();
    mSounds[_counter] = snd;
    return _counter++;
  }

  void AudioController::Stop(int id) {
    auto sound = mSounds[id];
    sound->stop();
  }

  void AudioController::Delete(int id) {
    auto sound = mSounds[id];
    if(sound != nullptr) {
      sound->stop();
    }
    helpers::safeDelete(sound);
    mSounds.erase(id);
  }
} // namespace game
