#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <array>

struct Texturas
{
  private:
    std::array<sf::Texture, 5> texturas;
    Texturas();
  public:
    static const sf::Texture& getTexturas(const int& = 0);
};
