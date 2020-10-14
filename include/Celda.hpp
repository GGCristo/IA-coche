#pragma once
class Celda
{
  private:
    friend class Mapa;
    bool Ocupada_;
    int Estado_;
    bool EFinal_;
  public:
    Celda();
    const bool& getOcupacion() const;
    void Ocupar();
};
