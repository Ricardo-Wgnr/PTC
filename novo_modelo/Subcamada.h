//
// Created by ricardo on 16/06/25.
//

#ifndef NOVO_MODELO_SUBCAMADA_H
#define NOVO_MODELO_SUBCAMADA_H

#include "poller.h"
#include <vector>
#include "Quadro.h"

class Subcamada: public Callback {
public:
    Subcamada(int fd, long timeout);
    Subcamada(long timeout);
    virtual void envia(Quadro quadro) = 0;
    virtual void recebe(Quadro quadro) = 0;
    void conecta(Subcamada * acima);
protected:
    Subcamada * inferior;
    Subcamada * superior;
};


#endif //NOVO_MODELO_SUBCAMADA_H
