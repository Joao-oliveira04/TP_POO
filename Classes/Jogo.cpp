//
// Created by jpbol on 26/12/2024.
//

#include "Jogo.h"
#include <iostream>
#include <cstdlib>

Jogo::Jogo(int linhas, int colunas, int moedasIniciais)
    : buffer(linhas, colunas), deserto(buffer), moedasJogador(moedasIniciais),
      instantesDecorridos(0), combatesVencidos(0), jogoAtivo(true) {
    buffer.limpaBuffer();
    deserto.geraDeserto();
    deserto.geraMontanha();
    deserto.geraCidades(5); // Exemplo: 5 cidades

    // Adiciona caravanas do jogador
    caravanas.push_back(new Comercio(3, 3));
    caravanas.push_back(new Militar(5, 5));

    // Adiciona uma caravana bárbara
    barbaras.push_back(new Barbara(7, 7));

    // Posiciona caravanas no buffer
    for (auto* caravana : caravanas)
        buffer.moveCaravana(caravana, ' '); // Posiciona no mapa inicial
    for (auto* barbara : barbaras)
        buffer.moveCaravana(barbara, ' ');
}

Jogo::~Jogo() {
    // Libera memória das caravanas
    for (auto* caravana : caravanas)
        delete caravana;
    for (auto* barbara : barbaras)
        delete barbara;
}

void Jogo::iniciar() {
    while (jogoAtivo) {
        // Mostra o estado do jogo
        buffer.mostraBuffer();
        std::cout << "Turno " << ++instantesDecorridos << ":\n";

        // Processa o comando do jogador
        std::string comando;
        std::cout << "Insira um comando: ";
        std::cin >> comando;

        if (comando == "terminar") {
            jogoAtivo = false;
            break;
        }

        processarComando(comando);
        verificarCondicoesDeTermino();
    }

    mostrarPontuacaoFinal();
}

void Jogo::processarComando(const std::string& comando) {
    if (comando == "moedas") {
        std::cout << "Você possui " << moedasJogador << " moedas.\n";
    } else if (comando.rfind("move", 0) == 0) { // Exemplo: "move 1 N"
        int id = comando[5] - '0';             // ID da caravana
        char direcao = comando[7];             // Direção
        if (id >= 0 && id < caravanas.size()) {
            buffer.moveCaravana(caravanas[id], direcao);
        }
    }
    // Adiciona outros comandos conforme necessário
}

void Jogo::verificarCondicoesDeTermino() {
    bool temCaravanasAtivas = false;

    for (Caravana* caravana : caravanas) {
        if (!caravana->semTripulantes()) {
            temCaravanasAtivas = true;
            break;
        }
    }

    if (!temCaravanasAtivas && moedasJogador < 100) { // Sem caravanas e sem dinheiro
        std::cout << "Você ficou sem caravanas e dinheiro suficiente para comprar novas!\n";
        jogoAtivo = false;
    }
}

void Jogo::mostrarPontuacaoFinal() {
    std::cout << "\n=== Fim da Simulação ===\n";
    std::cout << "Instantes decorridos: " << instantesDecorridos << "\n";
    std::cout << "Combates vencidos: " << combatesVencidos << "\n";
    std::cout << "Moedas restantes: " << moedasJogador << "\n";
    std::cout << "=========================\n";
}
