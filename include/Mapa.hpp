#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "Celda.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "random.hpp" // Libreria ajena (https://github.com/effolkronium/random)

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

typedef std::vector<std::vector<Celda>> MATRIX;

class Malla
{
  private:
    static int PorcentajeDeObstaculos;
    MATRIX Malla_;
    int M_; // Filas
    int N_; // Columnas
    std::pair<int, int> EstadoInicial;
    std::pair<int, int> EstadoFinal;
    void ConstruirObstaculos();
    float CalcularTamanoCelda() const;
    void ColocarPunto(const int&);
  public:
    Malla(int row, int column);
    const int& getRow() const;
    const int& getColumn() const;
    const MATRIX& getMalla();
    const std::pair<int, int>& getEstadoInicial() const;
    const std::pair<int, int>& getEstadoFinal() const;
    void Click(int, int);
    void Control_Entrada(int, int);
    void Control_Salida(int, int);
    void ConstruirGrafo();
    std::ostream& mostrar(std::ostream&);
    const std::vector<Celda>& operator [](const int&);

    // Interfaz
    void draw(sf::RenderWindow& window);
};
