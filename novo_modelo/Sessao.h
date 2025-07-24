//
// Created by ricardo on 14/07/25.
//

#ifndef SESSAO_H
#define SESSAO_H
#include "Subcamada.h"
#include <cstdint>
#include <queue>

class Sessao: public Subcamada {
enum class Estado:uint8_t {
    DISC,
    ESPERA,
    CONN,
    HALF1,
    HALF2
};
public:
    Sessao();
    void handle() override;
    void handle_timeout() override;
    void recebe(Quadro quadro) override;
    void envia(Quadro quadro) override;
    void mef(Quadro quadro, bool timeout, bool inferior, bool disc);
    void handleDisc();
    void handleEspera(Quadro quadro, bool timeout);
    void handleHalf1(Quadro quadro, bool timeout);
    void handleHalf2(Quadro quadro, bool timeout);
    void handleConn(Quadro quadro, bool timeout, bool inferior, bool disc);
private:
    Estado estadoAtual;
    Quadro quadroArmazenado;
};



#endif //SESSAO_H
