//
// Created by ricardo on 16/06/25.
//

#include "Subcamada.h"

Subcamada::Subcamada(int fd, long timeout): Callback(fd, timeout){
    inferior = nullptr;
    superior = nullptr;
}

void Subcamada::conecta(Subcamada * acima) {
    if (acima == nullptr) throw "camada acima nao pode ser nullptr";
    superior = acima;
    acima->inferior = this;
}


