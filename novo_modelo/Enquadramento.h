//
// Created by ricardo on 16/06/25.
//

#ifndef NOVO_MODELO_ENQUADRAMENTO_H
#define NOVO_MODELO_ENQUADRAMENTO_H

#include "Subcamada.h"
#include "Serial.h"
#include <vector>
#include "MaquinaEstado.h"
#include "CRC16.h"
#define FLAG 0x7e
#define ESC 0x7d

class Enquadramento: public Subcamada {
public:
    Enquadramento(Serial & rf, long timeout);
    void handle() override;
    void handle_timeout() override;
    void envia(Quadro quadro) override;
    void recebe(Quadro quadro) override;
    void set_en_timeout(bool en);
private:
    Serial & rf;
    MaquinaEstado mef;
};


#endif //NOVO_MODELO_ENQUADRAMENTO_H
