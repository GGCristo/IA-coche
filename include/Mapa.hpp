#pragma once
#include <vector>
#include "Celda.hpp"
typedef std::vector<std::vector<Celda>> MATRIX;
class Mapa
{
  private:
    MATRIX Mapa_;
  public:
    Mapa(const int& row, const int& column);
    MATRIX& get_Mapa_();
};
