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

//posiciona o cursor
void Buffer::posicionaCursor(int linha, int coluna){
    if (linha >= 0 && linha < numLinhas && coluna >= 0 && coluna < numColunas) {
        cursorLinha = linha;
        cursorColuna = coluna;
    }
}

//atualiza a posição do cursor
void Buffer::atualizaCursor() {
    if (cursorColuna >= numColunas) {
        cursorColuna = 0;
        cursorLinha++;
    }

    if (cursorLinha >= numLinhas) {
        cursorLinha = 0; //?? - voltar ao inicio e a melhor opcao?
    }
}

//atualiza a posição com uma cidade
void Buffer::escreve(char c){
    if (cursorLinha < numLinhas && cursorColuna < numColunas) {
        buffer[cursorLinha][cursorColuna++] = c;
    }
    atualizaCursor();
}

//move cursor
void Buffer::escreve(const char* str){
    while (*str != '\0' && cursorColuna < numColunas) {
        escreve(*str++);
    }
}

//atualiza a posição com uma caravana??
void Buffer::escreve(int numero) {
    string numStr = to_string(numero);
    escreve(numStr.c_str());
}

//escreve cada character da string
void Buffer::escreve(const string& str) {
    for (char c : str) {
        escreve(c);
    }
}


Buffer& Buffer::operator<<(char c) {
    escreve(c);
    return *this;
}

Buffer& Buffer::operator<<(const char* str) {
    escreve(str);
    return *this;
}

Buffer& Buffer::operator<<(int numero) {
    escreve(numero);
    return *this;
}



// Move uma caravana
bool Buffer::moveCaravana(Caravana* caravana, char direcao) {
    int x = caravana->getPosX();
    int y = caravana->getPosY();
    int novoX = x;
    int novoY = y;

    switch (direcao) {
        case 'N': novoX--; break;
        case 'S': novoX++; break;
        case 'O': novoY--; break;
        case 'E': novoY++; break;
        default: return false;
    }

    // Verifica se o movimento é válido
    if (novoX >= 0 && novoX < numLinhas && novoY >= 0 && novoY < numColunas && buffer[novoX][novoY] != '+') {
        buffer[x][y] = '.'; // Limpa posição atual
        buffer[novoX][novoY] = caravana->getSymbol(); // Atualiza posição
        caravana->setPos(novoX, novoY); // Atualiza coordenadas da caravana
        return true;
    }

    return false;
}




