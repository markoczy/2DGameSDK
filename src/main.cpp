#include "exampleclass/exampleclass.h"
#include <iostream>

#include <SFML/Graphics.hpp>

int main() {
  std::cout << "Hello Compiler" << std::endl;

  auto c = ExampleClass();

  for(int i = 0; i < 10; i++) {
    std::cout << c.doStuff() << std::endl;
  }

  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();

    int* a = 0x0;
  }

  std::cout << "End." << std::endl;

  return 0;
}