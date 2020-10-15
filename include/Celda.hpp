#pragma once
class Celda
{
  private:
    friend class Mapa;
    int i;
    int j;
    int Estado_;
    bool EFinal_;
  public:
    Celda();
    bool getOcupacion() const;
    void Ocupar();
};
