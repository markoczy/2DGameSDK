/**
 * @file AnimatedTransformableEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Animated Transformable Entity class 
 * @version 1.0
 * @date 2019-06-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __ANIMATED_TRANSFORMABLE_ENTITY_H__
#define __ANIMATED_TRANSFORMABLE_ENTITY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/TransformableEntity.h>
#include <sstream>

namespace game {

  /**
   * @brief Entity that is transformable and that defines a set of animation
   *        states, where every state is represented by it's own texture. The
   *        current animation state can be changed at measure to render a
   *        different texture for the entity.
   * 
   */
  class GAMESDK_DLL AnimatedTransformableEntity : public TransformableEntity {
  public:
    /**
     * @brief Creates a new Animated Transformable Entity
     * 
     * @param type type The Entity Type (does not affect anything and is meant
     *        to be used freely to identify entities of some kind)
     * 
     * @param animationStates The set of Animation States
     */
    AnimatedTransformableEntity(int type, std::map<int, sf::Texture*> animationStates);

    /**
     * @brief Destroys the Animated Transformable Entity
     * 
     */
    ~AnimatedTransformableEntity();

    /**
     * @brief Updates the Entity
     * 
     */
    virtual void Tick();

    /**
     * @brief Renders the Entity
     * 
     * @param target The screen or texture to render on
     * @param states The initial Render States (transformation etc.)
     */
    virtual void Render(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    /**
     * @brief Retreives the reference to the SFML Transformable wich can
     *        be used to apply transformations to the Transformable Entity.
     * 
     * @return sf::Transformable* The Reference of the Transormable Object
     */
    virtual sf::Transformable* GetTransformable();

    /**
     * @brief Sets the current Animation State
     * 
     * @param state The Animation State (must match to any key of the 
     *        Animation states Map defined in the Constructor)
     */
    void SetAnimState(int state);

    virtual sf::FloatRect GetAABB();

  protected:
    std::map<int, sf::Texture*> mAnimStates;
    sf::Sprite mCurState;
    sf::Transformable mTransform;
  };

} // namespace game

#endif