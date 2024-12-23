//
// Created by david on 14/11/2024.
//

#include "Cidades.h"
#include <iostream>
#include <bits/stdc++.h>
Cidade::Cidade(std::string nome, int x, int y, Buffer& buf)
        : nome(nome), posX(x), posY(y), buffer(buf) {
    if (isAccessible()) {
        buffer.setChar(x, y, nome[0]); // Representa a cidade com a primeira letra do nome
    } else {
        throw std::runtime_error("Posição da cidade não é acessível");
    }
}

std::string Cidade::getNome() const {
    return nome;
}

int Cidade::getPosX() const {
    return posX;
}

int Cidade::getPosY() const {
    return posY;
}

void Cidade::entraCaravana(Caravana* caravana) {
    caravanas.push_back(caravana);
    buffer.setChar(caravana->getPosX(), caravana->getPosY(), '.'); // Remove caravana do mapa
    std::cout << "Caravana entrou na cidade " << nome << "\n";
}

void Cidade::saiCaravana(Caravana* caravana) {
    auto it = std::find(caravanas.begin(), caravanas.end(), caravana);
    if (it != caravanas.end()) {
        caravanas.erase(it);
        std::cout << "Caravana saiu da cidade " << nome << "\n";
    }
}

void Cidade::listarCaravanas() const {
    std::cout << "Caravanas na cidade " << nome << ":\n";
    for (const auto& caravana : caravanas) {
        std::cout << " - Caravana " << caravana->getSymbol() << "\n";
    }
}

bool Cidade::isAccessible() const {
    // Verifica se pelo menos um lado da cidade é acessível (deserto)
    return (buffer.getChar(posX - 1, posY) == '.' || buffer.getChar(posX + 1, posY) == '.' ||
            buffer.getChar(posX, posY - 1) == '.' || buffer.getChar(posX, posY + 1) == '.');
}