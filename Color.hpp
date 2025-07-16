/*Definição da classe Color, com os atributos red_, green_ e blue_ representando cada um, um dos componentes da definição
de uma cor segundo o modelo RGB*/

#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  //Definição do tipo rgb_value como unsigned char;
  typedef unsigned char rgb_value;

  class Color
  {
    
    private:
      rgb_value red_; //Atributo representativo da cor vermelha (0 - 255);
      rgb_value green_; //Atributo representativo da cor verde (0 - 255);
      rgb_value blue_; //Atributo representativo da cor azul (0 - 255);

    public:
      Color(); //Default Constructor - Definição;
      Color(const Color& c); //Copy Constructor - Definição;
      Color(rgb_value r, rgb_value g, rgb_value b); //Constructor com recurso a parâmetros - Definição;
      rgb_value red() const; //Função Get para o atributo red_ - Definição;
      rgb_value green() const; //Função Get para o atributo green_ - Definição;
      rgb_value blue() const; //Função Get para o atributo blue_ - Definição;
      rgb_value& red(); //Função Set para o atributo red_ - Definição:
      rgb_value& green(); //Função Set para o atributo green_ - Definição;
      rgb_value& blue(); //Função Set para o atributo blue_ - Definição;
  };
}

#endif