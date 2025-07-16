/*Implementação da classe Image, com os atributos width_ (int), height_(int) e pixels(Color**) representando cada um, respetivamente,
o comprimento, a largura e a matriz dos píxeis da imagem*/

#include "Image.hpp" 

namespace prog
{
  //Constructor com recurso a parâmetros ( por definição preenche a foto a branco) - Implementação;
  Image::Image(int w, int h, const Color &fill) : width_(w), height_(h)
  {
    pixels = new Color*[h];
    for (int i=0;i<h;i++){
      pixels[i] = new Color[w];
      for (int j=0;j<w;j++){
        pixels[i][j] = fill;
      }
    }
  }

  //Destructor - Implementação;
  Image::~Image()
  {
    for(int i=(height_-1); i >= 0; i--) {
      delete [] pixels[i];
    }
    delete [] pixels;
  }

  //Função Get para o atributo width_ - Implementação;
  int Image::width() const
  {
    return width_;
  }

  //Função Get para o atributo height_ - Implementação;
  int Image::height() const
  {
    return height_;
  }

  //Função Set para o atributo pixels na posição [y] [x] - Implementação;
  Color& Image::at(int x, int y)
  {
    return pixels[y][x];
  }

  //Função Get para o atributo pixels na posição [y] [x] - Implementação;
  const Color& Image::at(int x, int y) const
  {
    return pixels[y][x];
  }
}