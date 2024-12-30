//
// Created by david on 14/11/2024.
//

#ifndef TP_POO_CIDADES_H
#define TP_POO_CIDADES_H
#include <string>
#include <vector>
#include "Buffer.h"
#include "Caravanas.h"
#include "Deserto.h"
#include "Jogo.h"

class Cidade {
private:
    std::string nome; // Nome único da cidade
    int posX, posY; // Posição da cidade no mapa
    int nCaravanas = 0; // Número de caravanas na cidade
    std::vector<Caravana*> caravanas; // Caravanas dentro da cidade
    Buffer& buffer;

public:
    Cidade(std::string nome, int x, int y, Buffer& buf);
    std::string getNome() const;
    int getPosX() const;
    int getPosY() const;
    int getnCaravanas() const;
    void entraCaravana(Caravana* caravana);
    void saiCaravana(Caravana* caravana);
    void listarCaravanas() const;
    bool isAccessible() const;
};


#endif //TP_POO_CIDADES_H
