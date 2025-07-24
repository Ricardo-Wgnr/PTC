//
// Created by ricardo on 30/06/25.
//

#include "Quadro.h"

Quadro::Quadro(const std::vector<char> & dados) {
    this->dados = dados;
    this->idSessao = 0;
}

Quadro::Quadro() {}

void Quadro::setSessao(const int & bit0, const int & bit1, const int & bit2) {
    this->controle &= 0x00;
    this->controle |= bit0;
    this->controle |= bit1 << 1;
    this->controle |= bit2 << 2;
}

std::vector<int> Quadro::getTipoControle() {
    std::vector<int> tipoControle;
    tipoControle.push_back(this->controle & 0x1);
    tipoControle.push_back((this->controle & 0x2) >> 1);
    return tipoControle;
}

bool Quadro::getIsControle() {
    return (this->controle & 0x4) >> 2;
}

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

void Quadro::setIdSessao(char idSessao) {
    this->idSessao = idSessao;
}

char Quadro::getIdSessao() {
    return this->idSessao;
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

std::vector<char> Quadro::serialize(bool data, bool controle) {
    std::vector<char> serializado;

    serializado.push_back(this->controle);
    serializado.push_back(this->idSessao);
    if (controle) {
        serializado.push_back(this->idProto);
    } else {
        if (data) {
            serializado.push_back(this->idProto);
            for (auto c : this->dados) {
                serializado.push_back(c);
            }
        }
    }
    return serializado;
}

Quadro Quadro::deserializer(const std::vector<char> & dados) {
    Quadro quadro;
    quadro.setControleChar(dados[0]);
    quadro.setIdSessao(dados[1]);
    if (quadro.getControle() == 0) {
        if (quadro.getIsControle()) {
            quadro.setIdProto(dados[2]);
        } else {
            quadro.setIdProto(dados[2]);
            std::vector<char> buffer(dados.begin()+3, dados.end());
            quadro.setDados(buffer);
        }
    }
    return quadro;
}
