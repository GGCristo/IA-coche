#include "../include/Celda.hpp"

#include <cassert>

#include "../include/Texturas.hpp"
#include "../include/variables.hpp"

Celda::Celda(float tamano)
{
  i_ = -1;
  j_ = -1;
  retorno_ = nullptr;
  setEstado(vr::DEFAULT);
  celda.setSize(sf::Vector2f(tamano, tamano));

  auto acortamiento = 25;
  muros[0].setSize(sf::Vector2f(tamano, tamano / acortamiento));
  muros[1].setSize(sf::Vector2f(tamano, tamano / acortamiento));
  muros[2].setSize(sf::Vector2f(tamano / acortamiento, tamano));
  muros[3].setSize(sf::Vector2f(tamano / acortamiento, tamano));

  for (int i = 0; i < 4; i++)
  {
    muros[i].setFillColor(sf::Color::Black);
  }
}

Celda::Celda(const Celda& celda2)
{
  i_ = celda2.i_;
  j_ = celda2.j_;
  retorno_ = celda2.retorno_;
  setEstado(celda2.Estado_);
  celda.setSize(sf::Vector2f(celda2.celda.getSize()));

  for (int i = 0; i < 4; i++)
  {
    muros[i].setSize(celda2.muros[i].getSize());
  }

  for (int i = 0; i < 4; i++)
  {
    muros[i].setFillColor(celda2.muros[i].getFillColor());
  }
}

Celda::~Celda()
{
}

bool Celda::getOcupacion() const
{
  return (Estado_ == vr::OBSTACULO || Estado_ == vr::MURO);
}

void Celda::Ocupar()
{
  if (Estado_ == vr::OBSTACULO)
  {
    std::cout << "Intentando ocupar un muro\n";
    assert(true);
  }
  setEstado(vr::OBSTACULO);
}

const int Celda::get_i() const
{
  return i_;
}

const int Celda::get_j() const
{
  return j_;
}

void Celda::setRetorno(Celda* celda)
{
  retorno_ = celda;
}

// const Celda* Celda::getRetorno()
// {
//   return retorno_;
// }

Celda* Celda::getRetorno() const
{
  return retorno_;
}

const int& Celda::getEstado() const
{
  return Estado_;
}

void Celda::setEstado(int estado)
{
  Estado_ = estado;
  if (Estado_ == vr::DEFAULT)
  {
    celda.setTexture(&Texturas::getTexturas(tx::GRASS), true);
  }
  else if (Estado_ == vr::OBSTACULO)
  {
    celda.setTexture(&Texturas::getTexturas(tx::BOX), true);
  }
  else if (Estado_ == vr::MURO)
  {
    celda.setTexture(&Texturas::getTexturas(tx::WALL), true);
  }
  else if (Estado_ == vr::INICIAL)
  {
    celda.setTexture(&Texturas::getTexturas(tx::ENTRADA), true);
  }
  else if (Estado_ == vr::FINAL)
  {
    celda.setTexture(&Texturas::getTexturas(tx::SALIDA), true);
  }
  else if (Estado_ == vr::TIERRA)
  {
    celda.setTexture(&Texturas::getTexturas(tx::DIRT), true);
  }
  else
  {
    std::cerr << "El estado " << estado << " no existe\n";
    exit(2);
  }
}

const sf::Vector2f& Celda::getPosition() const
{
  return celda.getPosition();
}

void Celda::setPosicion(int i, int j)
{
  i_ = i;
  j_ = j;

  celda.setPosition((celda.getSize().y) * (float)j_,
                    (celda.getSize().x) * (float)i_);
  for (int z = 0; z < 4; z++)
  {
    muros[z].setPosition(sf::Vector2f(celda.getPosition().x,
                                      celda.getPosition().y));
  }
}

const sf::Vector2f& Celda::getSize() const
{
  return celda.getSize();
}

void Celda::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(celda);
  for (int i = 0; i < 4; i++)
  {
    target.draw(muros[i]);
  }
}
