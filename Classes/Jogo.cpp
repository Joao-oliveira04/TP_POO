//
// Created by jpbol on 26/12/2024.
//

#include "Jogo.h"
#include <iostream>
#include <cstdlib>
#include "Caravanas.h"
#include "Cidades.h"
Jogo::Jogo(int linhas, int colunas, int moedasIniciais)
    : buffer(linhas, colunas), deserto(buffer), moedasJogador(moedasIniciais),
      instantesDecorridos(0), combatesVencidos(0), jogoAtivo(true) {
    buffer.limpaBuffer();
    deserto.geraDeserto();
    deserto.geraMontanha();
    deserto.geraCidades(5);

    // Adiciona caravanas do jogador
    caravanas.push_back(new Comercio(0, 0,buffer));
    caravanas.push_back(new Militar(0, 0,buffer));
    // Posiciona caravanas no buffer
    for (auto* caravana : caravanas)
        caravana->encontrarPosicaoValida();
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
        if(instantesDecorridos % 40 == 0) {
            deserto.geraItens(1);
            // Adiciona uma caravana bárbara
            barbaras.push_back(new Barbara(0, 0, buffer));
            nBarbaras++;
            barbaras[nBarbaras - 1]->encontrarPosicaoValida();
        }
        // Movimento autônomo das caravanas bárbaras
        for (auto* barbara : barbaras) {
            barbara->comportamentoAutonomo(caravanas, buffer);
        }

        // Mostra o estado do jogo
        buffer.mostraBuffer();
        std::cout << "Turno " << ++instantesDecorridos << ":\n";
        for (auto* barbara : barbaras) {
            Caravana* caravanaProxima = barbara->getCaravanaClose(caravanas);
            if (caravanaProxima != nullptr) {
                std::cout << "Combate entre uma caravana Bárbara e a caravana "<<caravanaProxima->getSymbol()<<"!\n";
                barbara->combate(caravanaProxima);
            }
            else{
                barbara->comportamentoAutonomo(caravanas, buffer);
            }
        }
        // Processa o comando do jogador
        std::string comando;
        std::cout << "Insira um comando: ";
        std::getline(std::cin, comando); // Lê a linha inteira de entrada

        if (comando == "terminar") {
            jogoAtivo = false;
            break;
        }

        processarComando(comando);
        verificarCondicoesDeTermino();
    }

    mostrarPontuacaoFinal();
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
            for (auto* barbara : barbaras) {
                Caravana *a = barbara->getCaravanaClose(caravanas);
                if (a != nullptr) {
                    std::cout << "Combate entre Bárbara e outra caravana!\n";
                    barbara->combate(a);
                }
                else{
                    barbara->comportamentoAutonomo(caravanas, buffer);
                }
            }
            for (auto* caravana : caravanas) {
                if (!caravana->semTripulantes()) {
                    if(caravana->getTipo() == "Militar"){
                        caravana->consumirAgua(1);
                    }
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
        if(!cidadeAlvo->getnCaravanas()){
            std::cout << "Nenhuma caravana na cidade\n";
            return;
        }

        if (tipoCaravana != 'C' && tipoCaravana != 'M') {
            std::cout << "Tipo de caravana inválido. Use 'C' para Comércio ou 'M' para Militar.\n";
            return;
        }

        int custo = (tipoCaravana == 'C') ? 100 : 200;
        if (moedasJogador < custo) {
            std::cout << "Você não tem moedas suficientes para comprar esta caravana.\n";
            return;
        }

        Caravana* novaCaravana = (tipoCaravana == 'C')
                                 ? static_cast<Caravana*>(new Comercio(cidadeAlvo->getPosX(), cidadeAlvo->getPosY(), buffer))
                                 : static_cast<Caravana*>(new Militar(cidadeAlvo->getPosX(), cidadeAlvo->getPosY(), buffer));
        if (novaCaravana) {
            cidadeAlvo->entraCaravana(novaCaravana);
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
        id--;
        if (id >= 0 && id < caravanas.size()) {
            if (caravanas[id]->isAutonomo()) {
                std::cout<<"Caravana é autônoma.\n";
                return;
            }
            if (direcao != 'N' && direcao != 'S' && direcao != 'E' && direcao != 'O') {
                std::cout << "Direção inválida. Use N, S, E ou O.\n";
                return;
            }

            bool sucesso = caravanas[id]->moveCaravana(caravanas[id], direcao,buffer);
            if (!sucesso) {
                std::cout << "Movimento inválido.\n";
            } else {
                std::cout << "Caravana " << caravanas[id]->getTipo() << " moveu-se para " << direcao << ".\n";
            }
        } else {
            std::cout << "Caravana inválida.\n";
        }
    }
    else if (comando.rfind("cidade", 0) == 0) { // Exemplo: cidade A
        if (comando.size() < 8) {
            std::cout << "Comando inválido. Uso correto: cidade <C>"<<endl;
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
            std::cout << "Cidade " << nomeCidade << " não encontrada."<< endl;
            return;
        }

        // Listar caravanas na cidade
        std::cout << "Informações da cidade " << cidadeAlvo->getNome() << ":"<< endl;
        cidadeAlvo->listarCaravanas();
    }
    else if (comando.rfind("comprat", 0) == 0) {
        if (comando.size() < 9) {
            std::cout << "Comando inválido. Uso correto: comprat <ID> <N>"<<endl;
            return;
        }

        int id = comando[7] - '0'; // ID da caravana
        id--;
        int tripulantes = std::stoi(comando.substr(9)); // Quantidade de tripulantes

        if (id < 0 || id >= caravanas.size()) {
            std::cout << "Caravana inválida."<<endl;
            return;
        }

        Caravana* caravana = caravanas[id];
        if (caravana->getTipo() != "Comercio") {
            std::cout << "Caravana não é do tipo Comercio."<<endl;
            return;
        }

        // Verifica se a caravana está numa cidade
        bool naCidade = false;
        for (auto* c : deserto.getCidades()) {
            if (c->getPosX() == caravana->getPosX() && c->getPosY() == caravana->getPosY()) {
                naCidade = true;
                break;
            }
        }

        if (!naCidade) {
            std::cout << "A caravana não está numa cidade para comprar tripulantes."<<endl;
            return;
        }

        // Simula o custo e verifica capacidade
        int custo = tripulantes * 1; // Exemplo: 1 moeda por tripulante
        if (moedasJogador < custo) {
            std::cout << "Moedas insuficientes. Precisa de " << custo << " moedas."<<endl;
            return;
        }

        if (caravana->getTripulantes() + tripulantes > caravana->getMaxTripulantes()) {
            std::cout << "Capacidade de tripulantes excedida."<<endl;
            return;
        }

        // Realiza a compra
        caravana->setTripulantes(caravana->getTripulantes() + tripulantes);
        moedasJogador -= custo;

        std::cout << "Compra realizada com sucesso. Tripulantes atuais: " << caravana->getTripulantes()
                  << ". Moedas restantes: ";
    }
    else if (comando.rfind("compra", 0) == 0) { // Exemplo: compra 1 10
        if (comando.size() < 10) {
            std::cout << "Comando inválido. Uso correto: compra <id> <M>"<<endl;
            return;
        }

        int id = comando[7] - '0';  // ID da caravana
        id--;
        int quantidade = std::stoi(comando.substr(9));  // Quantidade de mercadoria

        if (id < 0 || id >= caravanas.size()) {
            std::cout << "Caravana inválida."<<endl;
            return;
        }

        Caravana* caravana = caravanas[id];
        if(caravana->getTipo() != "Comercio"){
            std::cout << "Caravana não é do tipo Comercio."<<endl;
            return;
        }

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
        int custo = quantidade; // Exemplo: 1 moedas por unidade
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
        if (comando.size() < 10) {
            std::cout << "Comando inválido. Uso correto: vende <id> <N>\n";
            return;
        }

        int id = comando[6] - '0'; // ID da caravana
        id--;
        int quantidade = std::stoi(comando.substr(8)); // Quantidade de mercadoria
        if (id < 0 || id >= caravanas.size()) {
            std::cout << "Caravana inválida.\n";
            return;
        }

        Caravana* caravana = caravanas[id];

        if(caravana->getTipo() != "Comercio"){
            std::cout << "Caravana não é do tipo Comercio."<<endl;
            return;
        }
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
        int totalVendido = quantidade * 2; // Exemplo: 15 moedas por unidade
        if (quantidade > caravana->getCargaAtual()) {
            std::cout << "Quantidade de mercadoria insuficiente.\n";
            return;
        }
        else{
            moedasJogador += totalVendido;

            std::cout << "Venda realizada com sucesso. Lucro: " << totalVendido
                      << ". Moedas totais: " << moedasJogador << "\n";

            caravana->setCargaAtual(caravana->getCargaAtual()-totalVendido); // Zera a carga da caravana
        }
    }
    else if (comando.rfind("auto", 0) == 0) { // Exemplo: auto 1
        int id = comando[5] - '0';
        id--;
        if (id < 0 || id >= caravanas.size()) {
            std::cout << "Caravana inválida.\n";
            return;
        }

        caravanas[id]->setAutonomo(true);
        std::cout << "Caravana " << id << " está agora em modo autónomo.\n";
    }
    else if (comando.rfind("stop", 0) == 0) { // Exemplo: stop 1
        int id = comando[5] - '0';
        id--;
        if (id < 0 || id >= caravanas.size()) {
            std::cout << "Caravana inválida.\n";
            return;
        }

        caravanas[id]->setAutonomo(false);
        std::cout << "Caravana " << id << " está agora em modo manual.\n";
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


