#include "../include/Coche.hpp"

Coche::Coche(const sf::Vector2f& tamano, const sf::Vector2f& posicion)
{
  coche.setTexture(Texturas::getTexturas(tx::COCHE));
  std::cout << "X: " << coche.getGlobalBounds().height << '\n';
  std::cout << "Y: " << coche.getGlobalBounds().height << '\n';
  coche.scale(tamano.x / coche.getLocalBounds().width, tamano.y / coche.getLocalBounds().height);
  coche.setPosition(posicion.x, posicion.y);
}

void Coche::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(coche);
}
