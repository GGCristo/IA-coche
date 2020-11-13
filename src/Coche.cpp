#include "../include/Coche.hpp"
#include "iostream"

Coche::Coche(const sf::Vector2f& tamano, std::vector<Celda*>& recorrido) : recorrido_(std::move(recorrido))
{
  offset_.x = tamano.x / 2;
  offset_.y = tamano.y / 2;
  coche.setTexture(Texturas::getTexturas(tx::COCHE));
  coche.scale(tamano.x / coche.getLocalBounds().width, tamano.y / coche.getLocalBounds().height);
  coche.setOrigin(coche.getTexture()->getSize().x / 2, coche.getTexture()->getSize().y / 2);
  coche.setPosition(recorrido_[0]->getPosition().x + offset_.x, recorrido_[0]->getPosition().y + offset_.y);
}

void Coche::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(coche);
}

void Coche::Move()
{
  static int posicion_recorrido = 1;
  if (posicion_recorrido < recorrido_.size())
  {
    if (posicion_recorrido != recorrido_.size() - 1)
    {
      recorrido_[posicion_recorrido]->setEstado(vr::TIERRA);
      Celda* siguiente = recorrido_[posicion_recorrido + 1];
      if (siguiente->get_i() < recorrido_[posicion_recorrido]->get_i()) // Norte
      {
        coche.setRotation(90);
      }
      else if (siguiente->get_i() > recorrido_[posicion_recorrido]->get_i()) // Sur
      {
        coche.setRotation(-90);
      }
      else if (siguiente->get_j() < recorrido_[posicion_recorrido]->get_j()) // Oeste
      {
        coche.setRotation(180);
      }
      else if (siguiente->get_j() > recorrido_[posicion_recorrido]->get_j()) // Este
      {
        coche.setRotation(0);
      }
    }

    coche.setPosition(recorrido_[posicion_recorrido]->getPosition().x + offset_.x,
                      recorrido_[posicion_recorrido]->getPosition().y + offset_.y);
    posicion_recorrido++;
  }
}
