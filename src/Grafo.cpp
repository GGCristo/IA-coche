#include "../include/Grafo.hpp"

Grafo::Grafo(Mapa& mapa)
{
  TablaGrafo_.resize(Mapa::PorcentajeDeObstaculos);
  // Introduzco el estado inicial (estado 0);
  Cola_.push(std::make_pair(mapa.EstadoInicial.first, mapa.EstadoInicial.second));
  // Numero de estados que creo, sin contar el inicial
  int contador = 0;
  while(!Cola_.empty())
  {
    std::pair <int, int> celdaObjeto = Cola_.front();
    Cola_.pop();
    // Norte
    Celda& Norte = mapa.get_Mapa()[celdaObjeto.first - 1][celdaObjeto.second];
    // Sur
    Celda& Sur = mapa.get_Mapa()[celdaObjeto.first + 1][celdaObjeto.second];
    // Oeste
    Celda& Oeste = mapa.get_Mapa()[celdaObjeto.first][celdaObjeto.second - 1];
    // Este
    Celda& Este = mapa.get_Mapa()[celdaObjeto.first][celdaObjeto.second + 1];

    // Norte
    if (Norte.getEstado() == -1)
    {
      TablaGrafo_[contador][0] =
      ++contador;
      Cola_.push(std::make_pair(celdaObjeto.first - 1, celdaObjeto.second));
      Norte.setEstado(contador);
    }
  }
}
