
#ifndef TP_POO_ITENS_H
#define TP_POO_ITENS_H

#include <iostream>
#include <string>

class Caravana; // Forward declaration

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
    int posX, posY;

public:
    Itens(const std::string t, int X, int Y) : tipo(t), posX(X), posY(Y) {}
    virtual ~Itens() {}

    virtual void aplicarEfeito(Caravana* caravana) = 0;

    int getPosX() const { return posX; }
    int getPosY() const { return posY; }
    std::string getTipo() const { return tipo; }
};

class CaixaDePandora : public Itens {
public:
    CaixaDePandora(int x, int y) : Itens("caixa de Pandora", x, y) {}
    void aplicarEfeito(Caravana* caravana) override;
};

class ArcaDoTesouro : public Itens {
public:
    ArcaDoTesouro(int x, int y) : Itens("arca do Tesouro", x, y) {}
    void aplicarEfeito(Caravana* caravana) override;
};

class Jaula : public Itens {
public:
    Jaula(int x, int y) : Itens("Jaula", x, y) {}
    void aplicarEfeito(Caravana* caravana) override;
};

class Mina : public Itens {
public:
    Mina(int x, int y) : Itens("Mina", x, y) {}
    void aplicarEfeito(Caravana* caravana) override;
};

class Surpresa : public Itens {
public:
    Surpresa(int x, int y) : Itens("Surpresa", x, y) {}
    void aplicarEfeito(Caravana* caravana) override;
};

#endif // TP_POO_ITENS_H
