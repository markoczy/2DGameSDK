/**
 * @file SceneGraph.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Scene Graph class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __SCENE_GRAPH_H__
#define __SCENE_GRAPH_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/SceneGraphNode.h>
#include <SFML/Graphics.hpp>

namespace game {

  /**
   * @brief 
   * 
   */
  class GAMESDK_DLL SceneGraph {
  public:
    /**
     * @brief Constructs a new Scene Graph object
     * 
     */
    SceneGraph();

    /**
     * @brief Destroys the Scene Graph object
     */
    ~SceneGraph();

    /**
     * @brief Updates all entities of the Scene Graph 
     * 
     */
    void Tick();

    /**
     * @brief Renders the Scene Graph with all it's contents
     * 
     * @param target The screen or texture to render on
     * @param states The initial Render States (transformation etc.)
     */
    void Render(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    /**
     * @brief Retreives the Root Node
     * 
     * @return SceneGraphNode* The Root Node
     */
    SceneGraphNode* GetRoot();

  private:
    SceneGraphNode* mRoot;
  };

} // namespace game

#endif