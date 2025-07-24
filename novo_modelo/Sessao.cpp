//
// Created by ricardo on 14/07/25.
//

#include "Sessao.h"
#include <iostream>

Sessao::Sessao(): Subcamada(30000) {
    estadoAtual = Estado::DISC;
    disable_timeout();
}

void Sessao::mef(Quadro quadro, bool timeout, bool inferior, bool disc) {
    switch (estadoAtual) {
        case Estado::DISC:
            handleDisc();
            break;
        case Estado::CONN:
            handleConn(quadro, timeout, inferior, disc);
            break;
        case Estado::HALF1:
            handleHalf1(quadro, timeout);
            break;
        case Estado::HALF2:
            handleHalf2(quadro, timeout);
            break;
        case Estado::ESPERA:
            handleEspera(quadro, timeout);
            break;
    }
}

void Sessao::handleDisc() {
    std::cout << "sessao, handleDisc" << std::endl;
    if (superior->is_enabled()) {
        superior->disable();
    }
    Quadro cr;
    cr.setSessao(0,0,1);
    cr.setIdSessao(0);
    cr.setIdProto(0);
    inferior->envia(cr);
    enable_timeout();
    estadoAtual = Estado::ESPERA;
}

void Sessao::handleEspera(Quadro quadro, bool timeout) {
    std::cout << "sessao, handleEspera" << std::endl;
    if (timeout) {
        disable_timeout();
        estadoAtual = Estado::DISC;
    } else {
        if (quadro.getIsControle()) {
            std::vector<int> tipoControle = quadro.getTipoControle();
            if (tipoControle[0] == 1 && tipoControle[1] == 0) {
                std::cout << "cc recebido, handle espera" << std::endl;
                Quadro cc;
                cc.setSessao(1,0,1);
                cc.setIdSessao(0);
                cc.setIdProto(0);
                inferior->envia(cc);
                inferior->envia(quadroArmazenado);
                if (!superior->is_enabled()) {
                    superior->enable();
                }
                estadoAtual = Estado::CONN;
            }
        }
    }
}

void Sessao::handleHalf1(Quadro quadro, bool timeout) {
    std::cout << "sessao, handleHalf1" << std::endl;
    if (quadro.getIsControle()) {
        std::vector<int> tipoControle = quadro.getTipoControle();
        if (tipoControle[0] == 0 && tipoControle[1] == 1) {
            std::cout << "desconectado" << std::endl;
            Quadro dc;
            dc.setSessao(1,1,1);
            dc.setIdSessao(0);
            dc.setIdProto(0);
            inferior->envia(dc);
            disable_timeout();
            estadoAtual = Estado::DISC;
        } else if (timeout) {
            disable_timeout();
            estadoAtual = Estado::DISC;
        }
    } else {
        superior->recebe(quadro);
    }
}

void Sessao::handleHalf2(Quadro quadro, bool timeout) {
    std::cout << "sessao, handleHalf2" << std::endl;
    if (quadro.getIsControle()) {
        std::vector<int> tipoControle = quadro.getTipoControle();
        if ((tipoControle[0] == 1 && tipoControle[1] == 1) || timeout) {
            disable_timeout();
            estadoAtual = Estado::DISC;
            std::cout << "desconectado" << std::endl;
        }
    }
}

void Sessao::handleConn(Quadro quadro, bool timeout, bool inferior, bool disc) {
    std::cout << "sessao, handleConn" << std::endl;
    if (disc) {
        Quadro dr;
        dr.setSessao(0,1,1);
        dr.setIdSessao(0);
        dr.setIdProto(0);
        this->inferior->envia(dr);
        estadoAtual = Estado::HALF1;
    } else {
        if (quadro.getIsControle()) {
            std::vector<int> tipoControle = quadro.getTipoControle();
            if (tipoControle[0] == 0 && tipoControle[1] == 1) {
                Quadro dr;
                dr.setSessao(0,1,1);
                dr.setIdSessao(0);
                dr.setIdProto(0);
                this->inferior->envia(dr);
                estadoAtual = Estado::HALF2;
            }
        } else if (!quadro.getIsControle()) {
            if (inferior) {
                superior->recebe(quadro);
            } else {
                this->inferior->envia(quadro);
            }
        } else if (timeout) {
            Quadro ka;
            ka.setSessao(1,1,0);
            ka.setIdSessao(0);
            ka.setIdProto(0);
            this->inferior->envia(ka);
        }
    }

}

void Sessao::recebe(Quadro quadro) {
    std::cout << "sessao, recebe" << std::endl;
    this->mef(quadro, false, true, false);
}

void Sessao::envia(Quadro quadro) {
    std::cout << "sessao, envia" << std::endl;
    if (estadoAtual == Estado::DISC) {
        quadroArmazenado = quadro;
    }
    std::vector<char> conteudo = quadro.getDados();
    if (conteudo.size() == 1 && conteudo[0] == '0') {
        this->mef(quadro, false, false, true);
    } else {
        this->mef(quadro, false, false, false);
    }
}

void Sessao::handle() {

}

void Sessao::handle_timeout() {
    Quadro quadro;
    this->mef(quadro, true, false, false);
}



