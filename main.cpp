#include "Classes\buffer.h"
#include "Classes\Caravanas.h"
#include "Classes\Deserto.h"
#include <iostream>
#include <ctime>

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Cria o tabuleiro
    Buffer buffer(10, 30);
    buffer.limpaBuffer();

    // Cria o deserto e gera elementos
    Deserto deserto(buffer);
    deserto.geraDeserto();
    deserto.geraMontanha();
    deserto.geraCidades(5);
    deserto.geraItens(5); // Por exemplo 5 itens
    // verificar itens apos o movimentp das caransbas
    deserto.verificaItens(&comercio);
    deserto.verificaItens(&militar);
    deserto.verificaItens(&barbara);

    // Cria caravanas
    Comercio comercio(3, 3);
    Militar militar(5, 5);
    Barbara barbara(7, 7);

    // Posiciona caravanas no tabuleiro
    buffer.moveCaravana(&comercio, 'N'); // Mover para iniciar no tabuleiro
    buffer.moveCaravana(&militar, 'S');
    buffer.moveCaravana(&barbara, 'E');

    // Simula movimentos
    for (int i = 0; i < 5; ++i) {
        buffer.mostraBuffer();
        std::cout << "Turno " << i + 1 << "\n";

        buffer.moveCaravana(&comercio, 'E'); // Comércio move-se para leste
        buffer.moveCaravana(&militar, 'N');  // Militar move-se para norte
        buffer.moveCaravana(&barbara, 'O');  // Bárbara move-se para oeste

        std::cout << "\n";
    }

    return 0;
}
