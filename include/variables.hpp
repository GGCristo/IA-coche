#pragma once

namespace vr
{
  constexpr static int DEFAULT = -1;
  constexpr static int OBSTACULO = -2;
  constexpr static int MURO = -3;
  constexpr static int INICIAL = 0;
  constexpr static int FINAL = 1;
}

namespace tx
{
  constexpr static int GRASS = 0;
  constexpr static int BOX = 1;
  constexpr static int ENTRADA = 2;
  constexpr static int SALIDA = 3;
  constexpr static int COCHE = 4;
  constexpr static int WALL = 5;
}

namespace cr
{
  constexpr static int NORTE = 1;
  constexpr static int SUR = -1;
  constexpr static int ESTE = 2;
  constexpr static int OESTE = 3;
}