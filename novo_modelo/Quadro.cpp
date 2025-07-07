//
// Created by ricardo on 30/06/25.
//

#include "Quadro.h"

Quadro::Quadro(const std::vector<char> & dados) {
    this->dados = dados;
    this->reservado = 0;
}

Quadro::Quadro() {}

void Quadro::setControleInt(const int & controle) {
    this->controle &= 0x7f;
    this->controle |= controle << 7;
}

void Quadro::setControleChar(const char & controle) {
    this->controle = controle;
}

int Quadro::getControle() {
    return (this->controle & 0x80) >> 7;
}

void Quadro::setIdProto(const char & idProto) {
    this->idProto = idProto;
}

void Quadro::setDados(const std::vector<char> & dados) {
    this->dados = dados;
}

void Quadro::setReservado(char reservado) {
    Quadro::reservado = reservado;
}

void Quadro::setSequencia(int sequencia) {
    this->controle &= 0xf7;
    this->controle |= sequencia << 3;
}

int Quadro::getSequencia() {
    return (this->controle & 0x8) >> 3;
}

std::vector<char> Quadro::getDados() {
    return this->dados;
}

std::vector<char> Quadro::serialize(bool data) {
    std::vector<char> serializado;

    serializado.push_back(this->controle);
    serializado.push_back(this->reservado);
    if (data) {
        serializado.push_back(this->idProto);
        for (auto c : this->dados) {
            serializado.push_back(c);
        }
    }

    return serializado;
}

Quadro Quadro::deserializer(const std::vector<char> & dados) {
    Quadro quadro;
    quadro.setControleChar(dados[0]);
    quadro.setReservado(dados[1]);
    if (quadro.getControle() == 0) {
        quadro.setIdProto(dados[2]);
        auto it = dados.begin();
        it++;
        it++;
        it++;
        std::vector<char> buffer(it, dados.end());
        quadro.setDados(buffer);
    }

    return quadro;
}
