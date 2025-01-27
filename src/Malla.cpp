#include "../include/Malla.hpp"
#include "../include/variables.hpp"

void Malla::ConstruirObstaculos()
{
  if (!fichero_.is_open())
  {
    std::vector<int> lista;
    lista.resize((M_ - 2) * (N_ - 2));
    for (int i = 0; i < lista.size(); ++i)
    {
      lista[i] = i;
    }
    for (int i = 0; i < (M_ - 2) * (N_ - 2) * (PorcentajeDeObstaculos/100.0); i++)
    {
      auto randomIt = Random::get(lista);
      auto row = *randomIt/(N_ - 2);
      auto col = *randomIt - row*(N_ - 2);
      lista.erase(randomIt);
      Malla_[row + 1][col + 1].Ocupar();
    }
  }
  else
  {
    int x;
    int y;
    while (fichero_ >> x >> y)
    {
      Malla_[x][y].Ocupar();
    }
  }
  mostrar(std::cout);
}

void Malla::ColocarPunto(int punto, int row, int col)
{
  if (punto == vr::FINAL)
  {
    Malla_[row][col].setEstado(vr::FINAL);
    EstadoFinal = &Malla_[row][col];
  }
  else
  {
    Malla_[row][col].setEstado(vr::INICIAL);
    EstadoInicial = &Malla_[row][col];
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

Malla::Malla()
{
  EstablecesFilasyColumnas();
  EstadoInicial = nullptr;
  EstadoFinal = nullptr;
  Malla_.resize(M_);
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
  if (fichero_.is_open())
  {
    LeerEntradaySalida();
    ConstruirObstaculos();
    fichero_.close();
  }
  else
  {
    int esAleatorio;
    do
    {
      std::cout << "Colocar obstaculos manual(0) o aleatorio(1)\n";
      std::cin >> esAleatorio;
    } while (esAleatorio != 0 && esAleatorio != 1);
    if (esAleatorio == 1)
    {
      ConstruirObstaculos();
    }
  }
}

Malla& Malla::get_instance()
{
  static Malla instance;
  return instance;
}

void Malla::EstablecesFilasyColumnas()
{
  if (!fichero_.is_open())
  {
    std::cout << "Introduzca el numero de filas" << '\n';
    int row;
    std::cin >> row;
    std::cout << "Introduzca el numero de columnas" << '\n';
    int column;
    std::cin >> column;
    M_ = row + 2;
    N_ = column + 2;
  }
  else
  {
    std::string linea_fichero;
    getline(fichero_, linea_fichero);
    M_ = atoi(linea_fichero.c_str()) + 2;
    std::cout << linea_fichero << std::endl;
    getline(fichero_, linea_fichero);
    N_ = atoi(linea_fichero.c_str()) + 2;
    std::cout << linea_fichero << std::endl;
  }
}

Celda& Malla::getEstadoInicial()
{
  return *EstadoInicial;
}

Celda& Malla::getEstadoFinal()
{
  return *EstadoFinal;
}

const int Malla::getM()
{
  return M_;
}

const int Malla::getN()
{
  return N_;
}

void Malla::Click(int x, int y)
{
  int i = int(( (float)y ) / Malla_[0][0].getSize().x);
  int j = int(( (float)x ) / Malla_[0][0].getSize().y);
  if (Malla_[i][j].getEstado() != vr::MURO)
  {
    if (Malla_[i][j].getOcupacion())
    {
      Malla_[i][j].setEstado(vr::DEFAULT);
    }
    else if (Malla_[i][j].getEstado() == vr::DEFAULT)
    {
      Malla_[i][j].setEstado(vr::OBSTACULO);
    }
  }
}

void Malla::Control_Entrada_Pixel(int x, int y)
{
  int i = int(((float)y) / Malla_[0][0].getSize().x);
  int j = int(( (float)x ) / Malla_[0][0].getSize().y);
  Control_Entrada(i, j);
}

void Malla::Control_Salida_Pixel(int x, int y)
{
  int i = int(((float)y) / Malla_[0][0].getSize().x);
  int j = int(( (float)x ) / Malla_[0][0].getSize().y);
  Control_Salida(i, j);
}

void Malla::Control_Entrada(int i, int j) {
  if (i <= M_ - 1 && j <= N_ - 1 &&
      Malla_[i][j].getEstado() != vr::FINAL &&
      Malla_[i][j].getEstado() != vr::MURO)
  {
    if (EstadoInicial)
    {
      EstadoInicial->setEstado(vr::DEFAULT);
    }
    ColocarPunto(vr::INICIAL, i, j);
  }
}

void Malla::Control_Salida(int i, int j)
{
  if (i <= M_ - 1 && j <= N_ - 1 &&
      Malla_[i][j].getEstado() != vr::INICIAL &&
      Malla_[i][j].getEstado() != vr::MURO)
  {
    if (EstadoFinal)
    {
      EstadoFinal->setEstado(vr::DEFAULT);
    }
    ColocarPunto(vr::FINAL, i, j);
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
  return (EstadoInicial && EstadoFinal);
}

const std::vector<Celda>& Malla::operator [](int pos) const
{
  return Malla_[pos];
}

std::vector<Celda>& Malla::operator [](int pos)
{
  return Malla_[pos];
}

void Malla::LeerEntradaySalida() {
  int x;
  int y;
  fichero_ >> x >> y;
  Control_Entrada(x, y);
  fichero_ >> x >> y;
  Control_Salida(x, y);
}
