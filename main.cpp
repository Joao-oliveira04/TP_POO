#include <iostream>
#include "Buffer.h"
#include "Classes/Buffer.h"

using namespace std;

int main() {
    int nl, nc ;

    cout << "Quantidade de linhas que dejesa: " << endl;
    cin >> nl ;

    cout << "Quantidade de colunas que dejesa: " << endl;
    cin >> nc ;

    Buffer::Buffer(nl,nc);
    Buffer::mostraBuffer();

    return 0;
}
