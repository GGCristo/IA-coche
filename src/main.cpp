#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>
#include "../include/Mapa.hpp"
#include "../include/Celda.hpp"
#include "../include/Coche.hpp"
#include "../include/Texturas.hpp"

int Malla::PorcentajeDeObstaculos = 10;
const bool fullscreen = false;

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

  Malla malla(row, column);

  // Pongo el sleep porque el programa me detecta el enter de forma prematura
  sf::sleep(sf::seconds(0.5));

  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "IA-COCHE");
  window.setFramerateLimit(15);
  if (fullscreen)
  {
    window.create(sf::VideoMode::getDesktopMode(), "IA-COCHE", sf::Style::Fullscreen);
  }

  std::cout << "Tamaño ventanaX: " << window.getSize().x << '\n';
  std::cout << "Tamaño ventanaY: " << window.getSize().y << '\n';

  while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed)
      {
        malla.Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
      malla.Control_Entrada(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
      malla.Control_Salida(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    }
    window.clear();
    malla.draw(window);
    window.display();
  }
  std::cout << "El algoritmo empieza\n";
  Coche coche(malla.getMalla()[0][0].getSize(), malla.getMalla()[malla.getEstadoInicial().first][malla.getEstadoInicial().second].getPosition());
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
    }
    window.clear();
    malla.draw(window);
    window.draw(coche);
    window.display();
  }
  return 0;
}
