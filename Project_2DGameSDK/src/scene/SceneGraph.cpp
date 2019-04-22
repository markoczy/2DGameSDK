#include <2DGameSDK/scene/SceneGraph.h>

namespace game {
  SceneGraph::SceneGraph() {
    mRoot = new SceneGraphNode(nullptr, nullptr);
  }

  SceneGraph::~SceneGraph() {}

  void SceneGraph::Tick() {
    mRoot->Tick();
  }

  SceneGraphNode* SceneGraph::GetRoot() {
    return mRoot;
  }

} // namespace game