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
    caravanas.push_back(new Comercio(3, 3,buffer));
    caravanas.push_back(new Militar(5, 5,buffer));

    // Adiciona uma caravana bárbara
    caravanas.push_back(new Barbara(7, 7,buffer));

    // Posiciona caravanas no buffer
    for (auto* caravana : caravanas)
        caravana->moveCaravana(caravana, ' '); // Posiciona no mapa inicial
    for (auto* barbara : barbaras)
        barbara->moveCaravana(barbara, ' ');
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
            caravanas[id]->moveCaravana(caravanas[id], direcao);
        }
        for (auto* caravana : caravanas) {
            if (caravana->isAutonomo() && !caravana->semTripulantes()) {
                caravana->comportamentoAutonomo(); // Já implementado para cada tipo de caravana
            }
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

void Jogo::processarComando(const std::string& comando) {
    if (comando.rfind("prox", 0) == 0) {
        int turnos = 1;
        try {
            if (comando.size() > 5) {
                turnos = std::stoi(comando.substr(5));
            }
        } catch (...) {
            std::cout << "Comando inválido. Uso correto: prox <n>\n";
            return;
        }

        for (int i = 0; i < turnos; ++i) {
            for (auto* caravana : caravanas) {
                if (!caravana->semTripulantes()) {
                    caravana->consumirAgua();
                }
            }
        }
        instantesDecorridos += turnos;
        std::cout << "Avançado " << turnos << " turnos. Total: " << instantesDecorridos << " turnos.\n";
    }
    else if (comando.rfind("comprac", 0) == 0) {
        if (comando.size() < 11) {
            std::cout << "Comando inválido. Uso correto: comprac <Cidade> <Tipo>\n";
            return;
        }

        char cidade = comando[8];
        char tipoCaravana = comando[10];

        Cidade* cidadeAlvo = nullptr;
        for (auto* c : deserto.getCidades()) {
            if (c->getNome()[0] == cidade) {
                cidadeAlvo = c;
                break;
            }
        }

        if (!cidadeAlvo) {
            std::cout << "Cidade não encontrada.\n";
            return;
        }

        if (tipoCaravana != 'C' && tipoCaravana != 'M') {
            std::cout << "Tipo de caravana inválido. Use 'C' para Comércio ou 'M' para Militar.\n";
            return;
        }

        int custo = (tipoCaravana == 'C') ? 200 : 300;
        if (moedasJogador < custo) {
            std::cout << "Você não tem moedas suficientes para comprar esta caravana.\n";
            return;
        }

        Caravana* novaCaravana = (tipoCaravana == 'C')
                                 ? new Comercio(cidadeAlvo->getPosX(), cidadeAlvo->getPosY(), buffer)
                                 : new Militar(cidadeAlvo->getPosX(), cidadeAlvo->getPosY(), buffer);

        if (novaCaravana) {
            caravanas.push_back(novaCaravana);
            moedasJogador -= custo;
            std::cout << "Caravana comprada com sucesso! Moedas restantes: " << moedasJogador << "\n";
        }
    }
    else if (comando.rfind("move", 0) == 0) {
        if (comando.size() < 8) {
            std::cout << "Comando inválido. Uso correto: move <ID> <Direção>\n";
            return;
        }

        int id = comando[5] - '0';
        char direcao = comando[7];

        if (id >= 0 && id < caravanas.size()) {
            if (direcao != 'N' && direcao != 'S' && direcao != 'E' && direcao != 'O') {
                std::cout << "Direção inválida. Use N, S, E ou O.\n";
                return;
            }

            bool sucesso = caravanas[id]->moveCaravana(caravanas[id], direcao);
            if (!sucesso) {
                std::cout << "Movimento inválido.\n";
            }
        } else {
            std::cout << "Caravana inválida.\n";
        }
    }
    else if (comando.rfind("cidade", 0) == 0) { // Exemplo: cidade A
        if (comando.size() < 8) {
            std::cout << "Comando inválido. Uso correto: cidade <C>\n";
            return;
        }

        char nomeCidade = comando[7]; // Nome da cidade
        Cidade* cidadeAlvo = nullptr;

        // Procurar a cidade
        for (auto* c : deserto.getCidades()) {
            if (c->getNome()[0] == nomeCidade) {
                cidadeAlvo = c;
                break;
            }
        }

        if (!cidadeAlvo) {
            std::cout << "Cidade " << nomeCidade << " não encontrada.\n";
            return;
        }

        // Listar caravanas na cidade
        std::cout << "Informações da cidade " << cidadeAlvo->getNome() << ":\n";
        cidadeAlvo->listarCaravanas();
    }
    else if (comando.rfind("compra", 0) == 0) { // Exemplo: compra 1 10
        if (comando.size() < 10) {
            std::cout << "Comando inválido. Uso correto: compra <N> <M>\n";
            return;
        }

        int id = comando[7] - '0';  // ID da caravana
        int quantidade = std::stoi(comando.substr(9));  // Quantidade de mercadoria

        if (id < 0 || id >= caravanas.size()) {
            std::cout << "Caravana inválida.\n";
            return;
        }

        Caravana* caravana = caravanas[id];

        // Verifica se a caravana está numa cidade
        bool naCidade = false;
        for (auto* c : deserto.getCidades()) {
            if (c->getPosX() == caravana->getPosX() && c->getPosY() == caravana->getPosY()) {
                naCidade = true;
                break;
            }
        }

        if (!naCidade) {
            std::cout << "A caravana não está numa cidade para realizar a compra.\n";
            return;
        }

        // Simula o custo e verifica capacidade
        int custo = quantidade * 10; // Exemplo: 10 moedas por unidade
        if (moedasJogador < custo) {
            std::cout << "Moedas insuficientes. Precisa de " << custo << " moedas.\n";
            return;
        }

        if (caravana->getCargaAtual() + quantidade > caravana->getCapacidadeCarga()) {
            std::cout << "Capacidade de carga insuficiente.\n";
            return;
        }

        // Realiza a compra
        caravana->setCargaAtual(caravana->getCargaAtual() + quantidade);
        moedasJogador -= custo;

        std::cout << "Compra realizada com sucesso. Carga atual: " << caravana->getCargaAtual()
                  << ". Moedas restantes: " << moedasJogador << "\n";
    }
    else if (comando.rfind("vende", 0) == 0) { // Exemplo: vende 1
        if (comando.size() < 7) {
            std::cout << "Comando inválido. Uso correto: vende <N>\n";
            return;
        }

        int id = comando[6] - '0'; // ID da caravana

        if (id < 0 || id >= caravanas.size()) {
            std::cout << "Caravana inválida.\n";
            return;
        }

        Caravana* caravana = caravanas[id];

        // Verifica se a caravana está numa cidade
        bool naCidade = false;
        for (auto* c : deserto.getCidades()) {
            if (c->getPosX() == caravana->getPosX() && c->getPosY() == caravana->getPosY()) {
                naCidade = true;
                break;
            }
        }

        if (!naCidade) {
            std::cout << "A caravana não está numa cidade para realizar a venda.\n";
            return;
        }

        // Calcula o total de moedas recebidas
        int totalVendido = caravana->getCargaAtual() * 15; // Exemplo: 15 moedas por unidade
        moedasJogador += totalVendido;

        std::cout << "Venda realizada com sucesso. Lucro: " << totalVendido
                  << ". Moedas totais: " << moedasJogador << "\n";

        caravana->setCargaAtual(0); // Zera a carga da caravana
    }
    else if (comando.rfind("auto", 0) == 0) { // Exemplo: auto 1
        int id = comando[5] - '0';
        if (id < 0 || id >= caravanas.size()) {
            std::cout << "Caravana inválida.\n";
            return;
        }

        caravanas[id]->setAutonomo(true);
        std::cout << "Caravana " << id << " está agora em modo autónomo.\n";
    }
    else if (comando.rfind("stop", 0) == 0) { // Exemplo: stop 1
        int id = comando[5] - '0';
        if (id < 0 || id >= caravanas.size()) {
            std::cout << "Caravana inválida.\n";
            return;
        }

        caravanas[id]->setAutonomo(false);
        std::cout << "Caravana " << id << " está agora em modo manual.\n";
    }
    else if (comando.rfind("areia", 0) == 0) { // Exemplo: areia 5 5 3
        int l, c, r;
        try {
            l = std::stoi(comando.substr(6, comando.find(" ", 6)));
            c = std::stoi(comando.substr(comando.find(" ", 6) + 1, comando.find(" ", comando.find(" ", 6) + 1)));
            r = std::stoi(comando.substr(comando.find_last_of(" ") + 1));
        } catch (...) {
            std::cout << "Comando inválido. Uso correto: areia <l> <c> <r>\n";
            return;
        }

        // Afeta caravanas dentro do raio
        for (auto* caravana : caravanas) {
            int dx = caravana->getPosX() - l;
            int dy = caravana->getPosY() - c;
            if (dx * dx + dy * dy <= r * r) { // Dentro do raio
                caravana->setTripulantes(caravana->getTripulantes() - 5); // Perde 5 tripulantes
                caravana->consumirAgua(); // Consome água extra
                std::cout << "Caravana " << caravana->getSymbol() << " foi afetada pela tempestade de areia!\n";
            }
        }
    }
    else if (comando.rfind("moedas", 0) == 0) { // Exemplo: moedas 200
        int valor;
        try {
            valor = std::stoi(comando.substr(7));
        } catch (...) {
            std::cout << "Comando inválido. Uso correto: moedas <N>\n";
            return;
        }

        moedasJogador += valor;
        std::cout << "Moedas ajustadas. Total atual: " << moedasJogador << "\n";
    }
    else if (comando.rfind("tripul", 0) == 0) { // Exemplo: tripul 1 10
        int id, tripulantes;
        try {
            id = std::stoi(comando.substr(7, comando.find(" ", 7)));
            tripulantes = std::stoi(comando.substr(comando.find(" ", 7) + 1));
        } catch (...) {
            std::cout << "Comando inválido. Uso correto: tripul <N> <T>\n";
            return;
        }

        if (id < 0 || id >= caravanas.size()) {
            std::cout << "Caravana inválida.\n";
            return;
        }

        Caravana* caravana = caravanas[id];

        if (caravana->getTripulantes() + tripulantes > caravana->getMaxTripulantes()) {
            std::cout << "Não é possível adicionar tantos tripulantes. Capacidade máxima excedida.\n";
            return;
        }

        caravana->setTripulantes(caravana->getTripulantes() + tripulantes);
        std::cout << "Tripulantes ajustados. Total atual: " << caravana->getTripulantes() << "\n";
    }

}


