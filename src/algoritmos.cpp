#include "../include/algoritmos.hpp"

bool mysort(const std::pair<Celda*, float> &a, const std::pair<Celda*, float> &b)
{
  return (a.second < b.second);
}

std::vector<Celda*> Heuristica(std::vector<Celda*>& vector_desordenado)
{
  std::vector<std::pair<Celda*, float>> nuevo_vector;
  for (int i = 0; i < vector_desordenado.size(); i++)
  {
    double h;
    if (opcion == 0)
    {
      h = (abs(vector_desordenado[i]->get_i() - Malla::get_instance().getEstadoFinal().get_i()) + abs(vector_desordenado[i]->get_j() - Malla::get_instance().getEstadoFinal().get_j()));
    }
    else
    {
       h = sqrt(pow((vector_desordenado[i]->get_i() - Malla::get_instance().getEstadoFinal().get_i()),2)
     + pow((vector_desordenado[i]->get_j() - Malla::get_instance().getEstadoFinal().get_j()), 2));
    }
    nuevo_vector.push_back(std::make_pair(vector_desordenado[i], h));
  }

  std::sort(nuevo_vector.begin(), nuevo_vector.end(), mysort);

  std::vector<Celda*> vector_ordenado;
  for (int i = 0; i < nuevo_vector.size(); i++)
  {
    vector_ordenado.push_back(nuevo_vector[i].first);
  }
  return vector_ordenado;
}

bool estaprocesada(Celda* celda, const std::deque<Celda*>& procesados)
{
  for (const auto &i: procesados)
  {
    if (celda == i)
    {
      return true;
    }
  }
  return false;
}

bool estaenvisitas(Celda* celda, const std::deque<Celda*>& visitaras)
{
  for (const auto &i : visitaras)
  {
    if (celda == i)
    {
      return true;
    }
  }
  return false;
}

void Elprimeromejor()
{
  std::deque<Celda*> visitaras;
  std::deque<Celda*> procesados;
  ElMejor(Malla::get_instance().getEstadoInicial(), visitaras, procesados);
}

// TODO no puedo hacer a la celda constante
void ElMejor(Celda& celda, std::deque<Celda*>& visitaras, std::deque<Celda*>& procesados)
{
  if (celda.get_i() == Malla::get_instance().getEstadoFinal().get_i() &&
      celda.get_j() == Malla::get_instance().getEstadoFinal().get_j())
  {
    return;
  }
  Celda* NORTE = &Malla::get_instance()[celda.get_i() - 1][celda.get_j()];
  Celda* SUR   = &Malla::get_instance()[celda.get_i() + 1][celda.get_j()];
  Celda* OESTE = &Malla::get_instance()[celda.get_i()][celda.get_j() - 1];
  Celda* ESTE  = &Malla::get_instance()[celda.get_i()][celda.get_j() + 1];
  std::vector<Celda*> heuristico;
  if (!NORTE->getOcupacion() && !estaprocesada(NORTE, procesados) && !estaenvisitas(NORTE, visitaras))
  {
    heuristico.push_back(NORTE);
    NORTE->setRetorno(&celda);
  }
  if (!SUR->getOcupacion() && !estaprocesada(SUR, procesados) && !estaenvisitas(SUR, visitaras))
  {
    heuristico.push_back(SUR);
    SUR->setRetorno(&celda);
  }
  if (!OESTE->getOcupacion() && !estaprocesada(OESTE,procesados) && !estaenvisitas(OESTE, visitaras))
  {
    heuristico.push_back(OESTE);
    OESTE->setRetorno(&celda);
  }
  if (!ESTE->getOcupacion() && !estaprocesada(ESTE, procesados) && !estaenvisitas(ESTE, visitaras))
  {
    heuristico.push_back(ESTE);
    ESTE->setRetorno(&celda);
  }
  if (!heuristico.empty())
  {
    heuristico = Heuristica(heuristico);
  }
  for (int i = 0; i < heuristico.size(); i++)
  {
    visitaras.push_back(heuristico[i]);
  }

  if (visitaras.empty())
  {
    return;
  }

  Celda* nueva = visitaras.front();
  visitaras.erase(visitaras.begin());
  procesados.push_back(&celda);
  ElMejor(*nueva, visitaras, procesados);
}
