#include <2DGameSDK/GameObject.h>
#include <2DGameSDK/ResourceCache.h>
#include <iostream>

#include <SFML/Graphics.hpp>

int main() {
  std::cout << "Hello Compiler" << std::endl;

  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Blue);

  auto cache = TextureCache();

  // auto assets = AssetManager();
  auto tex = cache.Get("res/textures/testtile/testtile_0.png");
  shape.setTexture(tex);

  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    window.draw(shape);
    window.display();
  }

  // auto k = cache.Get("res/textures/testtile/testtile_0.png");
  cache.Clear();
  std::cout << "End." << std::endl;
  system("pause");

  return 0;
}