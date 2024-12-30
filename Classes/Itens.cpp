#include "Itens.h"
#include "Caravanas.h"
#include "Jogo.h"

void CaixaDePandora::aplicarEfeito(Caravana* caravana) {
    if (caravana) {
        int perda = caravana->getTripulantes() * 0.2; // 20% da tripulação
        caravana->setTripulantes(caravana->getTripulantes() - perda);
        std::cout << "Caixa de Pandora: " << perda << " tripulantes mortos!\n";
    }
}

void ArcaDoTesouro::aplicarEfeito(Caravana* caravana) {
    if (caravana) {
        int moedasAtuais = caravana->getMoedasJogador();
        int incremento = moedasAtuais * 0.1;
        caravana->setMoedasJogador(moedasAtuais + incremento);
        std::cout << "Arca do Tesouro: Adicionou " << incremento
                  << " moedas ao jogador! Total: " << caravana->getMoedasJogador() << " moedas.\n";
    }
}

void Jaula::aplicarEfeito(Caravana* caravana) {
    if (caravana) {
        int capacidadeLivre = caravana->getMaxTripulantes() - caravana->getTripulantes();
        int aumento = std::min(5, capacidadeLivre);
        caravana->setTripulantes(caravana->getTripulantes() + aumento);
        std::cout << "Jaula: Libertou prisioneiros! Tripulantes aumentados em " << aumento << "!\n";
    }
}

void Mina::aplicarEfeito(Caravana* caravana) {
    if (caravana) {
        caravana->destruir();
        std::cout << "Mina: Caravana destruída!\n";
    }
}

void Surpresa::aplicarEfeito(Caravana* caravana) {
    if (caravana) {
        int novaPosX = rand() % 10;
        int novaPosY = rand() % 10;
        caravana->setPos(novaPosX, novaPosY);
        std::cout << "Surpresa: Caravana teleporta para (" << novaPosX << ", " << novaPosY << ")!\n";
    }
}
