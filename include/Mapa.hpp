#pragma once
#include <iostream>
#include <vector>
#include "Celda.hpp"

typedef std::vector<std::vector<Celda>> MATRIX;

class Mapa
{
  private:
    MATRIX Mapa_;
    int M_; // Filas
    int N_; // Columnas
  public:
    Mapa(const int& row, const int& column);
    MATRIX& get_Mapa();
    std::ostream& mostrar(std::ostream&);
};
