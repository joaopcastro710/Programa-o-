#include "XPM2.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

//conversão int->hexcode
std::string decToHexa(int dec)
{
    if (dec==0) return "00";
	int hex=dec;
	std::string hexcode = "";
	while (dec>0)
	{
		hex = dec % 16;
		if (hex<10){
            hexcode = hexcode.insert(0, std::string(1, (hex + 48)));
        }
		else{
            hexcode = hexcode.insert(0, std::string(1, (hex + 55)));
        }
		dec = dec/16;
	}
	return hexcode;
}

namespace prog {
    //Abre um ficheiro do formato XPM2 - Implementação
    Image* loadFromXPM2(const std::string& file) {
        std::string line;
        std::ifstream st(file);
        Image* image;
        int w,h,n=0,c,counter=0;
        std::string *co, *ch;
        while (getline(st,line)){
            if (counter==1){ //segunda linha do ficheiro (a primeira é ignorada)
                std::stringstream ss;
                ss << line;
                ss >> w >> h >> n >> c; //leitura das dimensões e dos dados do ficheiro
                co = new std::string[n]; //array dinâmico com as cores dadas
                ch = new std::string[n]; //array dinâmico com os chars correspondentes
                image = new Image(w,h); //imagem com as dimensões pedidas
            }
            else if (counter<=n+1 && counter!=0){ //linhas da declaração das cores e mapeamento dos chars
                std::stringstream ss;
                std::string temp;
                ss << line;
                ss >> ch[counter-2] >> temp >> co[counter-2]; //atribuição das cores e dos chars aos arrays
            }
            else if (counter>n+1){ //linhas com todos os píxeis e os chars de cada um (todas as restantes)
                std::stringstream ss;
                ss << line;
                std::string temp,temp2; //temp2 serve apenas para simplificar a compreensão da soma de caracteres c que correspondem a uma única cor. Para o propósito do projeto c==1, no entanto, em teoria, esta implementação desta função em específico deve suportar valores de c maiores que 1.
                ss >> temp;
                
                for (int j=0;j<w;j+=c){ 
                    temp2 = temp[j];
                    for (int p=1;p<c;p++){
                        temp2=temp2+temp[j+c]; //leitura de grupos de c píxeis que correspondem a uma única cor (mais uma vez, para o propósito do projeto c==1)
                    }
                    for (int k=0;k<n;k++){
                        if (temp2==ch[k]){ //procura a igualdade entre o grupo de píxeis lido e a lista de caracteres declarada no início do ficheiro xpm
                            std::string rString = co[k].substr(1, 2); //conversão do hex code para inteiros r,g,b e para um objeto da classe Color
                            std::string gString = co[k].substr(3, 2);
                            std::string bString = co[k].substr(5, 2);

                            int r = std::stoi(rString, nullptr, 16);
                            int g = std::stoi(gString, nullptr, 16);
                            int b = std::stoi(bString, nullptr, 16);
                            image->at(j,counter-n-2) = Color(r,g,b); // atribuição da cor encontrada ao píxel
                        }
                    }
                }
            }
            counter++; //atualização do counter com o número de linhas do ficheiro
            
        }
        st.close();
        delete[] co; //libertação da memória ocupada pelos arrays dinâmicos usados
        delete[] ch;
        return image; //retorna a imagem computada
    }

    //Guarda um ficheiro no formato XPM2 - Implementação
    void saveToXPM2(const std::string& file, const Image* image) {
        int w = image->width();
        int h = image->height();
        std::string line;
        std::ofstream out(file);
        Color *co = new Color[128]; //assumindo que c==1, o número de caracteres usáveis na tabela ascii é 128, portanto não poderá haver mais do que 128 cores numa imagem
        
        out << "! XPM2\n"; //primeira linha do ficheiro
        int counter=0; //número de cores do ficheiro
        for (int i=0;i<h;i++){
            for (int j=0;j<w;j++){ //percorre os píxeis todos da imagem que queremos gravar para guardar o número de cores e as próprias cores
                int flag=0;
                for (int k=0;k<counter;k++){
                    if (co[k].red()==image->at(j,i).red() && co[k].green()==image->at(j,i).green() && co[k].blue()==image->at(j,i).blue()) flag=1;
                }
                if (flag==0){
                    co[counter]=image->at(j,i);
                    counter++;
                }
            }
        }
        out << w << " "  << h << " " << counter << " " << 1 << "\n"; //grava a segunda linha (c==1)
        for (int i=0;i<counter;i++){ //percorre todas as cores guardadas
            std::string hexcode = "#";
            hexcode += decToHexa(co[i].red()); //conversão de int para uma string correspondente ao hexcode através de uma função definida no início deste ficheiro
            hexcode += decToHexa(co[i].green());
            hexcode += decToHexa(co[i].blue());
            out << char(i) << " c " << hexcode << "\n"; //grava a cor e um char correspondente
        }
        for (int i=0;i<h;i++){
            for (int j=0;j<w;j++){
                for (int k=0;k<counter;k++){
                    if (co[k].red()==image->at(j,i).red() && co[k].green()==image->at(j,i).green() && co[k].blue()==image->at(j,i).blue()){
                        out << char(k); //grava todos os char que constroem o ficheiro XPM2 e possibilitam a identificação da cor dos píxeis
                    }
                }
            }
            out << "\n";
        }
        delete[] co; //liberta a memória utilizada pelo array dinâmico das cores guardadas
    }
}
