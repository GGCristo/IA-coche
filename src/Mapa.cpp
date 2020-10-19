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
    for (int i = 0; i < M_ * N_ * (PorcentajeDeObstaculos/100.0); i++)
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
    if (Mapa_[fila - 1][columna - 1].getOcupacion() ||
        Mapa_[fila - 1][columna - 1].getEstado() == 1)
    {
      std::cout << "Esa casilla esta ocupada, use otra\n";
      control = true;
    }
    else if (fila != 1 && columna != 1 &&
             fila != M_ && columna != N_)
    {
      std::cout << "Coloque el punto en un extremo\n";
      control = true;
    }
  }while(control);

  Mapa_[fila - 1][columna - 1].setEstado(0);
  EstadoInicial.first = fila - 1;
  EstadoInicial.second = columna - 1;
  mostrar(std::cout);
}
// TODO Refactorizar código para que no haya duplicidad con EstadoInicial
void Mapa::ColocarEstadoFinal()
{
  bool control;
  int columna;
  int fila;
  do
  {
    control = false;
    std::cout << "¿Donde quiere colocar el punto Final?\n";
    std::cout << "Fila: ";
    std::cin >> fila;
    std::cout << "Columna: ";
    std::cin >> columna;
    if (Mapa_[fila - 1][columna - 1].getOcupacion() || 
        Mapa_[fila - 1][columna - 1].getEstado() == 0)
    {
      std::cout << "Esa casilla esta ocupada, use otra\n";
      control = true;
    }
    else if (fila != 1 && columna != 1 &&
             fila != M_ && columna != N_)
    {
      std::cout << "Coloque el punto en un extremo\n";
      control = true;
    }
  }while(control);

  Mapa_[fila - 1][columna - 1].setEstado(1);
  EstadoFinal.first = fila - 1;
  EstadoFinal.second = columna - 1;
  mostrar(std::cout);
}

void Mapa::draw(sf::RenderWindow& window)
{
  for (int i = 0; i < M_; i++)
  {
    for (int j = 0; j < N_; j++)
    {
      window.draw(Mapa_[i][j]);
    }
  }

}

Mapa::Mapa(const int& row, const int& column) : Mapa_(row)
{
  M_ = row;
  N_ = column;
  for (int i = 0; i < M_; i++)
  {
    Mapa_[i].resize(N_, Celda(60.F));
    // El contenedor ya esta dimensionado pero necesito que cada celda
    // sea conciente de su posición.
    for (int j = 0; j < N_; j++)
    {
      Mapa_[i][j].setPosicion(i, j);
    }
  }

  mostrar(std::cout);

  ConstruirObstaculos();

  ColocarEstadoInicial();

  ColocarEstadoFinal();
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
      if (Mapa_[i][j].getEstado() == -2)
      {
        os << 'x';
      }
      else if (Mapa_[i][j].getEstado() == -1)
      {
        os << ' ';
      }
      else if (Mapa_[i][j].getEstado() == 0)
      {
        os << 'I';
      }
      else
      {
        os << 'F';
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
