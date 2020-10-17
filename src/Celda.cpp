#include "../include/Celda.hpp"
#include <cassert>

Celda::Celda(const float& tamano)
{
  i_ = -1;
  j_ = -1;
  Estado_ = -1;
  celda.setSize(sf::Vector2f(tamano, tamano));
  celda.setOrigin(celda.getSize().x / 2, celda.getSize().y / 2);
  celda.setFillColor(sf::Color::Black);

  muros[0].setSize(sf::Vector2f(tamano, tamano / 8));
  muros[0].setOrigin(muros[0].getSize().x / 2, muros[0].getSize().y / 2);

  muros[1].setSize(sf::Vector2f(tamano, tamano / 8));
  muros[1].setOrigin(muros[1].getSize().x / 2, muros[1].getSize().y / 2);


  muros[2].setSize(sf::Vector2f(tamano / 8, tamano));
  muros[2].setOrigin(muros[2].getSize().x / 2, muros[2].getSize().y / 2);

  muros[3].setSize(sf::Vector2f(tamano / 8, tamano));
  muros[3].setOrigin(muros[3].getSize().x / 2, muros[3].getSize().y / 2);

  for (int i = 0; i < 4; i++)
    muros[i].setFillColor(sf::Color::Cyan);
}

Celda::~Celda()
{}

bool Celda::getOcupacion() const
{
  return (Estado_ == -2);
}

void Celda::Ocupar()
{
  Estado_ = -2;
  celda.setFillColor(sf::Color::Green);
}

const int& Celda::getEstado() const
{
  return Estado_;
}

void Celda::setEstado(const int& estado)
{
  Estado_ = estado;
}

void Celda::setPosicion()
{
  assert(i_ != -1 && j_ != -1);

  celda.setPosition((celda.getSize().y) * (float)j_ + celda.getSize().y / 2,
                    (celda.getSize().x) * (float)i_ + celda.getSize().x / 2);

  std::cout << i_ << ' ' << j_ << ": " << celda.getPosition().x << ' ' << celda.getPosition().y << '\n';

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
