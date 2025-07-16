/*Definição da classe Script, com o atributo image (pointer para a um elemento da classe Image),
sendo esta imagem a trabalhar nas member functions desta classe */

#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {

  public: 
    Script(const std::string &filename); //Constructor - Definição;
    ~Script(); //Destructor - Definição;
    void run(); //Função para processar os comandos do script file - Definição;
    //Simple image manipulation
    void invert(); //Transforma cada pixel (r,g,b) em (255-r,255-g,255-b) - Definição;
    void to_gray_scale(); //Transforma cada pixel (r, g, b) em (v, v, v), sendo v = (r + g + b)/3 - Definição;
    void replace(); //Substitui todos os píxeis (r1,  g1, b1) por píxeis (r2,  g2, b2) - Definição;
    void fill(); //Preenche todos os píxeis da imagem com (r, g, b) -> Color c; Outros parâmetros: Coordenadas canto esquerdo (x, y), altura - h, largura - w - Definição;
    void h_mirror(); //Espelha a imagem horizontalmente - Definição;
    void v_mirror(); //Espelha a imagem verticalmente - Definição;
    void add(); //Copia todos os pixeis de image para um PNG, exceto pixeis com a cor (r, g, b). Outros parâmetros: Coordenadas canto esquerdo (x, y) - Definição;
    //Dimenson-changing operations
    void crop(); //Corta a imagem image a partir do canto esquerdo: coordenadas (x, y), para uma imagem final com as dimensões altura - h, largura - w - Definição;
    void rotate_left(); //Roda a imagem 90º para a esquerda - Definição;
    void rotate_right(); //Roda a imagem 90ª para a direita - Definição;
    //Advanced functionality
    void median_filter(); //Aplica o median filter à imagem - Definição
    void xpm2_open(); //Abre um ficheiro do formato XPM2 - Definição
    void xpm2_save(); //Guarda um ficheiro no formato XPM2 - Definição

  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::ifstream input;
    // Private functions
    void clear_image_if_any();
    void blank();
    void open();
    void save();
  };
}
#endif
