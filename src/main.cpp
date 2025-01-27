#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>
#include <chrono>
#include <algorithm> // reverse
#include <thread>
#include "../include/Malla.hpp"
#include "../include/Celda.hpp"
#include "../include/Coche.hpp"
#include "../include/Texturas.hpp"
#include "../include//algoritmos.hpp"

#include <iostream>
#include <fstream>

int Malla::PorcentajeDeObstaculos = 10;
std::ifstream Malla::fichero_;
int opcion_heuristico = 0;

/**
 * @brief Bucle para que el usuario cree las condiciones iniciales del "tablero"
 *
 * @param window ventana para hacer el proceso interactivo
 * @param malla Guarda los cambios en la malla, para poder trabajar con los datos
 */
static void modificarTerreno(sf::RenderWindow& window);

int casoFichero(int argc, char* argv[]);
/**
 * @brief Muestra el resultado del algoritmo
 *
 * @param window Muestralo a travez de esta ventana
 * @param malla Malla donde se va a mover el coche que vamos a crear dentro
 */
void main_loop(sf::RenderWindow& window, std::vector<Celda*> recorrido)
{
  Coche coche(Malla::get_instance()[0][0].getSize(), recorrido);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
    }
    window.clear();
    Malla::get_instance().draw(window);
    window.draw(coche);
    window.display();
    coche.Move();
  }
}

int main(int argc, char* argv[])
{
  int id = casoFichero(argc, argv);

  if (id > 0)
  {
    return id;
  }

  // Inicializo las texturas para que en caso de que no
  // cargen el programa cierre de forma segura
  try
  {
    Texturas::getTexturas();
  }
  catch(const char* msg)
  {
    std::cerr << msg;
    return 1;
  }

  Malla::get_instance();

  do
  {
    std::cout << "Algoritmo a usar\n";
    std::cout << "Manhattan[0] Euclidea[1]\n";
    std::cin >> opcion_heuristico;
  } while(opcion_heuristico != 0 && opcion_heuristico != 1);

  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "IA-COCHE", sf::Style::Fullscreen);
  window.setFramerateLimit(15);
  modificarTerreno(window);
  // Pongo el sleep porque el programa me detecta el enter de forma prematura
  sf::sleep(sf::seconds(0.25));

  if (window.isOpen())
  {
    auto t1 = std::chrono::high_resolution_clock::now();
    Elprimeromejor();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "El algoritmo tardó:\n"
              << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " microsegundos | "
              << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()/1000.0 << " milisegundos | "
              << std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()/1000000.0 << " segundos\n";

    std::vector<Celda*> recorrido;
    if (Malla::get_instance().getEstadoFinal().getRetorno() == nullptr)
    {
      std::cout << "No hay camino disponible";
      return 1;
    }
    else
    {
      Celda* celda = &Malla::get_instance().getEstadoFinal();
      while(celda != nullptr)
      {
        recorrido.push_back(celda);
        celda = celda->getRetorno();
      }
      std::reverse(recorrido.begin(), recorrido.end());
    }

    std::cout << "Longitud minima: " << recorrido.size() << '\n';
    main_loop(window, recorrido);
  }
  return 0;
}

void modificarTerreno(sf::RenderWindow& window)
{
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed)
      {
        Malla::get_instance().Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
      }
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Space)
        {
          Malla::get_instance().Control_Entrada_Pixel(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        }
        else if (event.key.code == sf::Keyboard::LControl)
        {
          Malla::get_instance().Control_Salida_Pixel(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        }
        else if (event.key.code == sf::Keyboard::Enter && Malla::get_instance().haySalidayEntrada())
        {
          return;
        }
      }
    }
    window.clear();
    Malla::get_instance().draw(window);
    window.display();
  }
}

int casoFichero(int argc, char* argv[])
{
  if (argc == 2 && std::string(argv[1]) == "--help")
  {
    std::cout << "                               ¡AYUDA!" << std::endl;
    std::cout << "---------------------------- MODO DE USO -----------------------------------------" << std::endl;
    std::cout << "Debe ponerlo de la forma: ./bin/main Intput.txt" << std::endl;
    std::cout << "El Input.txt debe ser el fichero de entrada en el que se encuentran las posiciones" << std::endl;
    return 1;
  }
  if (argc > 2)
  {
    std::cout << "Para ver la ayuda ponga: ./bin/main --help" << std::endl;
    return 1;
  }
  if (argc == 2 && std::string(argv[1]) != "--help")
  {
    std::string nombre_fichero_entrada = argv[1];
    std::string linea_fichero;
    Malla::fichero_.open(nombre_fichero_entrada, std::ios::in);
    if (Malla::fichero_.fail())
    {
      std::cout << "No se puede abrir el fichero de entrada porque no existe" << std::endl;
      return 1;
    }

    int numero_lineas_fichero = 0;
    while (Malla::fichero_.good())
    {
      getline(Malla::fichero_, linea_fichero);
      if (!linea_fichero.empty())
      {
        numero_lineas_fichero++;
      }
    }

    if (numero_lineas_fichero < 4)
    {
      std::cout << "Error: El fichero de entrada debe contener al menos 4 líneas" << std::endl;
      Malla::fichero_.close();
      return  1;
    }
    Malla::fichero_.clear();
    Malla::fichero_.seekg(0);
  }
  return 0;
}
