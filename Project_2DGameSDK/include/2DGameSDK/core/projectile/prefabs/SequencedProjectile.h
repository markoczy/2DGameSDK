/**
 * @file SequencedProjectile.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief SequencedProjectile
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SEQUENCED_PROJECTILE_H__
#define __SEQUENCED_PROJECTILE_H__

#include <2DGameSDK/core/projectile/Projectile.h>
#include <2DGameSDK/core/visual/SimpleSequenceRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  /**
   * @brief Defines a projectile that is rendered by a sequence of textures
   * 
   */
  class GAMESDK_DLL SequencedProjectile : public Projectile {
  public:
    /**
     * @brief Constructs a new Sequenced Projectile
     * 
     * @param game the game
     * @param type the user defined projectile type
     * @param sequence the texture sequence
     * @param shapes the physical shapes
     * @param start the spawn point in world coordinates
     * @param velocity the velocity vector
     * @param maxLifetime the maximum lifetime (-1 for infinite)
     * @param seqFrames the frames per rendered texture
     * @param seqStart the sequence start index
     */
    SequencedProjectile(GameBase* game, int type, std::vector<sf::Texture*> sequence, Shape<KinematicShapePhysics>* shapes, sf::Transform start, sf::Vector2f velocity, int maxLifetime = 100, int seqFrames = 1, int seqStart = 0);
  };

} // namespace game

#endif