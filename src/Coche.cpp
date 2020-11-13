#include "../include/Coche.hpp"
#include "iostream"

Coche::Coche(const sf::Vector2f& tamano, std::vector<Celda*>& recorrido) : recorrido_(std::move(recorrido))
{
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
  if (posicion_recorrido < recorrido_.size())
  {
    if (posicion_recorrido != 0 && posicion_recorrido != recorrido_.size() - 1)
    {
      recorrido_[posicion_recorrido]->setEstado(vr::TIERRA);
    }
    coche.setPosition(recorrido_[posicion_recorrido++]->getPosition()); }
}
