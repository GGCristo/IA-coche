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
}

Celda::Celda(const Celda& celda2)
{
  i_ = celda2.i_;
  j_ = celda2.j_;
  retorno_ = celda2.retorno_;
  setEstado(celda2.Estado_);
  celda.setSize(sf::Vector2f(celda2.celda.getSize()));
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
}

const sf::Vector2f& Celda::getSize() const
{
  return celda.getSize();
}

void Celda::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(celda);
}
