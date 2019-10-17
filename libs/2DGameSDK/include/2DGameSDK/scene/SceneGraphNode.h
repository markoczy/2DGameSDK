/**
 * @file SceneGraphNode.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Scene Graph Node class
 * @version 1.0
 * @date 2019-06-12
 *
 * @copyright Copyright (c) 2019
 *
 */
#ifndef __SCENE_GRAPH_NODE_H__
#define __SCENE_GRAPH_NODE_H__

#include <vector>

#include <SFML/System.hpp>

#include <2DGameSDK/common/GraphicTools.h>
#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/Entity.h>

namespace game {

  class SceneGraph;

  /**
   * @brief Single Node of the Scene Graph
   *
   */
  class GAMESDK_DLL SceneGraphNode {
  public:
    /**
     * @brief Creates a new Scene Graph Node
     *
     * @param graph The owning SceneGraph
     * @param parent The parent Node
     * @param entity The Game Entity on this Node
     */
    SceneGraphNode(SceneGraph* graph, SceneGraphNode* parent, Entity* entity);

    /**
     * @brief Destroys the Scene Graph Node object
     *
     */
    ~SceneGraphNode();

    void OnEntityTransformed(sf::Transform accumulated);

  private:
    friend class SceneGraph;

    SceneGraph* mGraph = nullptr;
    SceneGraphNode* mParent = nullptr;
    Entity* mEntity = nullptr;
    std::vector<SceneGraphNode*> mChildren;
  };

} // namespace game

#endif