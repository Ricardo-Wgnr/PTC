//
// Created by ricardo on 16/06/25.
//

#include "Enquadramento.h"

Enquadramento::Enquadramento(Serial & rf, long timeout): Subcamada(rf.get(), timeout), rf(rf), mef() {
    disable_timeout();
    mef.set_callback_timeout([this](bool en) {
        set_en_timeout(en);
    });
}

vector<char> gera_quadro(const vector<char> & dados) {
    vector<char> quadro;

    quadro.push_back(FLAG);

    for (auto & c: dados) {
        if (c == ESC || c == FLAG) {
            quadro.push_back(ESC);
            quadro.push_back(c ^ 0x20);
        } else {
            quadro.push_back(c);
        }
    }

    quadro.push_back(FLAG);

    return quadro;
}

void Enquadramento::envia(Quadro quadro) {
    //modo correto
    vector<char> buffer = quadro.serialize(true);
    auto crc = make_crc16(buffer);
    crc.generate_into(buffer);
    auto quadroFinal = gera_quadro(buffer);
    rf.write(quadroFinal);
//    vector<char> buffer = dados;
//    auto crc = make_crc16(buffer);
//    crc.generate_into(buffer);
//    auto quadro = gera_quadro(buffer);
//    rf.write(quadro);
//    std::cout << "Enviou quadro: ";
//    for (auto c : quadro) {
//        std::cout << c;
//    }
//    std::cout << std::endl;
    //modo testes
//    rf.write(dados);
}

void Enquadramento::recebe(Quadro quadro) {

}

void Enquadramento::handle() {
    auto buffer = rf.read_byte();
    if (mef.mef(buffer, false)) {
        auto dados = mef.get_dados();
        dados.pop_back();
        dados.pop_back();
        Quadro q;
        Quadro quadro = q.deserializer(dados);
        superior->recebe(quadro);
    }
}

void Enquadramento::handle_timeout() {
    char buffer;
    mef.mef(buffer, true);
}

void Enquadramento::set_en_timeout(bool en) {
    if (en) {
        enable_timeout();
    } else {
        disable_timeout();
    }
}