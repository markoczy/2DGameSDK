#include <2DGameSDK/scene/SceneGraph.h>

namespace game {
  // static int idCounter = SceneGraph::ROOT_NODE + 1;
  const int SceneGraph::ROOT_NODE;
  int SceneGraph::idCounter = ROOT_NODE + 1;

  SceneGraph::SceneGraph() {
    mNodes[ROOT_NODE] = new Node{nullptr, nullptr};
  }

  SceneGraph::~SceneGraph() {
    for(auto entry : mNodes) {
      helpers::safeDelete(entry.second);
    }
  }

  void SceneGraph::Tick() {
    tickNodes(mNodes[ROOT_NODE]);
  }

  void SceneGraph::Render(sf::RenderTarget* target, GameOptions* options, sf::RenderStates states) {
    renderNodes(mNodes[ROOT_NODE], target, options, states);
  }

  // SceneGraphNode* SceneGraph::GetRoot() {
  //   return mRoot;
  // }

  int SceneGraph::AddEntity(TransformableEntity* entity, int parent) {
    auto parentNode = mNodes[parent];
    auto node = new Node{entity, mNodes[parent]};
    mNodes[idCounter] = node;
    parentNode->Children.push_back(node);
    return idCounter++;
  }

  void SceneGraph::tickNodes(Node* current) {
    auto entity = current->Entity;
    if(entity != nullptr) {
      entity->Tick();
    }
    for(auto iChild : current->Children) {
      tickNodes(iChild);
    }
  }

  void SceneGraph::renderNodes(Node* current, sf::RenderTarget* target, GameOptions* options, sf::RenderStates states) {
    auto entity = current->Entity;
    if(entity != nullptr) {
      entity->Render(target, states);
      states = sf::RenderStates(states.transform * entity->GetTransformable()->getTransform());

      if(options->RenderAABB) {
        auto aabb = entity->GetAABB();

        //* Render as Vertex Array
        // auto vertexArray = helpers::GrahicTools::CreateUniformVertexArray(helpers::GrahicTools::GetRectBoundary(aabb), sf::LineStrip, sf::Color::Magenta);
        // target->draw(vertexArray);

        //* Render as Shape
        auto rect = sf::RectangleShape(sf::Vector2f(aabb.width, aabb.height));
        rect.setPosition(aabb.left, aabb.top);
        rect.setOutlineColor(sf::Color::Magenta);
        rect.setOutlineThickness(0.5);
        rect.setFillColor(sf::Color::Transparent);
        target->draw(rect);
      }

      if(options->RenderCollisionMask) {
        auto collisionMask = entity->GetCollisionMask();

        if(collisionMask.size() > 0) {
          //* Render as Vertex Array
          // auto vertexArray = helpers::GrahicTools::CreateUniformVertexArray(collisionMask, sf::LineStrip, sf::Color::Red);
          // target->draw(vertexArray);

          //* Render as Shape
          auto shape = sf::ConvexShape(collisionMask.size());
          for(int i = 0; i < collisionMask.size(); i++) {
            shape.setPoint(i, collisionMask[i]);
          }
          shape.setOutlineColor(sf::Color::Red);
          shape.setOutlineThickness(0.5);
          shape.setFillColor(sf::Color::Transparent);
          target->draw(shape);
        }
      }
    }
    for(auto iChild : current->Children) {
      renderNodes(iChild, target, options, states);
    }
  }

} // namespace game