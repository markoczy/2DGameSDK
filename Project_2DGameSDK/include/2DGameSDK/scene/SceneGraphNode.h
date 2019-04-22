#ifndef __SCENE_GRAPH_NODE_H__
#define __SCENE_GRAPH_NODE_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/TransformableEntity.h>
#include <SFML/System.hpp>
#include <vector>

namespace game {

  class GAMESDK_DLL SceneGraphNode {
  public:
    // TODO private and Friend of SceneGraph
    SceneGraphNode(SceneGraphNode* parent, TransformableEntity* entity);
    ~SceneGraphNode();
    SceneGraphNode* AddChild(TransformableEntity* entity);

    bool IsRoot();

    void Tick();
    sf::Transform GetCurTransform();
    sf::Transform GetAccumulatedTransform();

  private:
    SceneGraphNode* mParent = nullptr;
    TransformableEntity* mEntity = nullptr;
    std::vector<SceneGraphNode*> mChildren;
  };

} // namespace game

#endif