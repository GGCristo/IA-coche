#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>
#include "../include/Malla.hpp"
#include "../include/Celda.hpp"
#include "../include/Coche.hpp"
#include "../include/Texturas.hpp"

int Malla::PorcentajeDeObstaculos = 10;

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

  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "IA-COCHE", sf::Style::Fullscreen);
  window.setFramerateLimit(15);

  while (window.isOpen() && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && malla.haySalidayEntrada()))
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

  // No me crees el coche si la ventana se ha cerrado
  if (window.isOpen())
  {
    const Celda& EstadoInicial = malla[malla.getEstadoInicial().first]
                                    [malla.getEstadoInicial().second];
    Coche coche(malla[0][0].getSize(), EstadoInicial.getPosition());
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      coche.Move(3);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      coche.Move(2);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      coche.Move(1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
      coche.Move(-1);
    } 
    window.clear();
    malla.draw(window);
    window.draw(coche);
    window.display();
  }
  }

  return 0;
}
