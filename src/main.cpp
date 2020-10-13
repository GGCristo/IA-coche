#include <iostream>
#include "../include/random.hpp" // Libreria ajena (https://github.com/effolkronium/random)
#include "../include/Mapa.hpp"
#include "../include/Celda.hpp"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

int main()
{
  std::cout << "Introduzca el numero de filas" << '\n';
  int row;
  std::cin >> row;
  std::cout << "Introduzca el numero de columnas" << '\n';
  int column;
  std::cin >> column;

  Mapa mapa = Mapa(row, column);
  mapa.mostrar(std::cout);

  int opcion;
  do
  {
    std::cout << "Colocar obstaculos manual(0) o aleatorio(1)\n";
    std::cin >> opcion;
  } while (opcion != 0 && opcion != 1);

  if (opcion == 1)
  {
    for (int i = 0; i < row * column * 0.1; i++)
    {
      mapa.get_Mapa()[Random::get(0, row - 1)][Random::get(0, column - 1)].Ocupar();
    }
  }
  mapa.mostrar(std::cout);
  return 0;
}
