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

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/TransformableEntity.h>
#include <SFML/System.hpp>
#include <vector>

namespace game {

  /**
   * @brief Single Node of the Scene Graph
   * 
   */
  class GAMESDK_DLL SceneGraphNode {
  public:
    /**
     * @brief Creates a new Scene Graph Node
     * 
     * @param parent The parent Node
     * @param entity The Game Entity on this Node
     */
    SceneGraphNode(SceneGraphNode* parent, TransformableEntity* entity);

    /**
     * @brief Destroys the Scene Graph Node object
     * 
     */
    ~SceneGraphNode();

    /**
     * @brief Adds a new Child to this Node
     * 
     * @param entity 
     * @return SceneGraphNode* 
     */
    SceneGraphNode* AddChild(TransformableEntity* entity);

    /**
     * @brief Checks Wether the Node is a Root Node
     * 
     * @return Node is Root
     */
    bool IsRoot();

    /**
     * @brief Updates the Node and all it's children
     * 
     */
    void Tick();

    /**
     * @brief Renders the Node and all it's children
     * 
     * @param target The screen or texture to render on
     * @param states The initial Render States (transformation etc.)
     */
    void Render(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    /**
     * @brief Retreives the Transformation of this Node only
     * 
     * @return sf::Transform The current Transformation
     */
    sf::Transform GetCurTransform();

    /**
     * @brief Retreives the Transformation of all parent Nodes
     * 
     * @return sf::Transform The accumulated Transformation
     */
    sf::Transform GetAccumulatedTransform();

  private:
    SceneGraphNode* mParent = nullptr;
    TransformableEntity* mEntity = nullptr;
    std::vector<SceneGraphNode*> mChildren;
  };

} // namespace game

#endif