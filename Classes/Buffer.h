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

    void escreve(char c);
    void escreve(const char* str);
    void escreve(int numero);
    void escreve(const string& str);
    Buffer& operator<<(char c);
    Buffer& operator<<(const char* str);
    Buffer& operator<<(int numero);
    Buffer& operator<<(const string& str);

    void desenhaMoldura();
};

#endif //TP_POO_BUFFER_H
