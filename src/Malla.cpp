#include "../include/Malla.hpp"
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
      Malla_[Random::get(1, M_ - 2)][Random::get(1, N_ - 2)].Ocupar();
    }
    mostrar(std::cout);
  }
}

void Malla::ColocarPunto(int punto, int row, int col)
{
  if (punto == vr::FINAL)
  {
    Malla_[row][col].setEstado(vr::FINAL);
    EstadoFinal.first = row; EstadoFinal.second = col;
  }
  else
  {
    Malla_[row][col].setEstado(vr::INICIAL);
    EstadoInicial.first = row; EstadoInicial.second = col;
  }
  mostrar(std::cout);
}

void Malla::Levantar_muros()
{
  for (int i = 0; i < M_; i++)
  {
    Malla_[i][0].setEstado(vr::MURO);
    Malla_[i][N_ - 1].setEstado(vr::MURO);
  }
  for (int i = 0; i < N_; i++)
  {
    Malla_[0][i].setEstado(vr::MURO);
    Malla_[M_ - 1][i].setEstado(vr::MURO);
  }
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

Malla::Malla(int row, int column) : Malla_(row + 2)
{
  M_ = row + 2;
  N_ = column + 2;
  EstadoInicial.first = -1; EstadoInicial.second = -1;
  EstadoFinal.first = -1; EstadoFinal.second = -1;
  for (int i = 0; i < M_; i++)
  {
    Malla_[i].resize(N_, Celda(CalcularTamanoCelda()));
    // El contenedor ya esta dimensionado pero necesito que cada celda
    // sea conciente de su posición.
    for (int j = 0; j < N_; j++)
    {
      Malla_[i][j].setPosicion(i, j);
    }
  }

  Levantar_muros();

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

const std::pair<int, int>& Malla::getEstadoInicial() const
{
  return EstadoInicial;
}

const std::pair<int, int>& Malla::getEstadoFinal() const
{
  return EstadoFinal;
}

void Malla::Click(int x, int y)
{
  int i_ = int(( (float)y ) / Malla_[0][0].getSize().x);
  int j_ = int(( (float)x ) / Malla_[0][0].getSize().y);
  if (Malla_[i_][j_].getEstado() != vr::MURO)
  {
    if (Malla_[i_][j_].getOcupacion())
    {
      Malla_[i_][j_].setEstado(vr::DEFAULT);
    }
    else if (Malla_[i_][j_].getEstado() == vr::DEFAULT)
    {
      Malla_[i_][j_].setEstado(vr::OBSTACULO);
    }
  }
  std::cout << "He pinchado en: " << i_ << j_ << '\n';
}

void Malla::Control_Entrada(int x, int y)
{
  int i_ = int(( (float)y ) / Malla_[0][0].getSize().x);
  int j_ = int(( (float)x ) / Malla_[0][0].getSize().y);
  if (Malla_[i_][j_].getEstado() != vr::FINAL &&
      Malla_[i_][j_].getEstado() != vr::MURO)
  {
    if (EstadoInicial.first >= 0 && EstadoInicial.second >= 0)
    {
      Malla_[EstadoInicial.first][EstadoInicial.second].setEstado(vr::DEFAULT);
    }
    ColocarPunto(vr::INICIAL, i_, j_);
  }
}

void Malla::Control_Salida(int x, int y)
{
  int i_ = int(( (float)y ) / Malla_[0][0].getSize().x);
  int j_ = int(( (float)x ) / Malla_[0][0].getSize().y);
  if (Malla_[i_][j_].getEstado() != vr::INICIAL &&
      Malla_[i_][j_].getEstado() != vr::MURO)
  {
    if (EstadoFinal.first >= 0 && EstadoFinal.second >=  0)
    {
      Malla_[EstadoFinal.first][EstadoFinal.second].setEstado(vr::DEFAULT);
    }
    ColocarPunto(vr::FINAL, i_, j_);
  }
}

// El tamaño de las celdad es lo máximo que le permita el tamaño de la pantalla
float Malla::CalcularTamanoCelda() const
{
  auto anchura = sf::VideoMode::getDesktopMode().width / N_;
  auto altura  = sf::VideoMode::getDesktopMode().height / M_;
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
      if (Malla_[i][j].getEstado() == vr::DEFAULT)
      {
        os << ' ';
      }
      else if (Malla_[i][j].getEstado() == vr::OBSTACULO)
      {
        os << 'x';
      }
      else if (Malla_[i][j].getEstado() == vr::MURO)
      {
        os << 'M';
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

bool Malla::haySalidayEntrada() const
{
  return (EstadoInicial.first >= 0 && EstadoInicial.second >= 0 &&
      EstadoFinal.first >= 0 && EstadoFinal.second >= 0);
}

const std::vector<Celda>& Malla::operator [](int pos) const
{
  return Malla_[pos];
}

std::vector<Celda>& Malla::operator [](int pos)
{
  return Malla_[pos];
}
