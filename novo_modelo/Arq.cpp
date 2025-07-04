//
// Created by ricardo on 30/06/25.
//

#include "Arq.h"

Arq::Arq() : Subcamada(-1, 5000) {
    this->m = 0;
    this->n = 0;
    estadoAtual = Estado::Ocioso;
}

void Arq::mef(Quadro quadro, bool tx) {
    switch (estadoAtual) {
        case Estado::Ocioso:
            handleOcioso(quadro, tx);
            break;
        case Estado::Espera:
            handleEspera(quadro, tx);
            break;
    }
}

void Arq::handleOcioso(Quadro quadro, bool tx) {
    if (tx) {
        quadro.setSequencia(this->n);
        inferior->envia(quadro);
        estadoAtual = Estado::Espera;
    }
}

void Arq::handleEspera(Quadro quadro, bool tx) {

}

void Arq::envia(Quadro quadro) {
    this->mef(quadro, true);
}

void Arq::recebe(Quadro quadro) {

}

void Arq::handle() {

}

void Arq::handle_timeout() {

}
