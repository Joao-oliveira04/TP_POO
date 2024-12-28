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

class Cidade {
private:
    std::string nome; // Nome único da cidade
    int posX, posY; // Posição da cidade no mapa
    std::vector<Caravana*> caravanas; // Caravanas dentro da cidade
    std::vector<Caravana*> caravanas_buy; // Caravanas para comprar
    Buffer& buffer;

public:
    Cidade(std::string nome, int x, int y, Buffer& buf);
    std::string getNome() const;
    int getPosX() const;
    int getPosY() const;
    void entraCaravana(Caravana* caravana);
    void saiCaravana(Caravana* caravana);
    void addCaravana(Caravana* caravana);
    void buyCaravana(Caravana* caravana);
    void buyTripulantes(Caravana* caravana,int i); //i = quantidade de tripulantes
    void buyMercadoria(Caravana* caravana, int i); //i = quantidade de mercadoria
    void sellMercadoria(Caravana* caravana, int i); //i = quantidade de mercadoria
    void listarCaravanas() const;
    bool isAccessible() const;
};


#endif //TP_POO_CIDADES_H
