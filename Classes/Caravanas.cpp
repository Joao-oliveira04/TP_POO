
#include "Caravanas.h"
#include "Buffer.h"
#include <iostream>
#include <cstdlib> // Para rand()
#include <algorithm> // Para std::max
#include <vector>

int Caravana::totalCaravanas = 0; // Inicializa a variável estática

// Implementação da classe base Caravana
Caravana::Caravana(std::string t, int trip, int capAgua, int capCarga, int movimentos, Buffer& buffer)
        : tipo(t), tripulantes(trip), capacidadeAgua(capAgua),
          aguaAtual(capAgua), capacidadeCarga(capCarga), cargaAtual(0),
          movimentosPorTurno(movimentos), instantesSemTrip(0), direcaoAtual('N'), buffer(buffer) {
    encontrarPosicaoValida();
    nCaravana = ++totalCaravanas; // Incrementa e atribui o número da caravana
    std::cout << "Caravana criada " << nCaravana << " em (" << posX << ", " << posY << ").\n";
    if(tipo == "Bárbara"){
        buffer.setChar(posX, posY, '!'); // Converte nCaravana para caractere
    } else{
        buffer.setChar(posX, posY, '0' + nCaravana); // Converte nCaravana para caractere
    }

}

void Barbara::comportamentoAutonomo(vector<Caravana*>& caravanasJogador, Buffer& buffer) {
    int alvoX = -1, alvoY = -1;
    bool encontrouCaravana = false;

    // Verifica se há caravanas do jogador a até 8 posições de distância
    for (auto* caravana : caravanasJogador) {
        int distanciaX = std::abs(caravana->getPosX() - posX);
        int distanciaY = std::abs(caravana->getPosY() - posY);

        if ((distanciaX <= 8 && distanciaY == 0) || (distanciaY <= 8 && distanciaX == 0)) {
            alvoX = caravana->getPosX();
            alvoY = caravana->getPosY();
            encontrouCaravana = true;
            break; // Para na primeira caravana encontrada
        }
    }

    // Determina a direção do movimento
    char direcao = ' ';
    if (encontrouCaravana) {
        if (alvoX < posX) direcao = 'N';
        else if (alvoX > posX) direcao = 'S';
        else if (alvoY < posY) direcao = 'O';
        else if (alvoY > posY) direcao = 'E';
    } else {
        // Movimento aleatório
        int movimento = rand() % 4;
        switch (movimento) {
        case 0: direcao = 'N'; break;
        case 1: direcao = 'S'; break;
        case 2: direcao = 'O'; break;
        case 3: direcao = 'E'; break;
        }
    }

    // Tenta mover-se no buffer na direção escolhida
    if (!this->moveCaravana(this, direcao)) {
        std::cout << "Caravana Bárbara não conseguiu mover-se para " << direcao << "!\n";
    } else {
        std::cout << "Caravana Bárbara moveu-se para " << direcao << ".\n";
    }
}

void Caravana::encontrarPosicaoValida() {
    do {
        posX = rand() % buffer.getNumLinhas();
        posY = rand() % buffer.getNumColunas();
    } while (buffer.getChar(posX, posY) != '.');
}
Caravana::~Caravana() {}

void Caravana::mover(char direcao) {
    direcaoAtual = direcao;
    switch (direcao) {
        case 'N': posX--; break;
        case 'S': posX++; break;
        case 'O': posY--; break;
        case 'E': posY++; break;
    }
    std::cout << tipo << " moveu-se para (" << posX << ", " << posY << ").\n";
}

void Caravana::consumirAgua() {
    if (tripulantes > 0) {
        int consumo = (tripulantes > (capacidadeAgua / 4)) ? 2 : 1;
        aguaAtual = std::max(aguaAtual - consumo, 0);
        std::cout << tipo << " consumiu " << consumo << " litros de água. Restante: " << aguaAtual << " litros.\n";
    }
}

bool Caravana::semAgua() const { return aguaAtual <= 0; }

void Caravana::setTripulantes(int i){
    if(i<0){
        tripulantes = 0;
        this->destruir();
    } else{
        tripulantes = i;
    }
}

bool Caravana::semTripulantes() const { return tripulantes == 0; }

void Caravana::setMoedasJogador(int i) {
    if (i < 0) {
        moedas = 0;
    } else {
        moedas = i;
    }
}

bool Caravana::moveCaravana(Caravana* caravana, char direcao) {
    int x = caravana->posX;
    int y = caravana->posY;
    int novoX = x;
    int novoY = y;

    switch (direcao) {
        case 'N': novoX--; break;
        case 'S': novoX++; break;
        case 'O': novoY--; break;
        case 'E': novoY++; break;
        default: return false;
    }

    /*if(novoY <= 0){
        buffer.setChar(x, y, '.'); // Limpa posição atual
        if(tipo == "Bárbara"){
            buffer.setChar(x, buffer.getNumLinhas() -1, '!'); // Converte nCaravana para caractere
            return true;
        } else{
            buffer.setChar(x, buffer.getNumLinhas() -1, '0' + nCaravana); // Converte nCaravana para caractere
        }
        return true;
    } else if (novoY >= buffer.getNumColunas()){
        buffer.setChar(x, y, '.'); // Limpa posição atual
        if(tipo == "Bárbara"){
            buffer.setChar(x, 0, '!'); // Converte nCaravana para caractere
        } else{
            buffer.setChar(x, 0, '0' + nCaravana); // Converte nCaravana para caractere
        }
        return true;
    } else if(novoX <= 0){
        buffer.setChar(x, y, '.'); // Limpa posição atual
        if(tipo == "Bárbara"){
            buffer.setChar(buffer.getNumColunas() -1, y, '!'); // Converte nCaravana para caractere
        } else{
            buffer.setChar(buffer.getNumColunas() -1, y, '0' + nCaravana); // Converte nCaravana para caractere
        }
        return true;
    } else if (novoX >= buffer.getNumLinhas()){
        buffer.setChar(x, y, '.'); // Limpa posição atual
        if(tipo == "Bárbara"){
            buffer.setChar(0, y, '!'); // Converte nCaravana para caractere
        } else{
            buffer.setChar(0, y, '0' + nCaravana); // Converte nCaravana para caractere
        }
        return true;
    }*/

    // Verifica se o movimento é válido
    if (novoX >= 0 && novoX < buffer.getNumLinhas() && novoY >= 0 && novoY < buffer.getNumColunas() && buffer.getChar(novoX, novoY) == '.') {
        buffer.setChar(x, y, '.'); // Limpa posição atual
        if(tipo == "Bárbara"){
            buffer.setChar(novoX, novoY, '!'); // Atualiza posição com as novas coordenadas
        } else{
            buffer.setChar(novoX, novoY, '0' + nCaravana); // Atualiza posição com as novas coordenadas
        }

        caravana->setPos(novoX, novoY); // Atualiza coordenadas da caravana
        return true;
    }

    return false;
}

char Caravana::getSymbol() const {
    if(tipo == "Bárbara"){
        return '!';
    }
    return '0' + nCaravana;
}

Caravana *Caravana::getCaravana(int nCaravana) {
    if (nCaravana == 0) {
        return nullptr;
    }
    return nullptr;
}

void Caravana::combate(Caravana* outraCaravana) {
    int rollCaravana1 = rand() % tripulantes;
    int rollCaravana2 = rand() % outraCaravana->getTripulantes();
    std::cout << "entrei";
    std::cout << "entrei";
    if(rollCaravana1 > rollCaravana2){
        outraCaravana->setTripulantes(outraCaravana->getTripulantes() - rollCaravana1*2);
        tripulantes = tripulantes*0.8;
        std::cout << tipo << " venceu o combate contra " << outraCaravana->tipo << "!\n";
        std::cout << tipo << " tem " << outraCaravana->getTripulantes() << " tripulantes!\n";
        std::cout << tipo << " tem " << tripulantes << " tripulantes!\n";
    } else if(rollCaravana1 < rollCaravana2){
        tripulantes -= rollCaravana2*2;
        if(tripulantes < 0){
            tripulantes = 0;
            this->destruir();
        }
        outraCaravana->setTripulantes(outraCaravana->getTripulantes()*0.8);
        std::cout << outraCaravana->tipo << " venceu o combate contra " << tipo << "!\n";
        std::cout << tipo << " tem " << outraCaravana->getTripulantes() << " tripulantes!\n";
        std::cout << tipo << " tem " << tripulantes << " tripulantes!\n";
    } else{
        std::cout << "O combate entre " << tipo << " e " << outraCaravana->tipo << " terminou empatado!\n";
    }

}

void Caravana::destruir() {
    tripulantes = 0;
    aguaAtual = 0;
    cargaAtual = 0;
    std::cout << tipo << " foi destruída!\n";
}

// Implementação da classe Comercio
Comercio::Comercio(int x, int y, Buffer& buffer)
        : Caravana("Comércio", 20, 200, 40, 2, buffer) {}

void Comercio::comportamentoAutonomo() {
    std::cout << "Caravana de Comércio procura itens ou proteção próxima.\n";
    // Lógica adicional pode ser implementada aqui
}

void Comercio::moverSemTripulantes() {
    posX += rand() % 3 - 1; // Movimento aleatório
    posY += rand() % 3 - 1;
    std::cout << "Caravana de Comércio sem tripulantes move-se aleatoriamente.\n";
}

// Implementação da classe Militar
Militar::Militar(int x, int y, Buffer& buffer)
        : Caravana("Militar", 40, 400, 5, 3, buffer) {}

void Militar::comportamentoAutonomo() {
    std::cout << "Caravana Militar verifica por caravanas bárbaras próximas.\n";
    // Lógica adicional pode ser implementada aqui
}

void Militar::moverSemTripulantes() {
    mover(direcaoAtual); // Continua na última direção
    std::cout << "Caravana Militar sem tripulantes move-se na última direção.\n";
}

// Implementação da classe Barbara
Barbara::Barbara(int x, int y, Buffer& buffer)
        : Caravana("Bárbara", 30, 100, 10, 2, buffer) {}


int Caravana::getPosX() const { return posX; }
int Caravana::getPosY() const { return posY; }
void Caravana::setPos(int x, int y) {
    posX = x;
    posY = y;
}

