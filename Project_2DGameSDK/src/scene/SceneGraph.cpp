#include <2DGameSDK/scene/SceneGraph.h>

namespace game {
  const int SceneGraph::ROOT_NODE;
  int SceneGraph::idCounter = ROOT_NODE + 1;

  SceneGraph::SceneGraph(GameBase* game) : mGame(game) {
    mNodes[ROOT_NODE] = new SceneGraphNode(this, nullptr, nullptr);
  }

  SceneGraph::~SceneGraph() {
    for(auto entry : mNodes) {
      helpers::safeDelete(entry.second);
    }
  }

  void SceneGraph::OnTick() {
    tickNodes(mNodes[ROOT_NODE]);
    for(auto i = mNodes.begin(); i != mNodes.end(); i = std::next(i)) {
      if(i->second->mEntity != nullptr) {
        i->second->mEntity->OnTickEnded();
      }
    }
  }

  int SceneGraph::AddEntity(Entity* entity, int parent) {
    auto parentNode = mNodes[parent];
    auto node = new SceneGraphNode(this, mNodes[parent], entity);
    mNodes[idCounter] = node;
    parentNode->mChildren.push_back(node);
    return idCounter++;
  }

  void SceneGraph::tickNodes(SceneGraphNode* current) {
    auto entity = current->mEntity;
    if(entity != nullptr) {
      entity->OnTick();
    }
    for(auto iChild : current->mChildren) {
      tickNodes(iChild);
    }
  }

  void SceneGraph::renderNodes(SceneGraphNode* current, sf::RenderTarget* target, GameOptions* options, sf::RenderStates states) {
    auto entity = current->mEntity;

    if(entity != nullptr) {
      entity->OnRender(target, states);
    }

    for(auto iChild : current->mChildren) {
      renderNodes(iChild, target, options, states);
    }
  }
} // namespace game
