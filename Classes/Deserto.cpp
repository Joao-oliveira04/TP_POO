//
// Created by david on 14/11/2024.
//

#include "Deserto.h"
// Construtor que recebe uma referência ao buffer
Deserto::Deserto(Buffer& buf) : buffer(buf) {}

void Deserto::geraDeserto() {
    for (int i = 0; i < buffer.getNumLinhas(); ++i) {
        for (int j = 0; j < buffer.getNumColunas(); ++j) {
            buffer.setChar(i,j,'.');
        }
    }
}

// Gera montanhas no tabuleiro
void Deserto::geraMontanha() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    int numLinhas = buffer.getNumLinhas();
    int numColunas = buffer.getNumColunas();

    int larguraMontanha, alturaMontanha;
    int posicaoInicioX, posicaoInicioY;

    // Gera múltiplas montanhas (neste exemplo, 3 montanhas aleatórias)
    for (int montanha = 0; montanha < 3; ++montanha) {
        larguraMontanha = rand() % 4 + 2;  // Largura entre 2 e 5 colunas
        alturaMontanha = rand() % 3 + 2;   // Altura entre 2 e 4 linhas

        posicaoInicioX = rand() % (numLinhas - alturaMontanha);
        posicaoInicioY = rand() % (numColunas - larguraMontanha);

        // Preenche o buffer com a montanha ('+')
        for (int i = 0; i < alturaMontanha; ++i) {
            for (int j = 0; j < larguraMontanha; ++j) {
                buffer.setChar(posicaoInicioX + i, posicaoInicioY + j, '+');
            }
        }
    }
}

// Gera cidades no tabuleiro
void Deserto::geraCidades(int numCidades) {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    char cidade = 'a'; // Letra inicial para representar as cidades
    int posicaoX, posicaoY;

    for (int i = 0; i < numCidades; ++i) {
        do {
                posicaoX = rand() % buffer.getNumLinhas();
                posicaoY = rand() % buffer.getNumColunas();
        } while (buffer.getChar(posicaoX, posicaoY) != '.' && (buffer.getChar(posicaoX + 1, posicaoY + 1) == '.' ||
                 buffer.getChar(posicaoX - 1, posicaoY + 1) == '.' ||
                 buffer.getChar(posicaoX + 1, posicaoY - 1) == '.' ||
                 buffer.getChar(posicaoX - 1, posicaoY - 1) == '.'));  // Garante posição vazia

        buffer.setChar(posicaoX, posicaoY, cidade);
        // Incrementa a letra da cidade ('a' -> 'b' -> 'c' ...)
        if (cidade < 'z') {
            ++cidade;
        } else {
            cidade = 'a';
        }
    }
}