#include "../include/Grafo.hpp"

Grafo::Grafo(Mapa& mapa)
{
  // Introduzco el estado inicial (estado 0);
  Cola_.push(std::make_pair(mapa.EstadoInicial.first, mapa.EstadoInicial.second));

}
