#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Sleep.hpp>
#include "Texturas.hpp"
#include "variables.hpp"
#include "Malla.hpp"

class Coche : public sf::Drawable
{
  private:
    sf::Sprite coche;
    sf::Vector2f offset_;
    std::vector<Celda*> recorrido_;
  public:
    Coche(const sf::Vector2f&, std::vector<Celda*>&);
    void Move();

  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
