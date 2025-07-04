//
// Created by ricardo on 16/06/25.
//

#include "Aplicacao.h"

Aplicacao::Aplicacao(): Subcamada(0,0) {
    disable_timeout();
}

void Aplicacao::recebe(Quadro quadro) {
    //parte 1, escrever terminal
    for (auto c: dados) {
        std::cout << c;
    }
    std::cout << std::endl;

    //parte 2, escrever arquivo
//    std::ofstream arquivo;
//    arquivo.open("receptor.txt", std::ios::binary);
//
//    if (!arquivo.is_open()) {
//        std::cerr << "Erro ao abrir arquivo recepcao" << std::endl;
//        return;
//    }
//
//    for (auto c : dados) {
//        arquivo << c;
//    }
//
//    arquivo.close();
}

void Aplicacao::envia(Quadro quadro) {
}

void Aplicacao::handle() {
    // parte 1, lendo texto do teclado
    std::string linha;
    std::getline(std::cin, linha);
    Quadro quadro;
    quadro.setReservado(0);
    quadro.setIdProto(0);
    std::vector<char> buffer (linha.begin(), linha.end());
    quadro.setDados(buffer);
    inferior->envia(quadro);

    //parte 2, lendo arquivo
//    std::string nome_arquivo;
//    std::getline(std::cin, nome_arquivo);
//
//    std::ifstream arquivo;
//    arquivo.open(nome_arquivo, std::ios::binary);
//
//    if (!arquivo.is_open()) {
//        std::cerr << "Erro ao abrir arquivo" << std::endl;
//        return;
//    }
//
//    std::list<char> conteudo_arquivo;
//
//    std::string linha;
//    auto pos = conteudo_arquivo.begin();
//    while (std::getline(arquivo, linha)) {
//        //posicao, comeco, fim
//        conteudo_arquivo.insert(pos, linha.begin(), linha.end());
//        conteudo_arquivo.push_back('\n');
//        pos = conteudo_arquivo.end();
//    }
//
//    std::vector<char> buffer(conteudo_arquivo.begin(), conteudo_arquivo.end());
//    inferior->envia(buffer);
//    arquivo.close();
}

void Aplicacao::handle_timeout() {

}