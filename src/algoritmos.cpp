#include "../include/algoritmos.hpp"

bool estaprocesada(Celda* celda, const std::deque<Celda*>& procesados)
{
  for (int i = 0; i < procesados.size(); ++i)
  {
    if (celda == procesados[i])
    {
      return true;
    }
  }
  return false;
}

void ElMejor(Celda& celda, std::queue<Celda*>& visitados, std::deque<Celda*>& procesados)
{
  if (celda.get_i() == Malla::get_instance().getEstadoFinal().first &&
      celda.get_j() == Malla::get_instance().getEstadoFinal().second)
  {
    return;
  }
  else
  {
    Celda* NORTE = &Malla::get_instance()[celda.get_i() - 1][celda.get_j()];
    Celda* SUR   = &Malla::get_instance()[celda.get_i() + 1][celda.get_j()];
    Celda* OESTE = &Malla::get_instance()[celda.get_i()][celda.get_j() - 1];
    Celda* ESTE  = &Malla::get_instance()[celda.get_i()][celda.get_j() + 1];
    if (!NORTE->getOcupacion() && !estaprocesada(NORTE, procesados))
    {
      visitados.push(NORTE);
      NORTE->setRetorno(&celda);
    }
    else if (!SUR->getOcupacion() && !estaprocesada(SUR, procesados))
    {
      visitados.push(SUR);
      SUR->setRetorno(&celda);

    }
    else if (!OESTE->getOcupacion() && !estaprocesada(OESTE,procesados))
    {
      visitados.push(OESTE);
      OESTE->setRetorno(&celda);

    }
    else if (!ESTE->getOcupacion() && !estaprocesada(ESTE, procesados))
    {
      visitados.push(ESTE);
      ESTE->setRetorno(&celda);
    }
    Celda* nueva = visitados.front();
    visitados.pop();
    procesados.push_back(nueva);
    ElMejor(*nueva, visitados, procesados);
  }
}
