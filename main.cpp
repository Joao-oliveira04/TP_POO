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

    // Cria caravanas
    Comercio comercio(3, 3);
    Militar militar(5, 5);
    Barbara barbara(7, 7);


    // verificar itens apos o movimentp das caransbas
    deserto.verificaItens(&comercio);
    deserto.verificaItens(&militar);
    deserto.verificaItens(&barbara);

    // Posiciona caravanas no tabuleiro
    comercio.moveCaravana(&comercio, 'N',buffer); // Mover para iniciar no tabuleiro
    militar.moveCaravana(&militar, 'S',buffer);
    barbara.moveCaravana(&barbara, 'E',buffer);

    // Simula movimentos
    for (int i = 0; i < 5; ++i) {
        buffer.mostraBuffer();
        std::cout << "Turno " << i + 1 << "\n";

        comercio.moveCaravana(&comercio, 'E',buffer);
        militar.moveCaravana(&militar, 'N',buffer);
        barbara.moveCaravana(&barbara, 'O',buffer);

        std::cout << "\n";
    }

    return 0;
}
