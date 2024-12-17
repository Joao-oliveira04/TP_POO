#include <iostream>
#include "Classes/Buffer.h"

using namespace std;

int main() {
    int nl,nc;
    cout<<"numero linhas:";
    cin>>nl;
    cout<<"numero colunas:";
    cin>>nc;

    Buffer b(nl,nc);
    b.preencheBuffer();
    b.geraMontanha();
    b.geraMontanha();
    b.geraCidades(2);
    b.mostraBuffer();
    return 0;
}