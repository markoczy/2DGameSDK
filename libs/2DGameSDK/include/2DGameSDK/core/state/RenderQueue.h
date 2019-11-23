#ifndef __RENDER_QUEUE_H__
#define __RENDER_QUEUE_H__

#include <queue>

#include <SFML/Graphics.hpp>

#include <2DGameSDK/core/GameObject.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  class RenderQueue {
  public:
    RenderQueue();
    void Push(GameObject* object);

    void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

  private:
    static bool compareObjects(GameObject* a, GameObject* b);
    std::priority_queue<GameObject*, std::vector<GameObject*>, decltype(RenderQueue::compareObjects)> mQueue;
  };
} // namespace game

#endif