/*Implementação da classe Color, com os atributos red_, green_ e blue_ representando cada um, um dos componentes da definição
de uma cor segundo o modelo RGB*/

#include "Color.hpp"

namespace prog {
    //Default Constructor - Implementação;
    Color::Color() {
        red_= 0;
        green_= 0;
        blue_= 0;
    }

    //Copy Constructor - Implementação;
    Color::Color(const Color& other) {
        red_ = other.red_;
        blue_= other.blue_;
        green_ = other.green_;
    }

    //Constructor com recurso a parâmetros - Implementação;
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        red_ = red;
        blue_ = blue;
        green_ = green;
    }

    //Função Get para o atributo red_ - Implementação;
    rgb_value Color::red() const {
        return red_;
    }

    //Função Get para o atributo green_ - Implementação;
    rgb_value Color::green() const {
        return green_;
    }

    //Função Get para o atributo blue_ - Implementação;
    rgb_value Color::blue() const {
        return blue_;
    }

    //Função Set para o atributo red_ - Implementação;
    rgb_value& Color::red()  {
        return red_;
    }

    //Função Set para o atributo green_ - Implementação;
    rgb_value& Color::green()  {
      return green_;
    }

    //Função Set para o atributo blue_ - Implementação;
    rgb_value& Color::blue()  {
      return blue_;
    }
}