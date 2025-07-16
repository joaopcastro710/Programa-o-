/*Definição da classe Image, com os atributos width_ (int), height_(int) e pixels(Color**) representando cada um, respetivamente,
o comprimento, a largura e a matriz dos píxeis da imagem*/

#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__

#include "Color.hpp"

namespace prog
{
  class Image
  {

  private:
     int width_; //Atributo para o comprimento da Imagem;
     int height_; //Atributo para a largura da Imagem;
     Color** pixels; //Atributo para a matriz dos pixeis (Color) da Imagem;

  public:
    Image(int w, int h, const Color &fill = {255, 255, 255}); //Constructor com recurso a parâmetros ( por definição preenche a foto a branco) - Definição;
    ~Image(); //Destructor - Definição;
    int width() const; //Função Get para o atributo width_ - Definição;
    int height() const; //Função Get para o atributo height_ - Definição;
    Color &at(int x, int y); //Função Set para o atributo pixels na posição [y] [x] - Definição;
    const Color &at(int x, int y) const; //Função Get para o atributo pixels na posição [y] [x] - Definição;
  };
}

#endif