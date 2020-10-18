#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

struct Texturas
{
  private:
    sf::Texture texturas[2];
    Texturas();
  public:
    static const sf::Texture& getTexturas(const int&);
};
