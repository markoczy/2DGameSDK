/**
 * @file SceneGraph.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Scene Graph class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SCENE_GRAPH_H__
#define __SCENE_GRAPH_H__

#include <map>
#include <queue>

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/SceneGraphNode.h>
#include <2DGameSDK/scene/entity/Entity.h>

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
    SceneGraph(GameBase* game);

    /**
     * @brief Destroys the Scene Graph object
     */
    ~SceneGraph();

    /**
     * @brief Retreives all Entities
     * 
     * @return std::vector<Entity*> 
     */
    std::vector<Entity*> GetAllEntities();

    /**
     * @brief Updates all entities of the Scene Graph 
     * 
     */
    void OnTick();

    /**
     * @brief Adds a new entity
     * 
     * @param entity the entity
     * @param parent the parent id (default is root)
     * @return int the entity id
     */
    int AddEntity(Entity* entity, int parent = ROOT_NODE);

  private:
    static int idCounter;
    GameBase* mGame;
    std::map<int, SceneGraphNode*> mNodes;

    /**
     * @brief Updates all nodes recursively
     * 
     * @param current the current node
     * 
     * @deprecated managed by state manager
     */
    void tickNodes(SceneGraphNode* current);

    /**
     * @brief Renders all nodes recursively
     * 
     * @param current the current node
     * @param target the render target
     * @param options the game options
     * @param states the render states
     * 
     * @deprecated managed by state manager
     */
    void renderNodes(SceneGraphNode* current, sf::RenderTarget* target, GameOptions* options, sf::RenderStates states = sf::RenderStates::Default);
  };

} // namespace game

#endif