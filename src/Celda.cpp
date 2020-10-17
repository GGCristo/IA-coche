#include "../include/Celda.hpp"
#include <cassert>

Celda::Celda(const float& tamano)
{
  cargarTexturas();
  i_ = -1;
  j_ = -1;
  Estado_ = -1;
  celda.setSize(sf::Vector2f(tamano, tamano));
  celda.setOrigin(celda.getSize().x / 2, celda.getSize().y / 2);
  celda.setTexture(&texturas[0], true);

  auto acortamiento = 20;
  muros[0].setSize(sf::Vector2f(tamano, tamano / acortamiento));
  muros[0].setOrigin(muros[0].getSize().x / 2, muros[0].getSize().y / 2);

  muros[1].setSize(sf::Vector2f(tamano, tamano / acortamiento));
  muros[1].setOrigin(muros[1].getSize().x / 2, muros[1].getSize().y / 2);


  muros[2].setSize(sf::Vector2f(tamano / acortamiento, tamano));
  muros[2].setOrigin(muros[2].getSize().x / 2, muros[2].getSize().y / 2);

  muros[3].setSize(sf::Vector2f(tamano / acortamiento, tamano));
  muros[3].setOrigin(muros[3].getSize().x / 2, muros[3].getSize().y / 2);

  for (int i = 0; i < 4; i++)
    muros[i].setFillColor(sf::Color::Black);
}

// TODO Cuidado con la concordancia en las texturas
Celda::Celda(const Celda& celda2)
{
  std::cout << "Entro " << '\n';
  cargarTexturas();
  i_ = celda2.i_;
  j_ = celda2.j_;
  Estado_ = celda2.Estado_;
  celda.setSize(sf::Vector2f(celda2.celda.getSize()));
  celda.setOrigin(celda2.celda.getOrigin());
  celda.setTexture(&texturas[0], true);

  auto acortamiento = 20;
  muros[0].setSize(celda2.muros[0].getSize());
  muros[0].setOrigin(celda2.muros[0].getOrigin());

  muros[1].setSize(celda2.muros[1].getSize());
  muros[1].setOrigin(celda2.muros[1].getOrigin());

  muros[2].setSize(celda2.muros[2].getSize());
  muros[2].setOrigin(celda2.muros[2].getOrigin());

  muros[3].setSize(celda2.muros[3].getSize());
  muros[3].setOrigin(celda2.muros[3].getOrigin());

  for (int i = 0; i < 4; i++)
    muros[i].setFillColor(celda2.muros[i].getFillColor());
}

Celda::~Celda()
{}

bool Celda::getOcupacion() const
{
  return (Estado_ == -2);
}

void Celda::Ocupar()
{
  Estado_ = -2;
  celda.setTexture(&texturas[1], true);
}

const int& Celda::getEstado() const
{
  return Estado_;
}

void Celda::setEstado(const int& estado)
{
  Estado_ = estado;
}

void Celda::setPosicion()
{
  assert(i_ != -1 && j_ != -1);

  celda.setPosition((celda.getSize().y) * (float)j_ + celda.getSize().y / 2 + muros[0].getSize().y,
                    (celda.getSize().x) * (float)i_ + celda.getSize().x / 2 + muros[2].getSize().x);
  // TODO encontrar punto para cargando
  std::cout << i_ << ' ' << j_ << ": " << celda.getPosition().x << ' ' << celda.getPosition().y << '\n';

  muros[0].setPosition(sf::Vector2f(celda.getPosition().x,
                        celda.getPosition().y - (celda.getSize().y / 2)));
  muros[1].setPosition(sf::Vector2f(celda.getPosition().x,
                        celda.getPosition().y + (celda.getSize().y / 2)));
  muros[2].setPosition(sf::Vector2f(celda.getPosition().x - (celda.getSize().x / 2),
                        celda.getPosition().y));
  muros[3].setPosition(sf::Vector2f(celda.getPosition().x + (celda.getSize().x / 2),
                        celda.getPosition().y));
}

void Celda::cargarTexturas()
{
  if(!texturas[0].loadFromFile("assets/Graphics/grass.png"))
  {
    std::cerr << "Fallo al cargar la textura de la hierba\n";
    exit(-1);
  }
  if (!texturas[1].loadFromFile("assets/Graphics/box.jpeg"))
  {
    std::cerr << "Fallo al cargar la textura de la caja\n";
    exit(-1);
  }
}

void Celda::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(celda);
  for (int i = 0; i < 4; i++)
     target.draw(muros[i]);
}
