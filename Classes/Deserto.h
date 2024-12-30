//
// Created by david on 14/11/2024.
//

#ifndef TP_POO_DESERTO_H
#define TP_POO_DESERTO_H
#include "Buffer.h"
#include "Itens.h"
#include "Caravanas.h"

#include <vector>
class Cidade;
class Deserto {
private:
    Buffer& buffer; // Referência ao buffer onde será desenhado o deserto
    static std::vector<Itens*> itens; // Lista de itens no deserto
    std::vector<Caravana*> caravanas; // Lista de caravanas no deserto
    std::vector<Caravana*> Barbaras; // Lista de cidades no deserto
    static std::vector<Cidade*> cidades; // Lista de cidades no deserto

public:
    Deserto(Buffer& buf);
    static Deserto& getInstancia(Buffer& buf);
    void geraDeserto();
    void geraMontanha();    // Gera montanhas no tabuleiro
    void geraCidades(int numCidades); // Gera cidades no tabuleiro
    void geraItens(int numItens); // Novo mtodo para gerar itens
    Cidade* getCidade(int x, int y) const; // Retorna a cidade nas coordenadas
    void verificaItens(Caravana* caravana); // Aplicar o efeito dos itens

    void adicionaCidade(Cidade* cidade);
    void listarCidades() const;
    vector<Cidade*> getCidades();  // cidade
};


#endif //TP_POO_DESERTO_H
