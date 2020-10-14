#pragma once
#include <iostream>
#include <vector>
#include "Celda.hpp"
#include "../include/random.hpp" // Libreria ajena (https://github.com/effolkronium/random)

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

typedef std::vector<std::vector<Celda>> MATRIX;

class Mapa
{
  private:
    MATRIX Mapa_;
    int M_; // Filas
    int N_; // Columnas

    void ConstruirObstaculos();
    void ColocarEstadoInicial();
  public:
    Mapa(const int& row, const int& column);
    const int& getRow() const;
    const int& getColumn() const;
    MATRIX& get_Mapa();
    std::ostream& mostrar(std::ostream&);
};
