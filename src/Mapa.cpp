#include "../include/Mapa.hpp"
#include <vector>

Mapa::Mapa(const int& row, const int& column) : Mapa_(row)
{
  M_ = row;
  N_ = column;
  for (int i = 0; i < M_; i++)
  {
    Mapa_[i].resize(N_);
  }
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
      os << ((Mapa_[i][j].getOcupacion()) ? 'x' : ' ');
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
