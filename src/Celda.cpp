#include "../include/Celda.hpp"

Celda::Celda()
{
  Estado_ = -1;
}

bool Celda::getOcupacion() const
{
  return (Estado_ == -2);
}

void Celda::Ocupar()
{
  Estado_ = -2;
}

const int& Celda::getEstado() const
{
  return Estado_;
}

void Celda::setEstado(const int& estado)
{
  Estado_ = estado;
}
