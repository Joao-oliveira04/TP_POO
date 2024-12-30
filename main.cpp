#include "Classes\buffer.h"
#include "Classes\Caravanas.h"
#include "Classes\Deserto.h"
#include <iostream>
#include <ctime>

#include "Classes/Jogo.h"

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    Jogo jogo(10, 30, 1000); // cria o jogo com 10x30 e 1000 moedas iniciais
    jogo.iniciar(); // incia a simulacao

    return 0;
}
