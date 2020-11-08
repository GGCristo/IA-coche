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
    /**
     * @brief Poner obstaculos aleatorios por la malla
     *        Se crea una lista de números y se van sacando números aleatorios
     *        esto se hace para asegurarnos que se rellena la cantidad exacta
     *
     */
    void ConstruirObstaculos();
    /**
     * @brief Devolvemos el tamaño de las celdas, acorde al tamaño de la malla
     *        Esto se consigue con una división básica y devolviendo el valor
     *        mínimo de la anchura y altura pues la celda tiene que ser cuadrada
     *
     * @return [TODO:description]
     */
    float CalcularTamanoCelda() const;
    /**
     * @brief Coloca el punto Final o Inicial en su respectiva posición
     *
     * @param punto vr::FINAL o vr::INICIAL
     * @param row indice de la fila
     * @param col indice de la columna
     */
    void ColocarPunto(int punto, int row, int col);
    /**
     * @brief Coloca los muros que rodean la malla
     *
     */
    void Levantar_muros();
    Malla();
  public:
    static Malla& get_instance();
    const int& getRow() const;
    const int& getColumn() const;
    const std::pair<int, int>& getEstadoInicial() const;
    const std::pair<int, int>& getEstadoFinal() const;
    void Click(int, int);
    void Control_Entrada(int, int);
    void Control_Salida(int, int);
    void ConstruirGrafo();
    bool haySalidayEntrada() const;
    std::ostream& mostrar(std::ostream&);
    const std::vector<Celda>& operator [](int) const;
    std::vector<Celda>& operator [](int);

    // Interfaz
    void draw(sf::RenderWindow& window);
};
