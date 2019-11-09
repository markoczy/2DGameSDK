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

#include <map>

#include <SFML/Graphics.hpp>

#include <2DGameSDK/scene/entity/Entity.h>

#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/SceneGraphNode.h>

namespace game {

  /**
   * @brief Directed acyclic Graph that represents the Game Object hierarchy
   * 
   */
  class GAMESDK_DLL SceneGraph {
  public:
    static const int ROOT_NODE = 0;
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
    void OnTick();

    /**
     * @brief Renders the Scene Graph with all it's contents
     * 
     * @param target The screen or texture to render on
     * @param states The initial Render States (transformation etc.)
     */
    void OnRender(sf::RenderTarget* target, GameOptions* options, sf::RenderStates states = sf::RenderStates::Default);

    int AddEntity(Entity* entity, int parent = ROOT_NODE);

  private:
    static int idCounter;
    std::map<int, SceneGraphNode*> mNodes;

    void tickNodes(SceneGraphNode* current);
    void renderNodes(SceneGraphNode* current, sf::RenderTarget* target, GameOptions* options, sf::RenderStates states = sf::RenderStates::Default);
  };

} // namespace game

#endif