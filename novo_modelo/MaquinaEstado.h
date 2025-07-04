//
// Created by ricardo on 09/06/25.
//

#ifndef AULA_1_MAQUINAESTADO_H
#define AULA_1_MAQUINAESTADO_H

#include <cstdint>
#include <vector>
#include <iostream>
#include <functional>
#include "CRC16.h"

class MaquinaEstado {

#define FLAG 0x7e
#define ESC 0x7d

private:
    enum class Estado:uint8_t  {
        OCIOSO,
        INIT,
        RX,
        ESCAPE
    };
    Estado estadoAtual;
    std::vector<char> dados;
    std::function<void(bool)> callback_timeout;
public:
    MaquinaEstado();
    bool mef(char c, bool timeout);
    void handle_init(char c, bool timeout);
    void handle_ocioso(char c);
    bool handle_rx(char c, bool timeout);
    void handle_escape(char c, bool timeout);
    void set_callback_timeout(std::function<void(bool)> cb);
    std::vector<char> get_dados();
};


#endif //AULA_1_MAQUINAESTADO_H
