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
#include "Itens.h"
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
    bool autonomo = false; // Indica se a caravana está em modo autonomo

public:
    Caravana(std::string t, int trip, int capAgua, int capCarga, int movimentos, Buffer& buf);
    virtual ~Caravana();

    void encontrarPosicaoValida(); // Metodo para encontrar uma posição válida
    virtual void comportamentoAutonomo(); // Metodo abstrato
    void consumirAgua(int i);
    bool semAgua() const;
    bool semTripulantes() const;

    char getSymbol() const;   // Retorna o símbolo da caravana
    string getTipo() const;     // Retorna o tipo da caravana
    int getPosX() const;      // Retorna a posição X
    int getPosY() const;      // Retorna a posição Y
    void setPos(int x, int y);// Atualiza a posição
    Caravana* getCaravanaClose(vector<Caravana*>);  // retorna a caravana nas casas adjacentes
    void destruir();   // destroi a caravana
    int getTripulantes() {return tripulantes;}// tripulantes das caravanas
    void setTripulantes(int i); // tripulantes
    int getMaxTripulantes() {return MaxTripulantes;}// numero max de tripulantes em cada caravanna
    void setMoedasJogador(int i); // moedas depois da atualizacao
    int getMoedasJogador() {return moedas;}// moedas antes da atualizacao
    Caravana* getCaravana(int nCaravana);// retorna a caravana
    bool moveCaravana(Caravana* caravana, char direcao,Buffer& buffer); // move a caravana
    void combate(Caravana* outraCaravana);
    int getCargaAtual() {return cargaAtual;}
    void setCargaAtual(int novaCarga) {cargaAtual = novaCarga;}
    int getCapacidadeCarga() const { return capacidadeCarga; }
    void setAutonomo(bool estado) { autonomo = estado; }
    bool isAutonomo() const { return autonomo; }
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
    void comportamentoAutonomo(std::vector<Caravana*>& caravanasJogador, std::vector<Itens*>& itens, Buffer& buffer);
    void moverSemTripulantes();
};

// Classe Derivada: Militar
class Militar : public Caravana {
public:
    Militar(int x, int y, Buffer& buffer);
    void comportamentoAutonomo(std::vector<Barbara*>& barbaras, Buffer& buffer);
    void moverSemTripulantes();
};




#endif // CARAVANA_H



#endif //TP_POO_CARAVANAS_H
