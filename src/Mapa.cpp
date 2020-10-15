#include "../include/Mapa.hpp"
#include <vector>

void Mapa::ConstruirObstaculos()
{
  int opcion;
  do
  {
    std::cout << "Colocar obstaculos manual(0) o aleatorio(1)\n";
    std::cin >> opcion;
  } while (opcion != 0 && opcion != 1);

  if (opcion == 1)
  {
    for (int i = 0; i < M_ * N_ * 0.1; i++)
    {
      Mapa_[Random::get(0, M_ - 1)][Random::get(0, N_ - 1)].Ocupar();
    }
    mostrar(std::cout);
  }
  else
  {
    int columna;
    int fila;
    int otro;
    do
    {
      std::cout << "Fila del obstaculo: ";
      std::cin >> fila;
      std::cout << "Columna del obstaculo ";
      std::cin >> columna;
      if (fila - 1 > getRow() || columna - 1 > getColumn())
      {
        std::cout << "La Fila o la Columna estan fuera de limite\n";
        otro = 1;
      }
      else
      {
        if (Mapa_[fila - 1][columna - 1].getOcupacion())
        {
          std::cout << "Esa posición ya esta ocupada...\n";
        }
        else
        {
          Mapa_[fila - 1][columna - 1].Ocupar();
          mostrar(std::cout);
        }
        std::cout << "¿Quiere poner otro obstaculo (Si[1];No[0])?: ";
        std::cin >> otro;
      }
    }
    while(otro);
  }
}

void Mapa::ColocarEstadoInicial()
{
  bool control;
  int columna;
  int fila;
  do
  {
    control = false;
    std::cout << "¿Donde quiere colocar el punto Inicial?\n";
    std::cout << "Fila: ";
    std::cin >> fila;
    std::cout << "Columna: ";
    std::cin >> columna;
    if (Mapa_[fila - 1][columna - 1].getOcupacion())
    {
      std::cout << "Esa casilla esta ocupada, use otra\n";
      control = true;
    }
    else if (fila != getRow() && columna != getColumn())
    {
      std::cout << "Coloque el punto en un extremo\n";
      control = true;
    }
  }while(control);

  Mapa_[fila - 1][columna - 1].Estado_ = 0;
  EstadoInicial.first = fila - 1;
  EstadoInicial.second = columna - 1;
  mostrar(std::cout);
}

Mapa::Mapa(const int& row, const int& column) : Mapa_(row)
{
  M_ = row;
  N_ = column;
  for (int i = 0; i < M_; i++)
  {
    Mapa_[i].resize(N_);
    // El contenedor ya esta dimensionado pero necesito que cada celda
    // sea conciente de su posición.
    for (int j = 0; j < N_; j++)
    {
      Mapa_[i][j].i = i;
      Mapa_[i][j].j = j;
    }
  }

  mostrar(std::cout);

  ConstruirObstaculos();

  ColocarEstadoInicial();
}

const int& Mapa::getRow() const
{
  return M_;
}

const int& Mapa::getColumn() const
{
  return N_;
}

MATRIX& Mapa::get_Mapa()
{
  return Mapa_;
}

void Mapa::ConstruirGrafo()
{

}

std::ostream& Mapa::mostrar(std::ostream& os)
{
  // Cabecera
  for (int i = 0; i < N_; i++)
  {
    os << " -";
  }
  os << '\n';
  for (int i = 0; i < M_; i++)
  {
    os << "|";
    for (int j = 0; j < N_; j++)
    {
      if (Mapa_[i][j].Estado_ == -2)
      {
        os << 'x';
      }
      else if (Mapa_[i][j].Estado_ != 0)
      {
        os << ' ';
      }
      else
      {
        os << 'I';
      }
      os << "|";
    }
    os << '\n';
    // Pie
    for (int z = 0; z < N_; z++)
    {
      os << " -";
    }
    os << '\n';
  }
  os << '\n';
  return os;
}
