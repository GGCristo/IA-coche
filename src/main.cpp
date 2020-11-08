#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>
#include "../include/Malla.hpp"
#include "../include/Celda.hpp"
#include "../include/Coche.hpp"
#include "../include/Texturas.hpp"

int Malla::PorcentajeDeObstaculos = 10;

/**
 * @brief Bucle para que el usuario cree las condiciones iniciales del "tablero"
 *
 * @param window ventana para hacer el proceso interactivo
 * @param malla Guarda los cambios en la malla, para poder trabajar con los datos
 */
void modificarTerreno(sf::RenderWindow& window, Malla& malla);

/**
 * @brief Muestra el resultado del algoritmo
 *
 * @param window Muestralo a travez de esta ventana
 * @param malla Malla donde se va a mover el coche que vamos a crear dentro
 */
void main_loop(sf::RenderWindow& window, Malla& malla)
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


int main()
{

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

  Malla::get_instance();

  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "IA-COCHE", sf::Style::Fullscreen);
  window.setFramerateLimit(15);

  modificarTerreno(window, Malla::get_instance());

  // Pongo el sleep porque el programa me detecta el enter de forma prematura
  sf::sleep(sf::seconds(0.5));

  // Si el usuario cerro la ventana, cierra la aplicación
  if (window.isOpen())
  {
    main_loop(window, Malla::get_instance());
  }

  return 0;
}

void modificarTerreno(sf::RenderWindow& window, Malla& malla)
{
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
}
