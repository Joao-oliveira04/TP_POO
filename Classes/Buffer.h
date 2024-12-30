#ifndef TP_POO_BUFFER_H
#define TP_POO_BUFFER_H

using namespace std;
#include <string>
#include <iostream>

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

    // Métodos para acessar o buffer
    char getChar(int linha, int coluna) const;
    void setChar(int linha, int coluna, char c);
    int getNumLinhas() const { return numLinhas; }
    int getNumColunas() const { return numColunas; }
};
#endif //TP_POO_BUFFER_H