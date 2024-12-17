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

Buffer& Buffer::operator<<(const string& str) {
    escreve(str);
    return *this;
}

//preenche o tabuleiro
void Buffer::preencheBuffer() {
    for (int j = 0; j < numColunas; ++j) {
        for (int i = 0; i < numLinhas; ++i) {
            buffer[i][j] = '.';
        }
    }
}

//preenche o tabuleiro
void Buffer::geraMontanha() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    int larguraMontanha, alturaMontanha;
    int posicaoInicioX, posicaoInicioY;

    // Gera múltiplas montanhas (neste exemplo, 3 montanhas aleatórias)
    for (int montanha = 0; montanha < 3; ++montanha) {
        // Largura e altura mínima das montanhas
        larguraMontanha = rand() % 4 + 2;  // Largura entre 2 e 5 colunas
        alturaMontanha = rand() % 3 + 2;   // Altura entre 2 e 4 linhas

        // Gera posição inicial da montanha garantindo que fique dentro dos limites
        posicaoInicioX = rand() % (numLinhas - alturaMontanha);
        posicaoInicioY = rand() % (numColunas - larguraMontanha);

        // Preenche o buffer com a montanha ('+')
        for (int i = 0; i < alturaMontanha; ++i) {
            for (int j = 0; j < larguraMontanha; ++j) {
                buffer[posicaoInicioX + i][posicaoInicioY + j] = '+';
            }
        }
    }
}

void Buffer::geraCidades(int numCidades) {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    char cidade = 'a'; // Letra inicial para representar as cidades
    int posicaoX, posicaoY;

    for (int i = 0; i < numCidades; ++i) {
        // Encontre uma posição livre no tabuleiro
        do {
            posicaoX = rand() % numLinhas;  // Linha aleatória
            posicaoY = rand() % numColunas; // Coluna aleatória
        } while (buffer[posicaoX][posicaoY] != '.'); // Repete até encontrar posição vazia
        if(buffer[posicaoX+1][posicaoY+1] == '.'
           || buffer[posicaoX-1][posicaoY+1] == '.'
           || buffer[posicaoX+1][posicaoY-1] == '.'
           || buffer[posicaoX-1][posicaoY-1] == '.')//verifica se esta rodeado por montanhas
        {
            // Insere a cidade na posição encontrada
            buffer[posicaoX][posicaoY] = cidade;

            // Incrementa a letra da cidade ('a' -> 'b' -> 'c' ...)
            if (cidade < 'z') {
                ++cidade;
            } else {
                cidade = 'a'; // Volta para 'a' se chegar ao 'z'
            }
        }
        else{
            i--;
        }
    }
}




