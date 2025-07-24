//
// Created by ricardo on 30/06/25.
//

#ifndef NOVO_MODELO_QUADRO_H
#define NOVO_MODELO_QUADRO_H

#include <vector>

class Quadro {
private:
    char controle;
    char idSessao;
    char idProto;
    std::vector<char> dados;
public:
    Quadro(const std::vector<char> & dados);

    Quadro();
    void setSessao(const int & bit0, const int & bit1, const int & bit2);
    std::vector<int> getTipoControle();
    bool getIsControle();
    void setControleInt(const int & controle);
    void setControleChar(const char & controle);
    void setIdProto(const char & idProto);
    void setDados(const std::vector<char> &dados);
    std::vector<char> serialize(bool data, bool controle);
    Quadro deserializer(const std::vector<char> & dados);
    void setSequencia(int sequencia);
    void setIdSessao(char idSessao);
    char getIdSessao();
    int getSequencia();
    std::vector<char> getDados();
    int getControle();
};


#endif //NOVO_MODELO_QUADRO_H
