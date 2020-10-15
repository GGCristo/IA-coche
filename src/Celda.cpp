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
