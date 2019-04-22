#include <2DGameSDK/scene/SceneGraph.h>

namespace game {
  SceneGraph::SceneGraph() : mRoot(new SceneGraphNode(nullptr, nullptr)) {
  }

  SceneGraphNode* SceneGraph::GetRoot() {
    return mRoot;
  }

} // namespace game