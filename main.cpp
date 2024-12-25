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
    //deserto.geraMontanha();
    deserto.geraCidades(5);
    //deserto.geraItens(5); // Por exemplo 5 itens

    // Cria caravanas
    Comercio comercio(3, 3, buffer);
    Militar militar(5, 5, buffer);
    Barbara barbara(7, 7, buffer);

    // Vetor de caravanas do jogador
    std::vector<Caravana*> caravanasJogador = { &comercio, &militar };


    std::cout << "\n";
    // verificar itens apos o movimentp das caransbas
    deserto.verificaItens(&comercio);
    deserto.verificaItens(&militar);
    deserto.verificaItens(&barbara);

    // Posiciona caravanas no tabuleiro
    comercio.moveCaravana(&comercio, 'N'); // Mover para iniciar no tabuleiro
    militar.moveCaravana(&militar, 'S');
    barbara.moveCaravana(&barbara, 'E');

    // Simula movimentos
    for (int i = 0; i < 10; ++i) {
        buffer.mostraBuffer();
        std::cout << "Turno " << i + 1 << "\n";
        comercio.moveCaravana(&comercio, 'E');
        militar.moveCaravana(&militar, 'N');
        barbara.moveCaravana(&barbara, 'O');
        if(barbara.semTripulantes() || militar.semTripulantes() || comercio.semTripulantes()){
            barbara.combate(&militar);
        }
        std::cout << "\n";
    }

    return 0;
}
