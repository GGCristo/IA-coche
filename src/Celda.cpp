#include "../include/Celda.hpp"

Celda::Celda()
{
  Ocupada_ = false;
  Estado_ = -1;
}

const bool& Celda::getOcupacion() const
{
  return Ocupada_;
}

void Celda::Ocupar()
{
  Ocupada_ = true;
}
