#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/Mapa.hpp"

TEST_CASE("Puedo recorrer todo el vector")
{
  Mapa mapa = Mapa(50, 60);
  for (int i = 0; i < mapa.get_Mapa_().size(); i++)
  {
    for (int j = 0; j < mapa.get_Mapa_()[i].size(); j++)
    {
      mapa.get_Mapa_()[i][j];
    }
  }
}
