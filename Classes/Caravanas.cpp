
#include "Caravanas.h"
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

bool Caravana::semTripulantes() const { return tripulantes == 0; }

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
