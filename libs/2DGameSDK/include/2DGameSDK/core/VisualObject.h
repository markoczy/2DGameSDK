#ifndef __VISUAL_OBJECT_H__
#define __VISUAL_OBJECT_H__

#include <SFML/Graphics.hpp>

namespace game {
  class VisualObject {
  public:
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default) = 0;

    virtual int GetZIndex() = 0;

    static bool SortByZOrder(VisualObject* a, VisualObject* b) {
      return a->GetZIndex() < b->GetZIndex();
    }
  };
} // namespace game

#endif