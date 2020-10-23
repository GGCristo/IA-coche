#include "../include/Celda.hpp"

#include <cassert>

#include "../include/Texturas.hpp"
#include "../include/variables.hpp"

Celda::Celda(const float& tamano)
{
  i_ = -1;
  j_ = -1;
  setEstado(vr::DEFAULT);
  celda.setSize(sf::Vector2f(tamano, tamano));

  auto acortamiento = 25;
  muros[0].setSize(sf::Vector2f(tamano, tamano / acortamiento));
  muros[1].setSize(sf::Vector2f(tamano, tamano / acortamiento));
  muros[2].setSize(sf::Vector2f(tamano / acortamiento, tamano));
  muros[3].setSize(sf::Vector2f(tamano / acortamiento, tamano));

  for (int i = 0; i < 4; i++)
    muros[i].setFillColor(sf::Color::Black);
}

Celda::Celda(const Celda& celda2)
{
  i_ = celda2.i_;
  j_ = celda2.j_;
  setEstado(celda2.Estado_);
  celda.setSize(sf::Vector2f(celda2.celda.getSize()));

  for (int i = 0; i < 4; i++)
  {
    muros[i].setSize(celda2.muros[i].getSize());
  }

  for (int i = 0; i < 4; i++)
    muros[i].setFillColor(celda2.muros[i].getFillColor());
}

Celda::~Celda()
{
}

bool Celda::getOcupacion() const
{
  return (Estado_ == vr::OBSTACULO);
}

void Celda::Ocupar()
{
  setEstado(vr::OBSTACULO);
}

const int& Celda::getEstado() const
{
  return Estado_;
}

// TODO Comprobar si esta ordenado de más comun a menos comun
void Celda::setEstado(const int& estado)
{
  Estado_ = estado;
  if (Estado_ == vr::DEFAULT)
  {
    celda.setTexture(&Texturas::getTexturas(0), true);
  }
  else if (Estado_ == vr::INICIAL)
  {
    celda.setTexture(&Texturas::getTexturas(2), true);
  }
  else if (Estado_ == vr::OBSTACULO)
  {
    celda.setTexture(&Texturas::getTexturas(1), true);
  }
  else if (Estado_ == vr::FINAL)
  {
    celda.setTexture(&Texturas::getTexturas(3), true);
  }
  else
  {
    std::cerr << "El estado " << estado << " no existe\n";
    exit(2);
  }
}

void Celda::setPosicion(const int& i, const int& j)
{
  i_ = i;
  j_ = j;

  celda.setPosition((celda.getSize().y) * (float)j_,
                    (celda.getSize().x) * (float)i_);
  for (int i = 0; i < 4; i++)
  {
    muros[i].setPosition(sf::Vector2f(celda.getPosition().x,
                                      celda.getPosition().y));
  }
}

const sf::Vector2f& Celda::getSize()
{
  return celda.getSize();
}

void Celda::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(celda);
  for (int i = 0; i < 4; i++)
    target.draw(muros[i]);
}
