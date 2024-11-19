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
    for (int i = 0; i < numLinhas; ++i){
        for (int j = 0; j < numColunas; ++j){
            cout << buffer[i][j];
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

//nao sei
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

//nao sei
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

Buffer& Buffer::operator<<(const string& str) {
    escreve(str);
    return *this;
}

//cria o tabuleiro inicial
void Buffer::desenhaMoldura() {
    //borda supe e inf
    for (int j = 0; j < numColunas; ++j) {
        buffer[0][j] = '-';
        buffer[numLinhas - 1][j] = '-';
    }
    //laterAis
    for (int i = 0; i < numLinhas; ++i) {
        buffer[i][0] = '|';
        buffer[i][numColunas - 1] = '|';
    }
    //4 cantos
    buffer[0][0] = '*';
    buffer[0][numColunas - 1] = '*';
    buffer[numLinhas - 1][0] = '*';
    buffer[numLinhas - 1][numColunas - 1] = '*';
}


