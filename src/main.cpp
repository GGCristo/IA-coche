#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "../include/Mapa.hpp"
#include "../include/Celda.hpp"
#include "../include/Grafo.hpp"
#include "../include/Texturas.hpp"
// TODO Usar variables globales para definir los estados
// (e.j const int OBSTACULO = -2)
int Mapa::PorcentajeDeObstaculos = 10;

int main()
{
  std::cout << "Introduzca el numero de filas" << '\n';
  int row;
  std::cin >> row;
  std::cout << "Introduzca el numero de columnas" << '\n';
  int column;
  std::cin >> column;

  // Inicializo las texturas para que en caso de que no
  // cargen el programa cierre de forma segura
  try
  {
    Texturas::getTexturas();
  }
  catch(const char* msg)
  {
    std::cerr << msg;
    return 1;
  }

  Mapa mapa(row, column);

  sf::RenderWindow window(sf::VideoMode(1080, 1024), "IA-COCHE");
  window.setFramerateLimit(30);

  std::cout << "Tamaño ventanaX: " << window.getSize().x << '\n';
  std::cout << "Tamaño ventanaY: " << window.getSize().y << '\n';

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
