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

// Gera os tais itens
void Deserto::geraItens(int numItens)
{
    srand(time(NULL)); // Inicializa a semente de números aleatórios

    for ( int i = 0; i < numItens; ++i)
    {
        int posX, posY;

        // Gera posicoes aleatorias ate encontrar uma vazia

        do
        {
            posX = rand() % buffer.getNumLinhas();
            posY = rand() % buffer.getNumColunas();
        } while (buffer.getChar(posX, posY) != '.');

        // Sorteia o tipo de item
        int tipo = rand() % 5; //5 tipos de itens, REVER
        Itens* novoItens = nullptr;

        switch (tipo)
        {
            case 0: novoItens = new CaixaDePandora(posX, posY); break;
            case 1: novoItens = new ArcaDoTesouro(posX, posY); break;
            case 2: novoItens = new Jaula(posX, posY); break;
            case 3: novoItens = new Mina(posX, posY); break;
            case 4: novoItens = new Surpresa(posX, posY); break;
        }

        if (novoItens)
        {
            itens.push_back(novoItens);
            buffer.setChar(posX, posY, '*'); // Representacao no mapa
        }
    }
}

void Deserto::verificaItens(Caravana* caravana) {
    for (auto it = itens.begin(); it != itens.end(); ) {
        if ((*it)->getPosX() == caravana->getPosX() && (*it)->getPosY() == caravana->getPosY()) {
            (*it)->aplicarEfeito(caravana);
            delete *it; // Remove o item após ser apanhado
            it = itens.erase(it);
        } else {
            ++it;
        }
    }
}