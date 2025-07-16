/*Implementação da classe Script, com o atributo image (pointer para a um elemento da classe Image),
sendo esta imagem a trabalhar nas member functions desta classe */

#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    //Operator overload - Usado para ler cores no formato RGB a patir de um ficheiro script;
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    //Constructor, cujo filename indica o script a ser processado. Inicialmente, nenhuma imagem é carregada;
    Script::Script(const string& filename) : image(nullptr), input(filename) {

    }

    //Destructor da classe Script - Implementação;
    Script::~Script() {
        clear_image_if_any();
    }

    //Função para processar os comandos do script file - Implementação;
    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            //Initialization and I/O;
            if (command == "open") {
                open();
                continue;
            }

            if (command == "blank") {
                blank();
                continue;
            }
            
            if (command == "save") {
                save();
                continue;
            } 
            
            //Simple image manipulation;
            if (command == "invert"){
                invert();
                continue;
            }

            if (command == "to_gray_scale"){
                to_gray_scale();
                continue;
            }

            if (command == "replace"){
                replace();
                continue;
            }

            if (command == "h_mirror"){
                h_mirror();
                continue;
            }

            if (command == "v_mirror"){
                v_mirror();
                continue;
            }

            if (command == "fill"){
                fill();
                continue;
            }

            if (command == "add"){
                add();
                continue;
            }

            //dimenson-changing operations;
            if (command == "crop"){
                crop();
                continue;
            }
            
            if (command == "rotate_left"){
                rotate_left();
                continue;
            }

            if (command == "rotate_right"){
                rotate_right();
                continue;
            }

            //advanced functionality;
            if (command == "median_filter"){
                median_filter();
                continue;
            }

            if (command == "xpm2_open"){
                xpm2_open();
                continue;
            }

            if (command == "xpm2_save"){
                xpm2_save();
                continue;
            }
        }
    }

    //Função para limpar o atributo image caso este não esteja vazio;
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }

    //Define o atributo image com uma imagem completamente branca;
    void Script::blank() {
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }

    //Define o atributo image com uma imagem "lida" a partir de um ficheiro PNG;
    void Script::open() {
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    } 

    //Guarda a imagem atual em formato PNG;
    void Script::save() {
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    
    //Transforma cada píxel (r, g, b) em (255-r, 255-g, 255-b) - Implementação;
    void Script::invert(){    
        int h=this->image->height();
        int w=this->image->width();
        for (int i=0;i<w;i++){
            for (int j=0;j<h;j++){ //percorre todos os píxeis da imagem e posteriormente substitui os valores
                this->image->at(i,j).red()=255-this->image->at(i,j).red(); 
                this->image->at(i,j).green()=255-this->image->at(i,j).green();
                this->image->at(i,j).blue()=255-this->image->at(i,j).blue();
            }
        }
    }

    //Transforma cada píxel (r, g, b) em (v, v, v), sendo v = (r + g + b)/3 - Implementação;
    void Script::to_gray_scale(){
        int h=this->image->height();
        int w=this->image->width();
        for (int i=0;i<w;i++){
            for (int j=0;j<h;j++){ //percorre todos os píxeis da imagem
                int grey = (this->image->at(i,j).red()+this->image->at(i,j).green()+this->image->at(i,j).blue())/3; //tom a substituir
                this->image->at(i,j) = Color(grey,grey,grey);
            }
        }
    }

    //Substitui todos os píxeis (r1, g1, b1) por píxeis (r2, g2, b2) - Implementação;
    void Script::replace (){
        int r1, g1, b1, r2, g2, b2;
        input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
        int h = this->image->height();
        int w = this->image->width();
        for (int i=0;i<w;i++){
            for (int j=0;j<h;j++){ //percorre todos os píxeis da imagem
                Color aux = this->image->at(i, j);
                if(aux.red() == r1 && aux.green() == g1 && aux.blue() == b1){ //compara a cor do píxel selecionado
                    aux.red() = r2;
                    aux.green() = g2;
                    aux.blue() = b2;
                    image->at(i, j) = Color(aux.red(), aux.blue(), aux.green());
                }
            }
        }
    }

    //Preenche todos os píxeis da imagem com (r, g, b) -> Color c; Outros parâmetros: Coordenadas canto esquerdo (x, y), altura - h, largura - w - Implementação;
    void Script::fill(){
        int x, y; //canto superior esquerdo
        int w, h; //tamanho da janela
        Color c; 
        input >> x >> y >> w >> h >> c;
        for (int i=x;i<x+w;i++){
            for (int j=y;j<y+h;j++){ //percorre todos os píxeis da janela dada
                this->image->at(i,j) = c;
            }
        }
    }

    //Espelha a imagem horizontalmente - Implementação;
    void Script::h_mirror(){
        int w, h;
        w=image->width();
        h=image->height();
        Image& original = *image; //imagem original
        image = new Image(w,h); //nova imagem com as dimensões pedidas
        for (int i=0 ; i<w/2 ; i++){
            for (int j=0 ; j<h ; j++){ //percorre todos os píxeis da imagem na primeira metade do comprimento
                image->at(i,j)=original.at(w-i-1,j); //percorre a imagem original e copia os píxeis para a nova imagem
            }
        }

        for (int i=w/2 ; i<w ; i++){
            for (int j=0 ; j<h ; j++){//percorre todos os píxeis da imagem na segunda metade do comprimento
                image->at(i,j)=original.at(w-i-1,j); //percorre a imagem original e copia os píxeis para a nova imagem
            }
        }
        delete &original;
    }

    //Espelha a imagem verticalmente - Implementação;
    void Script::v_mirror(){
        int w, h;
        w=image->width();
        h=image->height();
        Image& original = *image; //imagem original
        image = new Image(w,h); //nova imagem com as dimensões pedidas
        for (int i=0 ; i<w ; i++){
            for (int j=0 ; j<h/2 ; j++){//percorre todos os píxeis da imagem na primeira metade da altura;
                image->at(i,j)=original.at(i, h - 1 - j); //percorre a imagem original e copia os píxeis para a nova imagem
            }
        }

        for (int i=0 ; i<w ; i++){
            for (int j=h/2 ; j<h ; j++){//percorre todos os píxeis da imagem na segunda metade da altura;
                image->at(i,j)=original.at(i, h - 1 - j); //percorre a imagem original e copia os píxeis para a nova imagem
            }
        }
        delete &original;
    }

    //Copia todos os píxeis de image para um PNG, exceto píxeis com a cor (r, g, b). Outros parâmetros: Coordenadas canto esquerdo (x, y) - Implementação;
    void Script::add(){
        int w, h; //canto superior esquerdo
        Color c;
        string filename;
        input >> filename >> c >> w >> h;
        Image& adicionar = *loadFromPNG(filename); //lê a imagem a adicionar
        Image& original = *image; //imagem original
        int imw = adicionar.width();
        int imh = adicionar.height();
        for (int i=0;i<imw;i++){
            for (int j=0;j<imh;j++){ //percorre todos os píxeis da imagem a adicionar;
                const Color& novacor = adicionar.at(i, j);
                if (novacor.red() == c.red() && novacor.green() == c.green() && novacor.blue() == c.blue()) {//verifica se a cor do píxel é igual à cor "proibida"
                    continue;
                }
                original.at(w + i, h + j) = novacor; //atribuição da nova cor do píxel da imagem original se for diferente da cor "proibida"
            }
        }
        delete &adicionar;
    }

    //Corta a imagem image a partir do canto esquerdo: coordenadas (x, y), para uma imagem final com as dimensões altura - h, largura - w - Implementação;
    void Script::crop(){
        int x, y; //canto superior esquerdo
        int w, h; //tamanho da nova imagem
        input >> x >> y >> w >> h;
        Image& original = *image; //imagem original
        image = new Image(w,h); //nova imagem com as dimensões pedidas
        for (int i=x ; i<x+w ; i++){
            for (int j=y ; j<y+h ; j++){ //percorre todos os píxeis da imagem original tendo em conta as dimensões da nova imagem
                image->at(i-x,j-y)=original.at(i,j); //percorre a imagem original e copia os píxeis para a nova imagem
            }
        }
        delete &original;
    }

    //Roda a imagem 90º para a esquerda - Implementação;
    void Script::rotate_left(){
        int w, h;
        w=image->width();
        h=image->height();
        Image& original = *image; //imagem original
        image = new Image(h,w); //nova imagem com as dimensões pedidas
        for (int i=0 ; i<w ; i++){
            for (int j=0 ; j<h ; j++){
                image->at(j,w-i-1)=original.at(i,j); //percorre a imagem original e copia os píxeis para a nova imagem tendo em conta a orientação da rotação
            }
        }
        delete &original;
    }

    //Roda a imagem 90ª para a direita - Implementação;
    void Script::rotate_right(){
        int w, h;
        w=image->width();
        h=image->height();
        Image& original = *image; //imagem original
        image = new Image(h,w); //nova imagem com as dimensões pedidas
        for (int i=0 ; i<w ; i++){
            for (int j=0 ; j<h ; j++){
                image->at(h-j-1,i)=original.at(i,j); //percorre a imagem original e copia os píxeis para a nova imagem tendo em conta a orientação da rotação
            }
        }
        delete &original;
    
    }

    //Aplica o median filter à imagem - Implementação
    void Script::median_filter(){
        int w, h, ws;
        input >> ws; //tamanho da vizinhança
        w=image->width();
        h=image->height();
        Image& original = *image; //imagem original
        image = new Image(w,h); //nova imagem com as dimensões originais
        for (int i=0 ; i<w ; i++){ //percorre todos os píxeis da imagem
            for (int j=0 ; j<h ; j++){
                int *mr=new int[ws*ws], *mg=new int[ws*ws], *mb=new int[ws*ws], counter=0; //criação de arrays dinâmicos com os valores r g b para cálculo da mediana, e de um counter com o tamanho dos arrays declarados dinamicamente
                for (int k=max(0,i-ws/2); k<=min(w-1,i+ws/2);k++){ //percorre os píxeis na vizinhança do píxel a substituir
                    for (int l=max(0,j-ws/2); l<=min(h-1,j+ws/2);l++){
                        mr[counter]=original.at(k,l).red(); //guarda os valores r g b desses píxeis para fazer a mediana
                        mg[counter]=original.at(k,l).green();
                        mb[counter]=original.at(k,l).blue();
                        counter++; //atualização do tamanho dos arrays
                    }
                }
                int tempr,tempg,tempb; //ordenação crescente dos arrays
                for(int u=0 ; u<counter ; u++)
                {
                    for(int s=0 ; s<counter-1 ; s++)
                    {
                        if(mr[s]>mr[s+1])
                        {
                            tempr = mr[s];
                            mr[s] = mr[s+1];
                            mr[s+1] = tempr;
                        }
                        if(mg[s]>mg[s+1])
                        {
                            tempg = mg[s];
                            mg[s] = mg[s+1];
                            mg[s+1] = tempg;
                        }
                        if(mb[s]>mb[s+1])
                        {
                            tempb = mb[s];
                            mb[s] = mb[s+1];
                            mb[s+1] = tempb;
                        }
                    }
                }
                Color c; //cor do píxel a substituir
                if(counter%2 == 0){
                    c = Color((mr[(counter-1)/2] + mr[counter/2])/2,(mg[(counter-1)/2] + mg[counter/2])/2,(mb[(counter-1)/2] + mb[counter/2])/2);
                }
                else{
                    c = Color(mr[counter/2],mg[counter/2],mb[counter/2]);
                }
                image->at(i,j)=c; //substituição da cor do píxel
                delete[] mr; //libertação da memória ocupada pelos arrays dinâmicos
                delete[] mg;
                delete[] mb;
            }
        }
        delete &original; //libertação da memória ocupada pela imagem original
    }

    //Função para abrir um ficheiro do tipo XPM2;
    void Script::xpm2_open(){
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromXPM2(filename);
    }

    //Função para guardar um ficheiro no formato XPM2;
    void Script::xpm2_save(){
        string filename;
        input >> filename;
        saveToXPM2(filename, image);
    }
}