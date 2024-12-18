#ifndef TP_POO_BUFFER_H
#define TP_POO_BUFFER_H

using namespace std;
#include <string>
#include <iostream>
#include "Caravanas.h"

class Buffer {
private:
    int numLinhas, numColunas;
    char** buffer;
    int cursorLinha, cursorColuna;
public:
    Buffer(int nl, int nc);
    Buffer(const Buffer& outro);
    void limpaBuffer();
    void mostraBuffer() const;
    ~Buffer();

    void posicionaCursor(int linha, int coluna);
    void atualizaCursor();
    bool moveCaravana(Caravana* caravana, char direcao); // Move uma caravana
    void escreve(char c);
    void escreve(const char* str);
    void escreve(int numero);
    void escreve(const string& str);
    Buffer& operator<<(char c);
    Buffer& operator<<(const char* str);
    Buffer& operator<<(int numero);
    Buffer& operator<<(const string& str);

    void preencheBuffer();
    void geraMontanha();
    void geraCidades(int n);
};
#endif //TP_POO_BUFFER_H
