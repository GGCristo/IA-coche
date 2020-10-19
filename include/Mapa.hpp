#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "Celda.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../include/random.hpp" // Libreria ajena (https://github.com/effolkronium/random)

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

typedef std::vector<std::vector<Celda>> MATRIX;

class Mapa
{
  private:
    static int PorcentajeDeObstaculos;
    friend class Grafo;
    MATRIX Mapa_;
    int M_; // Filas
    int N_; // Columnas
    // TODO Necesito esto?
    std::pair<int, int> EstadoInicial;
    std::pair<int, int> EstadoFinal;
    void ConstruirObstaculos();
    void ColocarEstadoInicial();
    void ColocarEstadoFinal();
  public:
    Mapa(const int& row, const int& column);
    const int& getRow() const;
    const int& getColumn() const;
    MATRIX& get_Mapa();
    void ConstruirGrafo();
    std::ostream& mostrar(std::ostream&);

    // Interfaz
    void draw(sf::RenderWindow& window);
};
