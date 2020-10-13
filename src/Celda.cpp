#include "../include/Celda.hpp"

Celda::Celda()
{
  Ocupada_ = false;
}

const bool& Celda::getOcupacion()
{
  return Ocupada_;
}

void Celda::Ocupar()
{
  Ocupada_ = true;
}
