//
// Created by david on 14/11/2024.
//

#ifndef TP_POO_DESERTO_H
#define TP_POO_DESERTO_H
#include "Buffer.h"
#include "Itens.h"
#include <vector>

class Deserto {
private:
    Buffer& buffer; // Referência ao buffer onde será desenhado o deserto
    std::vector<Itens*> itens; // Lista de itens no deserto

public:
    Deserto(Buffer& buf);
    void geraDeserto();
    void geraMontanha();    // Gera montanhas no tabuleiro
    void geraCidades(int numCidades); // Gera cidades no tabuleiro
    void geraItens(int numItens); // Novo mtodo para gerar itens
    void verificaItens(Caravana* caravana); // Aplicar o efeito dos itens
};


#endif //TP_POO_DESERTO_H
