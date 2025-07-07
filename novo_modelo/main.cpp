#include <iostream>
#include "poller.h"
#include "Enquadramento.h"
#include "Aplicacao.h"
#include "Serial.h"
#include "Arq.h"

int main (int argc, char * argv[]) {
    if (argc != 2) {
        std::cout << "uso: <porta serial>" << std::endl;
        return 0;
    }

    Serial rf(argv[1]);
    Enquadramento enquadramento(rf, 5000);
    Aplicacao aplicacao;
    Arq arq;
    Poller sched;

    enquadramento.conecta(&arq);
    arq.conecta(&aplicacao);

    sched.adiciona(&enquadramento);
    sched.adiciona(&aplicacao);
    sched.despache();
}
