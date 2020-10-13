#include "../include/Mapa.hpp"
#include <vector>

Mapa::Mapa(const int& row, const int& column) : Mapa_(row)
{
  for (int i = 0; i < row; i++)
  {
    Mapa_[i].resize(column);
  }
}

MATRIX& Mapa::get_Mapa_()
{
  return Mapa_;
}
