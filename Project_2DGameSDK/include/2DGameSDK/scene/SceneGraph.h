#ifndef __SCENE_GRAPH_H__
#define __SCENE_GRAPH_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/SceneGraphNode.h>

namespace game {

  class GAMESDK_DLL SceneGraph {
  public:
    SceneGraph();
    ~SceneGraph();

    void Tick();
    SceneGraphNode* GetRoot();

  private:
    SceneGraphNode* mRoot;
  };

} // namespace game

#endif