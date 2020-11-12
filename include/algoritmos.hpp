#pragma once
#include <queue>
#include <deque>
#include <cmath>
#include "Celda.hpp"
#include "Malla.hpp"
const int opcion = 1;
std::vector<Celda*> Heuristica(std::vector<Celda*>& vector_desordenado);
std::vector<Celda*> Hola(std::vector<Celda*>& vector_desordenado);
void Elprimeromejor();
void ElMejor(Celda&, std::deque<Celda*>&, std::deque<Celda*>&);
