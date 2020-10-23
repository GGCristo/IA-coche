#include "../include/Mapa.hpp"
#include "../include/variables.hpp"

void Malla::ConstruirObstaculos()
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
      Malla_[Random::get(0, M_ - 1)][Random::get(0, N_ - 1)].Ocupar();
    }
    mostrar(std::cout);
  }
  // else
  // {
  //   int columna;
  //   int fila;
  //   int otro;
  //   do
  //   {
  //     std::cout << "Fila del obstaculo: ";
  //     std::cin >> fila;
  //     std::cout << "Columna del obstaculo ";
  //     std::cin >> columna;
  //     if (fila - 1 > getRow() || columna - 1 > getColumn())
  //     {
  //       std::cout << "La Fila o la Columna estan fuera de limite\n";
  //       otro = 1;
  //     }
  //     else
  //     {
  //       if (Mapa_[fila - 1][columna - 1].getOcupacion())
  //       {
  //         std::cout << "Esa posición ya esta ocupada...\n";
  //       }
  //       else
  //       {
  //         Mapa_[fila - 1][columna - 1].Ocupar();
  //         mostrar(std::cout);
  //       }
  //       std::cout << "¿Quiere poner otro obstaculo (Si[1];No[0])?: ";
  //       std::cin >> otro;
  //     }
  //   }
  //   while(otro);
  // }
}

void Malla::ColocarPunto(const int& punto, int row, int col)
{
  bool control;
  int columna = col;
  int fila = row;
  if (punto == vr::FINAL)
  {
    Malla_[fila][columna].setEstado(vr::FINAL);
    EstadoFinal.first = fila;
    EstadoFinal.second = columna;
  }
  else
  {

    Malla_[fila][columna].setEstado(vr::INICIAL);
    EstadoInicial.first = fila;
    EstadoInicial.second = columna;
  }
  mostrar(std::cout);
}

void Malla::draw(sf::RenderWindow& window)
{
  for (int i = 0; i < M_; i++)
  {
    for (int j = 0; j < N_; j++)
    {
      window.draw(Malla_[i][j]);
    }
  }

}

Malla::Malla(const int& row, const int& column) : Malla_(row)
{
  M_ = row;
  N_ = column;
  for (int i = 0; i < M_; i++)
  {
    Malla_[i].resize(N_, Celda(CalcularTamanoCelda(row, column)));
    // El contenedor ya esta dimensionado pero necesito que cada celda
    // sea conciente de su posición.
    for (int j = 0; j < N_; j++)
    {
      Malla_[i][j].setPosicion(i, j);
    }
  }

  mostrar(std::cout);

  ConstruirObstaculos();
}

const int& Malla::getRow() const
{
  return M_;
}

const int& Malla::getColumn() const
{
  return N_;
}

MATRIX& Malla::get_Mapa()
{
  return Malla_;
}

void Malla::Click(int x, int y)
{
  int i_ = int(( (float)y ) / Malla_[0][0].getSize().x);
  int j_ = int(( (float)x ) / Malla_[0][0].getSize().y);
  if (Malla_[i_][j_].getOcupacion())
  {
    Malla_[i_][j_].setEstado(vr::DEFAULT);
  }
  else if (Malla_[i_][j_].getEstado() == vr::DEFAULT)
  {
    Malla_[i_][j_].setEstado(vr::OBSTACULO);
  }
  std::cout << "He pinchado en: " << i_ << j_ << '\n';
}

void Malla::Control_Entrada(int x, int y)
{
  int i_ = int(( (float)y ) / Malla_[0][0].getSize().x);
  int j_ = int(( (float)x ) / Malla_[0][0].getSize().y);
  if (Malla_[i_][j_].getEstado() != vr::FINAL)
  {
    Malla_[EstadoInicial.first][EstadoInicial.second].setEstado(vr::DEFAULT);
    ColocarPunto(vr::INICIAL, i_, j_);
  }
}

void Malla::Control_Salida(int x, int y)
{
  int i_ = int(( (float)y ) / Malla_[0][0].getSize().x);
  int j_ = int(( (float)x ) / Malla_[0][0].getSize().y);
  if (Malla_[i_][j_].getEstado() != vr::INICIAL)
  {
    Malla_[EstadoFinal.first][EstadoFinal.second].setEstado(vr::DEFAULT);
    ColocarPunto(vr::FINAL, i_, j_);
  }
}

void Malla::ConstruirGrafo()
{

}

// El tamaño de las celdad es lo máximo que le permita el tamaño de la pantalla
const float Malla::CalcularTamanoCelda(const int& row, const int& column)
{
  auto anchura = sf::VideoMode::getDesktopMode().width / column;
  auto altura  = sf::VideoMode::getDesktopMode().height / row;
  return (float)(std::min(anchura, altura));
}

std::ostream& Malla::mostrar(std::ostream& os)
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
      if (Malla_[i][j].getEstado() == vr::OBSTACULO)
      {
        os << 'x';
      }
      else if (Malla_[i][j].getEstado() == vr::DEFAULT)
      {
        os << ' ';
      }
      else if (Malla_[i][j].getEstado() == vr::INICIAL)
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
