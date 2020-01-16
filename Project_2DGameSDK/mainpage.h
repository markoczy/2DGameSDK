/**
 * @file mainpage.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Mainpage of doxygen documentation
 * @version 1.0
 * @date 2020-01-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/**
 * @mainpage 2DGameSDK Documentation
 * 
 * @section intro Introduction
 * 
 * Welcome to the official documentation of the project 2D Game SDK.
 * The 2D Game SDK is a fully extensible multi-platform Game engine
 * for creating 2D games of any kind.
 * 
 * @section example Example
 * 
 * Example usage of the 2DGameSDK:
 * 
 * ```
 * 
 * // File: minimal_demo.cpp
 * #include <2DGameSDK/Core.h>
 * #include <2DGameSDK/Scene.h>
 * #include <2DGameSDK/World.h>
 * 
 * using namespace std;
 * using namespace game;
 * 
 * // Type of player entity
 * const int _PLAYER_TYPE = 200;
 * 
 * // Make an Entity that rotates on the Screen
 * class RotatingEntity : public SpriteKinematicEntity {
 * public:
 *   RotatingEntity(Game* game,
 *                  sf::Texture* texture,
 *                  float rotPerTick,
 *                  sf::Vector2f pos = sf::Vector2f()) : SpriteKinematicEntity(1, game, texture), mRot(rotPerTick) {
 * 
 *     SetTransform(sf::Transform().translate(pos));
 *   }
 * 
 *   void OnTick() {
 *     Transform(sf::Transform().rotate(mRot));
 *     auto pt = mTransform.transformPoint(sf::Vector2f());
 *     pt = mCombinedTransform.transformPoint(sf::Vector2f());
 *   }
 * 
 * private:
 *   float mRot;
 * };
 * 
 * int minimalDemo() {
 *   cout << "Start minimalDemo" << endl;
 * 
 *   // Create game
 *   auto options = GameOptions{"My Game", sf::Vector2i(512, 512), 5.0, 50};
 *   auto game = new Game(options);
 * 
 *   // Create Game World
 *   auto world = GameWorldFactory::CreateGameWorld(game, "res/maps/simple_grass/tilemap.json", "", "res/maps/simple_grass/tile_");
 *   game->SetWorld(world);
 *   cout << "GameWorld created." << endl;
 * 
 *   // Create Player entity and Rotating child entity
 *   auto tex = AssetManager::GetTexture("res/textures/discus.png");
 *   auto ent = new RotatingEntity(game, tex, 5.0, sf::Vector2f(50, 50));
 * 
 *   // Layout entities in scene
 *   auto scene = new SceneGraph(game);
 *   auto parent = scene->AddEntity(ent);
 *   scene->AddEntity(ent, parent);
 *   game->SetScene(scene);
 * 
 *   // Run Game
 *   game->Run();
 * 
 *   return 0;
 * }
 *
 * ```
 *
 * 
 * 
 */
