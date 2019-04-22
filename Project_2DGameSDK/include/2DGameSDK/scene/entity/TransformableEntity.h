#ifndef __TRANSFORMABLE_ENTITY_H__
#define __TRANSFORMABLE_ENTITY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
// #include <2DGameSDK/scene/SceneGraphNode.h>
#include <2DGameSDK/scene/entity/Entity.h>
#include <SFML/Graphics.hpp>

namespace game {
  class SceneGraphNode;

  class GAMESDK_DLL TransformableEntity : public Entity {
  public:
    TransformableEntity(int type);
    ~TransformableEntity();
    void SetGraphNode(SceneGraphNode* graphNode);

    virtual sf::Transformable* GetTransformable() = 0;

  protected:
    SceneGraphNode* mGraphNode = nullptr;
  };

} // namespace game

#endif