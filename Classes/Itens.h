//
// Created by david on 14/11/2024.
//

#ifndef TP_POO_ITENS_H
#define TP_POO_ITENS_H

#include "Caravanas.h"
#include <iostream>
#include <string>

/*
 * Caixa de Pandora - mata 20% da tripulação FEITO
 * Arca do tesouro - add +10% de ouro ao utilizador FEITO
 * Jaula - aumenta tripulação sem exceder a capacidade maxima FEITO
 * Mina - destroi a caravana FEITO
 * Surpresa - inventar (se for igual a outro trabalho acusam de copia) FEITO +/-
 */
class Itens {
protected:
    std::string tipo;
    int posX, posY; // posicao das coisas no deserto

public:
    Itens( const std::string t, int X, int Y) : tipo(t), posX(X), posY(Y) {}
    virtual ~Itens() {}

    virtual void aplicarEfeito(Caravana* caravana) =  0; // Um metodo para aplicar o efeito

    int getPosX() const { return posX; }
    int getPosY() const { return posY; }
    std::string getTipo() const { return tipo; }
};

// Subclasse: Caixa de Pandora
class CaixaDePandora : public Itens
{
public:
    CaixaDePandora(int x,int y) : Itens("caixa de Pandora",x,y) {}
    void aplicarEfeito(Caravana* caravana) override
    {
        if (caravana)
        {
            int perda = caravana->getTripulantes() * 0.2; // 20% da tripulacao
            caravana->setTripulantes(caravana->getTripulantes() - perda);
            std::cout << "caixa de Pandora: " << perda << " tripulantes mortos!\n";
        }
    }
};

// Subclasse: Arco do Tesouro
class ArcaDoTesouro : public Itens
{
public:
    ArcaDoTesouro(int x,int y) : Itens("arca do Tesouro",x,y) {}
    void aplicarEfeito(Caravana* caravana) override
    {
        if (caravana)
        {
            // Obtem a quantidade de moedas atual do utilizador
            int moedasAtuais = caravana->getTripulantes(); // assumindo que a caravana sabe o valor do jogador
            int incremento = moedasAtuais * 0.1; // calcula os tais + 10% das moedas
            caravana->setMoedasJogador(moedasAtuais + incremento); // Atualiza as moedas do jogador

            std::cout << "Arca do Tesouro: Adicionou " << incremento
                      << " moedas ao jogador! Total: "
                      << caravana->getMoedasJogador() << " moedas.\n";
        }
    }
};

// Subclasse: Jaula
class Jaula : public Itens {
public:
    Jaula(int x, int y) : Itens("Jaula", x, y) {}
    void aplicarEfeito(Caravana* caravana) override {
        if (caravana) {
            int capacidadeLivre = caravana->getMaxTripulantes() - caravana->getTripulantes();
            int aumento = std::min(5, capacidadeLivre); // Aumenta até 5 tripulantes ou o máximo permitido
            caravana->setTripulantes(caravana->getTripulantes() + aumento);
            std::cout << "Jaula: Libertou prisioneiros! Tripulantes aumentados em " << aumento << "!\n";
        }
    }
};

// Subclasse: Mina
class Mina : public Itens
{
public:
    Mina (int x,int y) : Itens("Mina",x,y) {}
    void aplicarEfeito(Caravana* caravana) override
    {
        if (caravana)
        {
            caravana->destruir(); // a caravana fica destruida
            std::cout << "Mina: Caravana destruída!\n";
        }
    }
};

//Subclasse: Surpresa
class Surpresa : public Itens
{
public:
    Surpresa (int x,int y) : Itens("Surpresa",x,y) {}
    void aplicarEfeito(Caravana* caravana) override
    {
        if (caravana)
        {
            // Define o efeito surpresa - exemplo: teletransportar a caravana ATENCAO FOI O CHAT....
            int novaPosX = rand() % 10; // Exemplo de teletransporte
            int novaPosY = rand() % 10;
            caravana->setPos(novaPosX, novaPosY);
            std::cout << "Surpresa: Caravana teleporta para (" << novaPosX << ", " << novaPosY << ")!\n";
        }
    }
};

#endif //TP_POO_ITENS_H
