#include <2DGameSDK/scene/SceneGraph.h>

namespace game {
  static int idCounter = 1;

  SceneGraph::SceneGraph() : mRoot(new SceneGraphNode(nullptr, nullptr)) {
    mNodes[0] = mRoot;
  }

  SceneGraph::~SceneGraph() {
    for(auto entry : mNodes) {
      helpers::safeDelete(entry.second);
    }
  }

  void SceneGraph::Tick() {
    mRoot->Tick();
  }

  void SceneGraph::Render(sf::RenderTarget* target, GameOptions* options, sf::RenderStates states) {
    mRoot->Render(target, options, states);
  }

  SceneGraphNode* SceneGraph::GetRoot() {
    return mRoot;
  }

  int SceneGraph::AddEntity(TransformableEntity* entity, int parent) {
    auto parentNode = mNodes[parent];
    auto node = new SceneGraphNode(mNodes[parent], entity);
    mNodes[idCounter] = node;
    // parentNode->
    return idCounter++;
  }

} // namespace game