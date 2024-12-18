//
// Created by david on 14/11/2024.
//

#ifndef TP_POO_CARAVANAS_H
#define TP_POO_CARAVANAS_H


#ifndef CARAVANA_H
#define CARAVANA_H

#include <string>

// Classe Base: Caravana
class Caravana {
protected:
    std::string tipo;
    int posX, posY;           // Posição no tabuleiro
    int tripulantes;          // Número de tripulantes
    int capacidadeAgua;       // Capacidade total de água
    int aguaAtual;            // Quantidade atual de água
    int capacidadeCarga;      // Capacidade total de carga
    int cargaAtual;           // Quantidade atual de carga
    int movimentosPorTurno;   // Número máximo de movimentos por turno
    int instantesSemTrip;     // Contador de instantes sem tripulantes
    char direcaoAtual;        // Última direção de movimento

public:
    Caravana(std::string t, int x, int y, int trip, int capAgua, int capCarga, int movimentos);
    virtual ~Caravana();

    virtual void mover(char direcao);
    virtual void comportamentoAutonomo() = 0; // Metodo abstrato
    void consumirAgua();
    bool semAgua() const;
    bool semTripulantes() const;

    char getSymbol() const;   // Retorna o símbolo da caravana
    int getPosX() const;      // Retorna a posição X
    int getPosY() const;      // Retorna a posição Y
    void setPos(int x, int y);// Atualiza a posição
    void destruir();   // destroi a caravana
    int getTripulantes(); // tripulantes das caravanas
    void setTripulantes(int i); // tripulantes
    int getMaxTripulantes(); // numero max de tripulantes em cada caravanna
    void setMoedasJoagor(int i); // moedas depois da atualizacao
    void getMoedasJogador(); // moedas antes da atualizacao

    static int getMoedasJoagor();

};

// Classe Derivada: Comercio
class Comercio : public Caravana {
public:
    Comercio(int x, int y);
    void comportamentoAutonomo() override;
    void moverSemTripulantes();
};

// Classe Derivada: Militar
class Militar : public Caravana {
public:
    Militar(int x, int y);
    void comportamentoAutonomo() override;
    void moverSemTripulantes();
};

// Classe Derivada: Barbara
class Barbara : public Caravana {
public:
    Barbara(int x, int y);
    void comportamentoAutonomo() override;
};


#endif // CARAVANA_H



#endif //TP_POO_CARAVANAS_H
