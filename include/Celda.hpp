#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <array>
/**
 * @brief Clase Celda que controla su comportamiento tanto en la interfaz como
 *        en el código.
 */
class Celda: public sf::Drawable
{
  private:
    int i_;
    int j_;
    int Estado_;
    Celda* retorno_;
    // bool EFinal_;

    // Interfaz
    /**
     * @celda Instancia para la interfaz
     */
    sf::RectangleShape celda;
    /**
     * @muros Los 4 muros que rodean cada celda, para cear el efecto de malla
     */
    std::array<sf::RectangleShape, 4> muros;

  public:
    /**
     * @brief Constructor por defecto, los indices "i_" y "j_" se ponen a -1
     *        porque necesitan ser asignados en setPosicion, se crean los "muros"
     *        internos, y se pone el estado por defecto (vr::DEFAULT)
     */
    explicit Celda(float tamano = 50.F);
    /**
     * @brief Se necesita hacer copias porque la malla se crea con un resize
     *
     */
    Celda(const Celda&);
    /**
     * @brief Necesito un constructor aunque este vacío porque SFML lo requiere
     *
     */
    ~Celda() override;
    /**
     * @brief Saber si la celda es un obstaculo o muro
     *
     * @return TRUE si la celda el un muro u obstaculo, false en otro caso
     */
    bool getOcupacion() const;
    /**
     * @brief Convierte el "Estado_" en OBSTACULO,
     *        equivalente a setEstado(vr::OBSTACULO)
     *
     */
    void Ocupar();
    const int get_i() const;
    const int get_j() const;
    void setRetorno(Celda*);
    // const Celda* getRetorno();
    Celda* getRetorno() const;
    /**
     * @brief Devuelve el "Estado_" en el que se encuentra la celda
     *
     */
    const int& getEstado() const;
    /**
     * @brief Asigno el estado de la celda
     *
     * @param {estado} Estado que va a adquirir la celda (Ej vr::OBSTACULO)
     */
    void setEstado(int estado);
    /**
     * @brief [Interfaz] Devuelve la posción de la Celda
     *
     */
    const sf::Vector2f& getPosition() const;
    /**
     * @brief Asigna los indices de la Celda y su posción y la de los muros
     *        en la interfaz
     *
     * @param i Fila en la que esta posicionada la celda
     * @param j Columna en la que esta posicionada la celda
     */
    void setPosicion(int i, int j);
    /**
     * @brief [Interfaz] Devuelve el tamaño del atributo celda
     *
     */
    const sf::Vector2f& getSize() const;
  protected:
    /**
     * @brief [Interfaz] Heredo de la clase "Drawable", para poder pasar las
     *        instancias de Celda por la función draw e indicarle como dibujarlo
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
