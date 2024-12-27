//
// Created by david on 14/11/2024.
//

#ifndef TP_POO_CARAVANAS_H
#define TP_POO_CARAVANAS_H


#ifndef CARAVANA_H
#define CARAVANA_H

#include <string>
#include <vector>
#include "Buffer.h"
#include <cmath> // Para cálculos matemáticos (distância)
// Classe Base: Caravana
class Caravana {
protected:
    Buffer& buffer;
    std::string tipo;
    int posX, posY;           // Posição no tabuleiro
    int nCaravana;            // Número da caravana
    int tripulantes;          // Número de tripulantes
    int MaxTripulantes = 50;  // Número máximo de tripulantes
    int capacidadeAgua;       // Capacidade total de água
    int aguaAtual;            // Quantidade atual de água
    int capacidadeCarga;      // Capacidade total de carga
    int cargaAtual;           // Quantidade atual de carga
    int movimentosPorTurno;   // Número máximo de movimentos por turno
    int instantesSemTrip;     // Contador de instantes sem tripulantes
    int moedas;               // moedas do jogador
    char direcaoAtual;        // Última direção de movimento
    static int totalCaravanas;// Número da caravana

    void encontrarPosicaoValida(); // Método para encontrar uma posição válida
public:
    Caravana(std::string t, int trip, int capAgua, int capCarga, int movimentos, Buffer& buf);
    virtual ~Caravana();

    virtual void mover(char direcao);
    virtual void comportamentoAutonomo(); // Metodo abstrato
    void consumirAgua();
    bool semAgua() const;
    bool semTripulantes() const;

    char getSymbol() const;   // Retorna o símbolo da caravana
    int getPosX() const;      // Retorna a posição X
    int getPosY() const;      // Retorna a posição Y
    void setPos(int x, int y);// Atualiza a posição
    void destruir();   // destroi a caravana
    int getTripulantes() {return tripulantes;}// tripulantes das caravanas
    void setTripulantes(int i); // tripulantes
    int getMaxTripulantes() {return MaxTripulantes;}// numero max de tripulantes em cada caravanna
    void setMoedasJogador(int i); // moedas depois da atualizacao
    int getMoedasJogador() {return moedas;}// moedas antes da atualizacao
    Caravana* getCaravana(int nCaravana);// retorna a caravana
    bool moveCaravana(Caravana* caravana, char direcao);
    void combate(Caravana* outraCaravana);
};

// Classe Derivada: Barbara
class Barbara : public Caravana {
public:
    Barbara(int x, int y, Buffer& buffer);
    void comportamentoAutonomo(std::vector<Caravana*>& caravanasJogador, Buffer& buffer); // Recebe lista de caravanas do jogador e buffer
};

// Classe Derivada: Comercio
class Comercio : public Caravana {
public:
    Comercio(int x, int y, Buffer& buffer);
    void comportamentoAutonomo() override;
    void moverSemTripulantes();
};

// Classe Derivada: Militar
class Militar : public Caravana {
public:
    Militar(int x, int y, Buffer& buffer);
    void comportamentoAutonomo() override;
    void moverSemTripulantes();
};

// Classe Derivada: Infetada
class Infetada : public Caravana {
public:
    Infetada(int x, int y, Buffer& buffer);
    void comportamentoAutonomo() override;
};


#endif // CARAVANA_H



#endif //TP_POO_CARAVANAS_H
