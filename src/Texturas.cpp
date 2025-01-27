#include "../include/Texturas.hpp"
#include <cassert>

Texturas::Texturas()
{
  if(!texturas[0].loadFromFile("assets/Graphics/grass.png"))
  {
    throw "Fallo al cargar la textura de la hierba\n";
  }
  if (!texturas[1].loadFromFile("assets/Graphics/box.jpeg"))
  {
    throw "Fallo al cargar la textura de la caja\n";
  }
  if (!texturas[2].loadFromFile("assets/Graphics/Entrada.png"))
  {
    throw "Fallo al cargar la textura de la Entrada\n";
  }
  if (!texturas[3].loadFromFile("assets/Graphics/Salida.jpg"))
  {
    throw "Fallo al cargar la textura de la Salida";
  }
  if (!texturas[4].loadFromFile("assets/Graphics/car.png"))
  {
    throw "Fallo al cargar la textura de el Coche";
  }
  if (!texturas[5].loadFromFile("assets/Graphics/Wall.jpg"))
  {
    throw "Fallo al cargar la textura de los muros";
  }
  if (!texturas[6].loadFromFile("assets/Graphics/dirt.jpg"))
  {
    throw "Fallo al cargar la textura de la tierra";
  }
}

const sf::Texture& Texturas::getTexturas(const int& i)
{
  static Texturas instance;
  assert(i < (int)instance.texturas.size());
  return instance.texturas[i];
}
