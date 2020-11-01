#include "../include/Coche.hpp"
#include "iostream"

Coche::Coche(const sf::Vector2f& tamano, const sf::Vector2f& posicion)
{
  coche.setTexture(Texturas::getTexturas(tx::COCHE));
  coche.scale(tamano.x / coche.getLocalBounds().width, tamano.y / coche.getLocalBounds().height);
  coche.setPosition(posicion.x, posicion.y);
  desplazamiento_ = tamano;
}

void Coche::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(coche);
}

void Coche::Move(int coordenada) {
  if (coordenada == cr::SUR) {
    std::cout << "Se desplaza al Sur" << std::endl;
    coche.move(0.F,desplazamiento_.y);
  }
  else if (coordenada == cr::NORTE)
  {
    std::cout << "Se desplaza al Norte" << std::endl;
    coche.move(0.F,-desplazamiento_.y);
  }
  else if (coordenada == cr::ESTE)
  {
    std::cout << "Se desplaza al Este" << std::endl;
    coche.setPosition(coche.getPosition().x, coche.getPosition().y);
    coche.move(desplazamiento_.x,0.F);
  }
  else if (coordenada == cr::OESTE)
  {
    std::cout << "Se desplaza al oeste" << std::endl;
    coche.move(-desplazamiento_.x,0.F);
  }
}
