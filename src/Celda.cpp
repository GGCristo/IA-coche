#include "../include/Celda.hpp"
#include "../include/Texturas.hpp"
#include "../include/variables.hpp"
#include <cassert>

Celda::Celda(const float& tamano)
{
  i_ = -1;
  j_ = -1;
  setEstado(vr::DEFAULT);
  celda.setSize(sf::Vector2f(tamano, tamano));
  celda.setOrigin(celda.getSize().x / 2, celda.getSize().y / 2);

  auto acortamiento = 20;
  muros[0].setSize(sf::Vector2f(tamano, tamano / acortamiento));
  muros[0].setOrigin(muros[0].getSize().x / 2, muros[0].getSize().y / 2);

  muros[1].setSize(sf::Vector2f(tamano, tamano / acortamiento));
  muros[1].setOrigin(muros[1].getSize().x / 2, muros[1].getSize().y / 2);


  muros[2].setSize(sf::Vector2f(tamano / acortamiento, tamano));
  muros[2].setOrigin(muros[2].getSize().x / 2, muros[2].getSize().y / 2);

  muros[3].setSize(sf::Vector2f(tamano / acortamiento, tamano));
  muros[3].setOrigin(muros[3].getSize().x / 2, muros[3].getSize().y / 2);

  for (int i = 0; i < 4; i++)
    muros[i].setFillColor(sf::Color::Black);
}

Celda::Celda(const Celda& celda2)
{
  i_ = celda2.i_;
  j_ = celda2.j_;
  setEstado(celda2.Estado_);
  celda.setSize(sf::Vector2f(celda2.celda.getSize()));
  celda.setOrigin(celda2.celda.getOrigin());

  muros[0].setSize(celda2.muros[0].getSize());
  muros[0].setOrigin(celda2.muros[0].getOrigin());

  muros[1].setSize(celda2.muros[1].getSize());
  muros[1].setOrigin(celda2.muros[1].getOrigin());

  muros[2].setSize(celda2.muros[2].getSize());
  muros[2].setOrigin(celda2.muros[2].getOrigin());

  muros[3].setSize(celda2.muros[3].getSize());
  muros[3].setOrigin(celda2.muros[3].getOrigin());

  for (int i = 0; i < 4; i++)
    muros[i].setFillColor(celda2.muros[i].getFillColor());
}

Celda::~Celda()
{}

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

  celda.setPosition((celda.getSize().y) * (float)j_ + celda.getSize().y / 2 + muros[0].getSize().y,
                    (celda.getSize().x) * (float)i_ + celda.getSize().x / 2 + muros[2].getSize().x);

  muros[0].setPosition(sf::Vector2f(celda.getPosition().x,
                        celda.getPosition().y - (celda.getSize().y / 2)));
  muros[1].setPosition(sf::Vector2f(celda.getPosition().x,
                        celda.getPosition().y + (celda.getSize().y / 2)));
  muros[2].setPosition(sf::Vector2f(celda.getPosition().x - (celda.getSize().x / 2),
                        celda.getPosition().y));
  muros[3].setPosition(sf::Vector2f(celda.getPosition().x + (celda.getSize().x / 2),
                        celda.getPosition().y));
}

void Celda::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(celda);
  for (int i = 0; i < 4; i++)
     target.draw(muros[i]);
}
