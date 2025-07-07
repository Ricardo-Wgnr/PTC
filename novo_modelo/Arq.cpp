//
// Created by ricardo on 30/06/25.
//

#include "Arq.h"

Arq::Arq() : Subcamada(0, 5000) {
    this->m = 0;
    this->n = 0;
    estadoAtual = Estado::Ocioso;
}

void Arq::mef(Quadro quadro, bool tx, bool timeout) {
    switch (estadoAtual) {
        case Estado::Ocioso:
            handleOcioso(quadro, tx, timeout);
            break;
        case Estado::Espera:
            handleEspera(quadro, tx, timeout);
            break;
    }
}

void Arq::handleOcioso(Quadro quadro, bool tx, bool timeout) {
    if (tx && (timeout == false)) {
        quadro.setSequencia(this->n);
        quadro.setControleInt(0);
        inferior->envia(quadro);
        estadoAtual = Estado::Espera;
    } else if (tx == false) {
        if (quadro.getSequencia() == this->m) {
            Quadro ack;
            ack.setControleInt(1);
            ack.setSequencia(this->m);
            ack.setReservado(0);
            inferior->envia(ack);
            superior->recebe(quadro);
            this->m = not this->m;
        } else {
            Quadro ack;
            ack.setControleInt(1);
            ack.setSequencia(not this->m);
            ack.setReservado(0);
            inferior->recebe(ack);
        }
    } 
}

void Arq::handleEspera(Quadro quadro, bool tx, bool timeout) {
    if (tx && (timeout)) {
        inferior->envia(this->quadroTx);
    } else if (tx == false) {
        if (quadro.getControle() == 1) {
            if (quadro.getSequencia() == this->n) {
                this->n = not this->n;
                estadoAtual = Estado::Ocioso;
            }
        } else if (quadro.getSequencia() == this->m) {
            Quadro ack;
            ack.setControleInt(1);
            ack.setSequencia(this->m);
            ack.setReservado(0);
            inferior->envia(ack);
            superior->recebe(quadro);
            this->m = not this->m;
        } else {
            Quadro ack;
            ack.setControleInt(1);
            ack.setSequencia(not this->m);
            ack.setReservado(0);
            inferior->envia(ack);
        }
    }
}

void Arq::envia(Quadro quadro) {
    this->quadroTx = quadro;
    this->mef(quadro, true, false);
}

void Arq::recebe(Quadro quadro) {
    this->mef(quadro, false, false);
}

void Arq::handle() {

}

void Arq::handle_timeout() {
    Quadro quadro;
    this->mef(quadro, true, true);
}
