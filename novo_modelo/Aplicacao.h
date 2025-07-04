//
// Created by ricardo on 16/06/25.
//

#ifndef NOVO_MODELO_APLICACAO_H
#define NOVO_MODELO_APLICACAO_H

#include "Subcamada.h"
#include <string>
#include <iostream>
#include "Serial.h"
#include <fstream>
#include "Quadro.h"

class Aplicacao: public Subcamada{
public:
    Aplicacao();
    void handle() override;
    void handle_timeout() override;
    void envia(Quadro quadro) override;
    void recebe(Quadro quadro) override;
};


#endif //NOVO_MODELO_APLICACAO_H
