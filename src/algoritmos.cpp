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

bool estaenvisitas(Celda* celda, const std::deque<Celda*>& visitaras)
{
  for (int i = 0; i < visitaras.size(); ++i)
  {
    if (celda == visitaras[i])
    {
      return true;
    }
  }
  return false;
}

char carga()
{
  static int variable = 0;
  char nombre[] = {'\\', '|', '/', '-'};
  if (variable == 4) variable = 0;
  return nombre[variable++];
}

void ElMejor(Celda& celda, std::deque<Celda*>& visitaras, std::deque<Celda*>& procesados)
{
  if (celda.get_i() == Malla::get_instance().getEstadoFinal().first &&
      celda.get_j() == Malla::get_instance().getEstadoFinal().second)
  {
    // std::cout << "Explota cuando va a retornar el final\n";
    return;
  }
  else
  {
    std::cout << "Cargando" + std::string(1, carga()) << '\n';
    Celda* NORTE = &Malla::get_instance()[celda.get_i() - 1][celda.get_j()];
    Celda* SUR   = &Malla::get_instance()[celda.get_i() + 1][celda.get_j()];
    Celda* OESTE = &Malla::get_instance()[celda.get_i()][celda.get_j() - 1];
    Celda* ESTE  = &Malla::get_instance()[celda.get_i()][celda.get_j() + 1];
    if (!NORTE->getOcupacion() && !estaprocesada(NORTE, procesados) && !estaenvisitas(NORTE, visitaras))
    {
      visitaras.push_back(NORTE);
      NORTE->setRetorno(&celda);
    }
    if (!SUR->getOcupacion() && !estaprocesada(SUR, procesados) && !estaenvisitas(SUR, visitaras))
    {
      visitaras.push_back(SUR);
      SUR->setRetorno(&celda);
    }
    if (!OESTE->getOcupacion() && !estaprocesada(OESTE,procesados) && !estaenvisitas(OESTE, visitaras))
    {
      visitaras.push_back(OESTE);
      OESTE->setRetorno(&celda);
    }
    if (!ESTE->getOcupacion() && !estaprocesada(ESTE, procesados) && !estaenvisitas(ESTE, visitaras))
    {
      visitaras.push_back(ESTE);
      ESTE->setRetorno(&celda);
    }
    Celda* nueva;
    if (!visitaras.empty())
    {
      nueva = visitaras.front();
    }
    else
    {
      return;
    }
    visitaras.erase(visitaras.begin());
    procesados.push_back(&celda);
    ElMejor(*nueva, visitaras, procesados);
  }
}
