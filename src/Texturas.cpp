#include "../include/Texturas.hpp"
#include <cassert>

Texturas::Texturas()
{
  if(!texturas[0].loadFromFile("assets/Graphics/grass.png"))
  {
    std::cerr << "Fallo al cargar la textura de la hierba\n";
    exit(-1);
  }
  if (!texturas[1].loadFromFile("assets/Graphics/box.jpeg"))
  {
    std::cerr << "Fallo al cargar la textura de la caja\n";
    exit(-1);
  }
}

const sf::Texture& Texturas::getTexturas(const int& i)
{
  assert(i < 2);
  static Texturas instance;
  return instance.texturas[i];
}
