#include "../include/Malla.hpp"
#include <catch2/catch_test_macros.hpp>

int Mapa::PorcentajeDeObstaculos = 10;

TEST_CASE("Vamos a probar el nuevo Catch")
{
  REQUIRE(1 == 1);
}
// TEST_CASE("Puedo recorrer todo el vector")
// {
//   Mapa mapa = Mapa(50, 60);
//   for (int i = 0; i < mapa.get_Mapa().size(); i++)
//   {
//     for (int j = 0; j < mapa.get_Mapa()[i].size(); j++)
//     {
//       mapa.get_Mapa()[i][j];
//     }
//   }
// }
//
// TEST_CASE("Se ocupa la celda que yo quiero")
// {
//   Mapa mapa = Mapa(50, 60);
//   mapa.get_Mapa()[20][20].Ocupar();
//   REQUIRE(mapa.get_Mapa()[20][20].getOcupacion());
// }
