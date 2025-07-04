//
// Created by ricardo on 09/06/25.
//

#include "MaquinaEstado.h"

MaquinaEstado::MaquinaEstado() {
    estadoAtual = Estado::OCIOSO;
}

bool MaquinaEstado::mef(char c, bool timeout) {
    switch (estadoAtual) {
        case Estado::OCIOSO:
            handle_ocioso(c);
            break;
        case Estado::INIT:
            handle_init(c, timeout);
            break;
        case Estado::RX:
            if (handle_rx(c, timeout)) {
                return true;
            }
            break;
        case Estado::ESCAPE:
            handle_escape(c, timeout);
            break;
    }
    return false;
}

void MaquinaEstado::handle_ocioso(char c) {
    if(c == FLAG) {
        callback_timeout(true);
        dados.clear();
        estadoAtual = Estado::INIT;
    } else {
        callback_timeout(false);
        estadoAtual = Estado::OCIOSO;
    }
}

void MaquinaEstado::handle_init(char c, bool timeout) {
    if (c == FLAG) {
        estadoAtual = Estado::INIT;
    } else if (timeout) {
        std::cout << "timeout" << std::endl;
        callback_timeout(false);
        estadoAtual = Estado::OCIOSO;
    } else if (c == ESC) {
        estadoAtual = Estado::ESCAPE;
    } else {
        dados.push_back(c);
        estadoAtual = Estado::RX;
    }
}

bool MaquinaEstado::handle_rx(char c, bool timeout) {
    if (c == ESC) {
        estadoAtual = Estado::ESCAPE;
    } else if (c == FLAG) {
        callback_timeout(false);
        auto checker = make_crc16(dados);
        estadoAtual = Estado::OCIOSO;
        if (checker.check()) {
            return true;
        }
    } else if (timeout) {
        std::cout << "timeout" << std::endl;
        callback_timeout(false);
        estadoAtual = Estado::OCIOSO;
    } else {
        dados.push_back(c);
        estadoAtual = Estado::RX;
    }
    return false;
}

void MaquinaEstado::handle_escape(char c, bool timeout) {
    if (timeout || c == ESC || c == FLAG) {
        if (timeout) {
            std::cout << "timeout" << std::endl;
        }
        callback_timeout(false);
        estadoAtual = Estado::OCIOSO;
    } else {
        dados.push_back(c ^ 0x20);
        estadoAtual = Estado::RX;
    }
}

std::vector<char> MaquinaEstado::get_dados() {
    return dados;
}

void MaquinaEstado::set_callback_timeout(std::function<void(bool)> func) {
    callback_timeout = func;
}