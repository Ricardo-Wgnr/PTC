//
// Created by ricardo on 30/06/25.
//

#ifndef NOVO_MODELO_QUADRO_H
#define NOVO_MODELO_QUADRO_H

#include <vector>

class Quadro {
private:
    char controle;
    char reservado;
    char idProto;
    std::vector<char> dados;
public:
    Quadro(const std::vector<char> & dados);

    Quadro();

    void setControle(const int & controle);
    void setIdProto(const char & idProto);
    void setDados(const std::vector<char> &dados);
    std::vector<char> serialize(bool data);
    Quadro deserializer(const std::vector<char> & dados);
    void setSequencia(int sequencia);
    void setReservado(char reservado);
    int getSequencia();
    std::vector<char> getDados();
    int getControle();
};


#endif //NOVO_MODELO_QUADRO_H
