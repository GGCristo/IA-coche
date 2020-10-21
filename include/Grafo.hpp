#pragma once
#include <vector>
#include <array>
#include <queue>
#include "Mapa.hpp"

class Grafo
{
  private:
    std::vector<std::array<int,4>> TablaGrafo_;
    std::queue<std::pair<int, int>> Cola_;
  public:
    Grafo(Malla&);
};
