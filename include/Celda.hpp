#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <array>
class Celda: public sf::Drawable
{
  private:
    int i_;
    int j_;
    int Estado_;
    bool EFinal_;

    // Interfaz
    sf::RectangleShape celda;
    std::array<sf::RectangleShape, 4> muros;

    void setPosition(const sf::Vector2f&);
  public:
    Celda(const float& tamano = 50.F);
    Celda(const Celda&);
    ~Celda() override;
    bool getOcupacion() const;
    void Ocupar();
    const int& getEstado() const;
    void setEstado(const int&);
    void setPosicion(const int& i, const int& j);
  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
