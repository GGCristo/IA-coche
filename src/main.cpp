#include <iostream>
#include "../include/Mapa.hpp"
#include "../include/Celda.hpp"
#include "../include/Grafo.hpp"


int main()
{
  std::cout << "Introduzca el numero de filas" << '\n';
  int row;
  std::cin >> row;
  std::cout << "Introduzca el numero de columnas" << '\n';
  int column;
  std::cin >> column;

  Mapa mapa = Mapa(row, column);

  Grafo grafo(mapa);
  return 0;
}
