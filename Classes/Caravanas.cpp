// Caravanas.cpp

#include "Caravanas.h"
#include "Cidades.h"
#include "Deserto.h"
#include "Buffer.h"
#include <iostream>
#include <cstdlib> // Para rand()
#include <algorithm> // Para std::max
#include <vector>

// Implementação da classe base Caravana
int Caravana::totalCaravanas = 0; // Inicializa a variável estática

Caravana::Caravana(std::string t, int trip, int capAgua, int capCarga, int movimentos, Buffer& buffer)
        : tipo(t), tripulantes(trip), capacidadeAgua(capAgua),
          aguaAtual(capAgua), capacidadeCarga(capCarga), cargaAtual(0),
          movimentosPorTurno(movimentos), instantesSemTrip(0), direcaoAtual('N'), buffer(buffer) {
    encontrarPosicaoValida();
    nCaravana = ++totalCaravanas; // Incrementa e atribui o número da caravana
    if(tipo == "Bárbara"){
        buffer.setChar(posX, posY, '!'); // Converte nCaravana para caractere
    } else if(tipo == "Infetada"){
        buffer.setChar(posX, posY, '?'); // Converte nCaravana para caractere
    }else{
        buffer.setChar(posX, posY, '0' + nCaravana); // Converte nCaravana para caractere
    }
}

Caravana::~Caravana() {}

void Caravana::comportamentoAutonomo() {
    // This function should be overridden in derived classes
}

void Caravana::encontrarPosicaoValida() {
    buffer.setChar(posX, posY, '.'); // Limpa a posição atual
    do {
        posX = rand() % buffer.getNumLinhas();
        posY = rand() % buffer.getNumColunas();
    } while (buffer.getChar(posX, posY) != '.');
    this->setPos(posX, posY);
    buffer.setChar(posX, posY, this->getSymbol()); // Limpa a posição atual
}

string Caravana::getTipo() const {
    return tipo;
}

// Define the getPosX function
int Caravana::getPosX() const {
    return posX;
}

// Define the getPosY function
int Caravana::getPosY() const {
    return posY;
}

// Define the setPos function
void Caravana::setPos(int x, int y) {
    posX = x;
    posY = y;
}



void Caravana::consumirAgua(int i) {
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

bool Caravana::moveCaravana(Caravana* caravana, char direcao, Buffer& buffer) {
    int x = caravana->posX;
    int y = caravana->posY;
    int novoX = x;
    int novoY = y;

    switch (direcao) {
        case 'N':
            novoX--;
            break;
        case 'S':
            novoX++;
            break;
        case 'O':
            novoY--;
            break;
        case 'E':
            novoY++;
            break;
        default:
            return false;
    }

    // Wrap around the edges
    if (novoX < 0) novoX = buffer.getNumLinhas() - 1;
    if (novoX >= buffer.getNumLinhas()) novoX = 1;
    if (novoY < 0) novoY = buffer.getNumColunas() - 1;
    if (novoY >= buffer.getNumColunas()) novoY = 1;
    // Verifica se o movimento é válido
    if (novoX >= 0 && novoX < buffer.getNumLinhas() && novoY >= 0 && novoY < buffer.getNumColunas() &&
        buffer.getChar(novoX, novoY) == '.') {
        if (buffer.getChar(x, y) >= 'A' && buffer.getChar(x, y) <= 'Z') {
            std::cout << "Origem é uma cidade.\n";
            Cidade *cidade = Deserto::getInstancia(buffer).getCidade(x, y);
            if (cidade != nullptr) {
                cidade->saiCaravana(caravana);
                buffer.setChar(x, y, cidade->getNome()[0]);
            } else {
                std::cout << "Cidade não encontrada.\n";
                buffer.setChar(x, y, '.'); // Limpa posição atual
            }
        } else {
            buffer.setChar(x, y, '.'); // Limpa posição atual
        }

        if (tipo == "Comércio") {
            if (tripulantes > 10) {
                this->consumirAgua(2);
            } else if (tripulantes > 0) {
                this->consumirAgua(1);
            }
            buffer.setChar(novoX, novoY, '0' + nCaravana); // Atualiza posição com as novas coordenadas
        } else if (tipo == "Militar") {
            if (tripulantes > 20) {
                this->consumirAgua(3);
            } else {
                this->consumirAgua(1);
            }
            buffer.setChar(novoX, novoY, '0' + nCaravana); // Atualiza posição com as novas coordenadas
        } else {
            buffer.setChar(novoX, novoY, '!'); // Atualiza posição com as novas coordenadas
        }

        caravana->setPos(novoX, novoY); // Atualiza coordenadas da caravana
        return true;
    } else if (buffer.getChar(novoX, novoY) >= 'A' && buffer.getChar(novoX, novoY) <= 'Z') { // Verifica se o destino é uma cidade
        std::cout << "Destino é uma cidade.\n";
        // Adiciona a caravana ao array das caravanas da cidade
        Deserto &deserto = Deserto::getInstancia(buffer);

        Cidade *cidade = deserto.getCidade(novoX, novoY);
        if (cidade != nullptr) {
            cidade->entraCaravana(caravana);
            buffer.setChar(x, y, '.'); // Limpa posição atual
            caravana->setPos(novoX, novoY); // Atualiza coordenadas da caravana
            std::cout << "Caravana " << caravana->getSymbol() << " entrou na cidade em (" << novoX << ", " << novoY
                      << ").\n";
            if (tipo == "Comércio") {
                if (tripulantes > 10) {
                    this->consumirAgua(2);
                } else if (tripulantes > 0) {
                    this->consumirAgua(1);
                }
            } else if (tipo == "Militar") {
                if (tripulantes > 20) {
                    this->consumirAgua(3);
                } else {
                    this->consumirAgua(1);
                }
                return true;
            }
        }else {
            std::cout << "Cidade não encontrada.\n";
        }

    } else if (buffer.getChar(novoX, novoY) == '*') {
            Deserto &deserto = Deserto::getInstancia(buffer);
            std::cout << "Caravana " << caravana->getSymbol() << " encontrou um item!\n";
            buffer.setChar(x, y, '.'); // Limpa posição atual
            if (tipo == "Comércio") {
                if (tripulantes > 10) {
                    this->consumirAgua(2);
                } else if (tripulantes > 0) {
                    this->consumirAgua(1);
                }
                buffer.setChar(novoX, novoY, '0' + nCaravana); // Atualiza posição com as novas coordenadas
            } else if (tipo == "Militar") {
                if (tripulantes > 20) {
                    this->consumirAgua(3);
                } else {
                    this->consumirAgua(1);
                }
                buffer.setChar(novoX, novoY, '0' + nCaravana); // Atualiza posição com as novas coordenadas
            } else {
                buffer.setChar(novoX, novoY, '!'); // Atualiza posição com as novas coordenadas
            }
            caravana->setPos(novoX, novoY); // Atualiza coordenadas da caravana
            deserto.verificaItens(caravana);
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
        std::cout << outraCaravana->getSymbol() << " tem " << outraCaravana->getTripulantes() << " tripulantes!\n";
        std::cout << tipo << " tem " << tripulantes << " tripulantes!\n";
    } else{
        std::cout << "O combate entre " << tipo << " e " << outraCaravana->tipo << " terminou empatado!\n";
    }

}

Caravana* Caravana::getCaravanaClose(vector<Caravana*> c) {
    // Verifica se há caravanas do jogador a até 1 posição de distância

    for (auto* caravana : c) {
        int distanciaX = std::abs(caravana->getPosX() - posX);
        int distanciaY = std::abs(caravana->getPosY() - posY);

        if (distanciaX <= 1 && distanciaY <= 1) {
            std::cout << "Caravana próxima: " << caravana->getSymbol() << " em (" << caravana->getPosX() << ", " << caravana->getPosY() << ")\n";
            return caravana;
        }
    }
    return nullptr;
}

void Caravana::destruir() {
    tripulantes = 0;
    aguaAtual = 0;
    cargaAtual = 0;
    std::cout << tipo << " foi destruída!\n";
    buffer.setChar(posX, posY, '.'); // Limpa a posição atual
}

// Implementação da classe Comercio
Comercio::Comercio(int x, int y, Buffer& buffer)
        : Caravana("Comércio", 20, 200, 40, 2, buffer) {}

void Comercio::comportamentoAutonomo(std::vector<Caravana*>& caravanasJogador, std::vector<Itens*>& itens, Buffer& buffer) {
    int alvoX = -1, alvoY = -1;
    bool encontrouItem = false;

    // Verifica se há itens a até 2 posições de distância
    for (auto* item : itens) {
        int distanciaX = std::abs(item->getPosX() - posX);
        int distanciaY = std::abs(item->getPosY() - posY);

        if (distanciaX <= 2 && distanciaY <= 2) {
            alvoX = item->getPosX();
            alvoY = item->getPosY();
            encontrouItem = true;
            break; // Para no primeiro item encontrado
        }
    }

    // Se não encontrou item, tenta manter-se ao lado de uma caravana do jogador
    if (!encontrouItem) {
        for (auto* caravana : caravanasJogador) {
            int distanciaX = std::abs(caravana->getPosX() - posX);
            int distanciaY = std::abs(caravana->getPosY() - posY);

            if ((distanciaX == 1 && distanciaY == 0) || (distanciaY == 1 && distanciaX == 0)) {
                alvoX = caravana->getPosX();
                alvoY = caravana->getPosY();
                break; // Para na primeira caravana encontrada
            }
        }
    }

    // Determina a direção do movimento
    char direcao = ' ';
    if (alvoX != -1 && alvoY != -1) {
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
    if (!this->moveCaravana(this, direcao,buffer)) {
        std::cout << "Caravana de Comércio não conseguiu mover-se para " << direcao << "!\n";
    } else {
        std::cout << "Caravana de Comércio moveu-se para " << direcao << ".\n";
    }
}

void Comercio::moverSemTripulantes() {
    char direcao;
    int movimento = rand() % 4;
    switch (movimento) {
        case 0: direcao = 'N'; break;
        case 1: direcao = 'S'; break;
        case 2: direcao = 'O'; break;
        case 3: direcao = 'E'; break;
    }
    if (!this->moveCaravana(this, direcao, buffer)) {
        std::cout << "Caravana de Comércio sem tripulantes não conseguiu mover-se para " << direcao << "!\n";
    } else {
        std::cout << "Caravana de Comércio sem tripulantes moveu-se para " << direcao << ".\n";
    }
}

// Implementação da classe Militar
Militar::Militar(int x, int y, Buffer& buffer)
        : Caravana("Militar", 40, 400, 5, 3, buffer) {}

void Militar::comportamentoAutonomo(std::vector<Barbara*>& barbaras, Buffer& buffer) {
    int alvoX = -1, alvoY = -1;
    bool encontrouBarbara = false;

    // Verifica se há caravanas bárbaras a até 6 posições de distância
    for (auto* barbara : barbaras) {
        int distanciaX = std::abs(barbara->getPosX() - posX);
        int distanciaY = std::abs(barbara->getPosY() - posY);

        if (distanciaX <= 6 && distanciaY <= 6) {
            alvoX = barbara->getPosX();
            alvoY = barbara->getPosY();
            encontrouBarbara = true;
            break; // Para na primeira caravana bárbara encontrada
        }
    }

    // Determina a direção do movimento
    if (encontrouBarbara) {
        char direcao = ' ';
        if (alvoX < posX) direcao = 'N';
        else if (alvoX > posX) direcao = 'S';
        else if (alvoY < posY) direcao = 'O';
        else if (alvoY > posY) direcao = 'E';

        // Tenta mover-se no buffer na direção escolhida
        if (!this->moveCaravana(this, direcao,buffer)) {
            std::cout << "Caravana Militar não conseguiu mover-se para " << direcao << "!\n";
        } else {
            std::cout << "Caravana Militar moveu-se para " << direcao << ".\n";
        }
    } else {
        std::cout << "Caravana Militar está parada.\n";
    }
}

void Militar::moverSemTripulantes() {
    if (!this->moveCaravana(this, direcaoAtual, buffer)) {
        std::cout << "Caravana Militar sem tripulantes não conseguiu mover-se para " << direcaoAtual << "!\n";
    } else {
        std::cout << "Caravana Militar sem tripulantes moveu-se para " << direcaoAtual << ".\n";
    };
}

// Implementação da classe Barbara
Barbara::Barbara(int x, int y, Buffer& buffer)
        : Caravana("Bárbara", 30, 100, 10, 2, buffer) {}

void Barbara::comportamentoAutonomo(vector<Caravana*>& caravanasJogador, Buffer& buffer) {
    int alvoX = -1, alvoY = -1;
    bool encontrouCaravana = false;

    // Verifica se há caravanas do jogador a até 8 posições de distância
    for (auto* caravana : caravanasJogador) {
        int distanciaX = std::abs(caravana->getPosX() - posX);
        int distanciaY = std::abs(caravana->getPosY() - posY);

        if (distanciaX <= 8 && distanciaY <= 8) {
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
    if (!this->moveCaravana(this, direcao, buffer)) {
        std::cout << "Caravana Bárbara não conseguiu mover-se para " << direcao << "!\n";
    } else {
        std::cout << "Caravana Bárbara moveu-se para " << direcao << ".\n";
    }
}
