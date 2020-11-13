#pragma once
#include <queue>
#include <deque>
#include <cmath>
#include "Celda.hpp"
#include "Malla.hpp"
const int opcion = 0;
std::vector<Celda*> Heuristica(std::vector<Celda*>& vector_desordenado);
bool mysort(const std::pair<Celda*, float> &a, const std::pair<Celda*, float> &b);
void Elprimeromejor();
void ElMejor(Celda&, std::deque<Celda*>&, std::deque<Celda*>&);
