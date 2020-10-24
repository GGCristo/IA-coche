#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Texturas.hpp"
#include "Mapa.hpp"
class Coche : public sf::Drawable
{
  private:
    sf::Sprite coche;
  public:
    Coche(const sf::Vector2f&, const sf::Vector2f&);
  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
