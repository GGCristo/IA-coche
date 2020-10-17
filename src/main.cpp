#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "../include/Mapa.hpp"
#include "../include/Celda.hpp"
#include "../include/Grafo.hpp"

int Mapa::PorcentajeDeObstaculos = 10;

int main()
{
  std::cout << "Introduzca el numero de filas" << '\n';
  int row;
  std::cin >> row;
  std::cout << "Introduzca el numero de columnas" << '\n';
  int column;
  std::cin >> column;

  Mapa mapa(row, column);

  sf::RenderWindow window(sf::VideoMode(1080, 1024), "IA-COCHE");
  window.setFramerateLimit(30);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    mapa.draw(window);
    window.display();
  }
  return 0;
}
