#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
class Celda: public sf::Drawable
{
  private:
    friend class Mapa;
    int i_;
    int j_;
    int Estado_;
    bool EFinal_;

    // Interfaz
    sf::RectangleShape celda;
    sf::RectangleShape muros[4];
    // TODO añadir más texturas
    sf::Texture texturas[3];

    void setPosition(const sf::Vector2f&);
  public:
    Celda(const float& tamano = 50.F);
    ~Celda() override;
    bool getOcupacion() const;
    void Ocupar();
    const int& getEstado() const;
    void setEstado(const int&);
    void setPosicion();
    void cargarTexturas();
  protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
