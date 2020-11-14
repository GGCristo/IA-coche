#include "../include/algoritmos.hpp"

bool mysort(const std::pair<Celda*, float> &a, const std::pair<Celda*, float> &b)
{
  return (a.second < b.second);
}

void Heuristica(std::vector<Celda*>& vector_desordenado)
{
  std::vector<std::pair<Celda*, float>> nuevo_vector;
  for (int i = 0; i < vector_desordenado.size(); i++)
  {
    double h;
    if (opcion_heuristico == 0)
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

  vector_desordenado.clear();
  for (int i = 0; i < nuevo_vector.size(); i++) {
    vector_desordenado.push_back(nuevo_vector[i].first);
  }
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

bool encontrar(Celda* celda, const std::vector<Celda*>& cola)
{
  for (auto it = cola.begin(); it != cola.end(); ++it)
  {
    if (*it == celda)
    {
      return true;
    }
  }
  return false;
}

void Elprimeromejor()
{
  std::vector<Celda*> cola;
  cola.reserve(Malla::get_instance().M_*Malla::get_instance().N_);
  cola.push_back(&Malla::get_instance().getEstadoInicial());
  std::vector<Celda*>::iterator it = cola.begin();
  ElMejor(cola, it);
}

// TODO no puedo hacer a la celda constante
void ElMejor(std::vector<Celda*>& cola, std::vector<Celda*>::iterator& it)
{
  if ((*it)->get_i() == Malla::get_instance().getEstadoFinal().get_i() &&
      (*it)->get_j() == Malla::get_instance().getEstadoFinal().get_j())
  {
    return;
  }
  Celda* NORTE = &Malla::get_instance()[(*it)->get_i() - 1][(*it)->get_j()];
  Celda* SUR   = &Malla::get_instance()[(*it)->get_i() + 1][(*it)->get_j()];
  Celda* OESTE = &Malla::get_instance()[(*it)->get_i()][(*it)->get_j() - 1];
  Celda* ESTE  = &Malla::get_instance()[(*it)->get_i()][(*it)->get_j() + 1];
  std::vector<Celda*> heuristico;
  if (!NORTE->getOcupacion() && !encontrar(NORTE, cola))
  {
    heuristico.push_back(NORTE);
    NORTE->setRetorno(*it);
  }
  if (!SUR->getOcupacion() && !encontrar(SUR, cola))
  {
    heuristico.push_back(SUR);
    SUR->setRetorno(*it);
  }
  if (!OESTE->getOcupacion()&& !encontrar(OESTE, cola))
  {
    heuristico.push_back(OESTE);
    OESTE->setRetorno(*it);
  }
  if (!ESTE->getOcupacion() && !encontrar(ESTE, cola))
  {
    heuristico.push_back(ESTE);
    ESTE->setRetorno(*it);
  }
  if (heuristico.size() > 1)
  {
    Heuristica(heuristico);
  }
  for (int i = 0; i < heuristico.size(); i++)
  {
    cola.push_back(heuristico[i]);
  }
//CUIDADO
  if (++it == cola.end())
  {
    return;
  }

  ElMejor(cola, it);
}
