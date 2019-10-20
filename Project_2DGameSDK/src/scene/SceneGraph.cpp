#include <2DGameSDK/scene/SceneGraph.h>

namespace game {
  const int SceneGraph::ROOT_NODE;
  int SceneGraph::idCounter = ROOT_NODE + 1;

  SceneGraph::SceneGraph() {
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

    for(auto i = mNodes.begin(); i != mNodes.end(); i = std::next(i)) {
      for(auto j = std::next(i); j != mNodes.end(); j = std::next(j)) {
        auto entA = i->second->mEntity;
        auto entB = j->second->mEntity;
        if(entA != nullptr && entA->IsCollidable() && entB != nullptr && entB->IsCollidable()) {
          if(entA->GetAABB().intersects(entB->GetAABB())) {
            LOGD("BB Intersect");
            // auto intersect = helpers::GrahicTools::ShapesIntersect(entA->GetCollisionMask(), entB->GetCollisionMask());
            // if(std::get<0>(intersect)) {
            //   // TODO performance!!
            //   auto pt = std::get<1>(intersect);
            //   auto invA = entA->GetTransform().getInverse();
            //   auto invB = entB->GetTransform().getInverse();

            //   entA->OnCollision(entB, invA.transformPoint(pt));
            //   entB->OnCollision(entA, invB.transformPoint(pt));
            // }
          }
        }
      }
    }
  }

  void SceneGraph::OnRender(sf::RenderTarget* target, GameOptions* options, sf::RenderStates states) {
    renderNodes(mNodes[ROOT_NODE], target, options, states);
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
          for(unsigned int i = 0; i < collisionMask.size(); i++) {
            shape.setPoint(i, collisionMask[i]);
          }
          shape.setOutlineColor(sf::Color::Red);
          shape.setOutlineThickness(0.5);
          shape.setFillColor(sf::Color::Transparent);
          target->draw(shape);
        }
      }
    }
    for(auto iChild : current->mChildren) {
      renderNodes(iChild, target, options, states);
    }
  }

} // namespace game