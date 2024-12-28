//
// Created by jpbol on 26/12/2024.
//

#ifndef JOGO_H
#define JOGO_H

#include <vector>
#include <string>
#include "Buffer.h"
#include "Caravanas.h"
#include "Deserto.h"

class Jogo {
private:
    Buffer buffer;   // representacao do mapa
    Deserto deserto;   // classe para manipular o deserto
    std::vector<Caravana*> caravanas;  // caravanas do jogador
    std::vector<Barbara*> barbaras;  // caravana bárbaras
    int moedasJogador;   // moedas jogador
    int instantesDecorridos;  // contador de instantes
    int combatesVencidos; // contador de combates
    bool jogoAtivo = true;  // estado do jogo

    // metodos auxiliares

    void verificarCondicoesDeTermino();
    void mostrarPontuacaoFinal();
    void processarComando(const std::string& comando);


public:
    Jogo(int linhas, int colunas, int moedasIniciais);
    ~Jogo();

    void iniciar(); // iniciar a simulacao
    std::vector<Cidade*> getCidades() const { return deserto.getCidades(); }

};



#endif //JOGO_H
