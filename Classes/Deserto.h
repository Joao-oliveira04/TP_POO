//
// Created by david on 14/11/2024.
//

#ifndef TP_POO_DESERTO_H
#define TP_POO_DESERTO_H
#include "Buffer.h"

class Deserto {
private:
    Buffer& buffer; // Referência ao buffer onde será desenhado o deserto

public:
    Deserto(Buffer& buf);
    void geraDeserto();
    void geraMontanha();    // Gera montanhas no tabuleiro
    void geraCidades(int numCidades); // Gera cidades no tabuleiro
};


#endif //TP_POO_DESERTO_H
