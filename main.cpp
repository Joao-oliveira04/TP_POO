#include "Classes\buffer.h"
#include "Classes\Caravanas.h"
#include <iostream>
#include <ctime>

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Cria o tabuleiro (10x30)
    Buffer buffer(10, 30);
    buffer.preencheBuffer();
    buffer.geraMontanha();
    buffer.geraCidades(5);
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
