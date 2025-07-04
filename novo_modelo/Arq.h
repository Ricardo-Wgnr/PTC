//
// Created by ricardo on 30/06/25.
//

#ifndef NOVO_MODELO_ARQ_H
#define NOVO_MODELO_ARQ_H

#include <cstdint>
#include "Subcamada.h"

class Arq: public Subcamada {
enum class Estado:uint8_t {
    Ocioso,
    Espera
};
private:
    Estado estadoAtual;
    int n;
    int m;
public:
    Arq();
    void mef(Quadro quadro, bool tx);
    void handleOcioso(Quadro quadro, bool tx);
    void handleEspera(Quadro quadro, bool tx);
    void handle_timeout() override;
    void handle() override;
    void envia(Quadro quadro) override;
    void recebe(Quadro quadro) override;
};


#endif //NOVO_MODELO_ARQ_H
