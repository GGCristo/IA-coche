#include "../include/Coche.hpp"
#include "iostream"

Coche::Coche(const sf::Vector2f& tamano, std::vector<Celda*> recorrido)
{
  recorrido_ = recorrido;
  coche.setTexture(Texturas::getTexturas(tx::COCHE));
  coche.scale(tamano.x / coche.getLocalBounds().width, tamano.y / coche.getLocalBounds().height);
  coche.setPosition(recorrido_[0]->getPosition().x, recorrido_[0]->getPosition().y);
  desplazamiento_ = tamano;
}

void Coche::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(coche);
}

void Coche::Move() {
  static int posicion_recorrido = 0;
  coche.setPosition(recorrido_[posicion_recorrido]->getPosition());
  if (posicion_recorrido < recorrido_.size() - 1)
  {
    posicion_recorrido++;
  }
}
