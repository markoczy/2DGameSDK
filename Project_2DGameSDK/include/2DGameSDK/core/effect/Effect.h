#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameObject.h>
#include <2DGameSDK/core/VisualObject.h>
#include <2DGameSDK/core/state/StateManager.h>
#include <2DGameSDK/core/visual/SimpleSequenceRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  class GAMESDK_DLL Effect : public GameObject, public VisualObject {
  public:
    Effect(GameBase* game, std::vector<sf::Texture*> sequence, sf::Transform transform = sf::Transform::Identity, int framesPerSprite = 1);

    virtual ~Effect();

    virtual int GetZIndex();
    virtual void SetZIndex(int zIndex);

    virtual void SetTransform(sf::Transform transform);
    virtual void SetSize(sf::Vector2f size);
    virtual void SetSize(int idx, sf::Vector2f size);

    virtual void OnTick();
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

  protected:
    SimpleSequenceRenderStrategy* mRenderer = nullptr;
    sf::Transform mTransform;
    int mZIndex = constants::DEFAULT_ZINDEX_EFFECT;

    void onDestroy();
  };
} // namespace game

#endif