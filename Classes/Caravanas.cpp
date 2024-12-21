
#include "Caravanas.h"
#include "Buffer.h"
#include <iostream>
#include <cstdlib> // Para rand()
#include <algorithm> // Para std::max

// Implementação da classe base Caravana
Caravana::Caravana(std::string t, int x, int y, int trip, int capAgua, int capCarga, int movimentos)
        : tipo(t), posX(x), posY(y), tripulantes(trip), capacidadeAgua(capAgua),
          aguaAtual(capAgua), capacidadeCarga(capCarga), cargaAtual(0),
          movimentosPorTurno(movimentos), instantesSemTrip(0), direcaoAtual('N') {}

Caravana::~Caravana() {}

void Caravana::mover(char direcao) {
    direcaoAtual = direcao;
    switch (direcao) {
        case 'N': posX--; break;
        case 'S': posX++; break;
        case 'O': posY--; break;
        case 'E': posY++; break;
    }
    std::cout << tipo << " moveu-se para (" << posX << ", " << posY << ").\n";
}

void Caravana::consumirAgua() {
    if (tripulantes > 0) {
        int consumo = (tripulantes > (capacidadeAgua / 4)) ? 2 : 1;
        aguaAtual = std::max(aguaAtual - consumo, 0);
        std::cout << tipo << " consumiu " << consumo << " litros de água. Restante: " << aguaAtual << " litros.\n";
    }
}

bool Caravana::semAgua() const { return aguaAtual <= 0; }

void Caravana::setTripulantes(int i){
    if(i<0){
        tripulantes = 0;
    } else{
        tripulantes = i;
    }
}

bool Caravana::semTripulantes() const { return tripulantes == 0; }

void Caravana::setMoedasJogador(int i) {
    if (i < 0) {
        tripulantes = 0;
    } else {
        tripulantes = i;
    }
}

bool Caravana::moveCaravana(Caravana* caravana, char direcao, Buffer buffer) {
    int x = caravana->posX;
    int y = caravana->posY;
    int novoX = x;
    int novoY = y;

    switch (direcao) {
        case 'N': novoX--; break;
        case 'S': novoX++; break;
        case 'O': novoY--; break;
        case 'E': novoY++; break;
        default: return false;
    }

    // Verifica se o movimento é válido
    if (novoX >= 0 && novoX < buffer.getNumLinhas() && novoY >= 0 && novoY < buffer.getNumColunas() && buffer.getChar(novoX,novoY) != '+') {
        buffer.setChar(x,y,'.'); // Limpa posição atual
        buffer.setChar(x,y,caravana->getSymbol()); // Atualiza posição
        caravana->setPos(novoX, novoY); // Atualiza coordenadas da caravana
        return true;
    }

    return false;
}

void Caravana::destruir() {
    tripulantes = 0;
    aguaAtual = 0;
    cargaAtual = 0;
    std::cout << tipo << " foi destruída!\n";
}

// Implementação da classe Comercio
Comercio::Comercio(int x, int y)
        : Caravana("Comércio", x, y, 20, 200, 40, 2) {}

void Comercio::comportamentoAutonomo() {
    std::cout << "Caravana de Comércio procura itens ou proteção próxima.\n";
    // Lógica adicional pode ser implementada aqui
}

void Comercio::moverSemTripulantes() {
    posX += rand() % 3 - 1; // Movimento aleatório
    posY += rand() % 3 - 1;
    std::cout << "Caravana de Comércio sem tripulantes move-se aleatoriamente.\n";
}

// Implementação da classe Militar
Militar::Militar(int x, int y)
        : Caravana("Militar", x, y, 40, 400, 5, 3) {}

void Militar::comportamentoAutonomo() {
    std::cout << "Caravana Militar verifica por caravanas bárbaras próximas.\n";
    // Lógica adicional pode ser implementada aqui
}

void Militar::moverSemTripulantes() {
    mover(direcaoAtual); // Continua na última direção
    std::cout << "Caravana Militar sem tripulantes move-se na última direção.\n";
}

// Implementação da classe Barbara
Barbara::Barbara(int x, int y)
        : Caravana("Bárbara", x, y, 30, 100, 10, 2) {}

void Barbara::comportamentoAutonomo() {
    std::cout << "Caravana Bárbara procura atacar outras caravanas.\n";
    // Lógica adicional pode ser implementada aqui
}

char Caravana::getSymbol() const {
    if (tipo == "Comércio" || tipo == "Militar") return '1';
    if (tipo == "Bárbara") return '!';
    return '?';
}

int Caravana::getPosX() const { return posX; }
int Caravana::getPosY() const { return posY; }
void Caravana::setPos(int x, int y) {
    posX = x;
    posY = y;
}

