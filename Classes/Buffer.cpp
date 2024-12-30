// Buffer.cpp
#include "Buffer.h"

using namespace std;

//constroi o buffer com o cursor na posição 0 0
Buffer::Buffer(int nl, int nc) : numLinhas(nl), numColunas(nc), cursorLinha(0), cursorColuna(0) {
    buffer = new char*[numLinhas];
    for (int i = 0; i < numLinhas; ++i) {
        buffer[i] = new char[numColunas];
    }
    limpaBuffer();
}

//constroi o buffer com o cursor em algum sitio especifico
Buffer::Buffer(const Buffer& outro): numLinhas(outro.numLinhas), numColunas(outro.numColunas),
                                     cursorLinha(outro.cursorLinha), cursorColuna(outro.cursorColuna) {
    buffer = new char*[numLinhas];
    for (int i = 0; i < numLinhas; ++i) {
        buffer[i] = new char[numColunas];
        for (int j = 0; j < numColunas; ++j) {
            buffer[i][j] = outro.buffer[i][j];
        }
    }
}

//limpa o buffer
void Buffer::limpaBuffer() {
    for (int i = 0; i < numLinhas; ++i) {
        for (int j = 0; j < numColunas; ++j) {
            buffer[i][j] = ' ';
        }
    }
}

//mostra na consola o buffer
void Buffer::mostraBuffer() const{
    for (int i = 0; i < numLinhas; i++){
        for (int j = 0; j < numColunas; j++){
            cout << this->getChar(i,j);
        }
        cout << endl;
    }
}

//destroi o buffer
Buffer::~Buffer() {
    for (int i = 0; i < numLinhas; ++i) {
        delete[] buffer[i];
    }
    delete[] buffer;
}

char Buffer::getChar(int linha, int coluna) const {
    if (linha >= 0 && linha < numLinhas && coluna >= 0 && coluna < numColunas) {
        return buffer[linha][coluna];
    }
    return ' ';
}

//retorna o caracter na posição
void Buffer::setChar(int linha, int coluna, char c) {
    if (linha >= 0 && linha < numLinhas && coluna >= 0 && coluna < numColunas) {
        buffer[linha][coluna] = c;
    }
}