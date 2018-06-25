#ifndef MYHASH_H
#define MYHASH_H

#include <iostream>
#include "mylist.h"
#include "../assunto.h"

using namespace std;

class MyHash
{
private:
    MyList<Assunto> *myHash;
    int tamanho;
public:
    MyHash(){myHash=0; tamanho=0;}
    MyHash(int tamanho_) {myHash = new MyList<Assunto>[tamanho_]; tamanho = tamanho_;}

    inline int funcaoHash(int k){return k-1;}
    inline int getTamanho(){return tamanho;}

    void inserir(int k, Assunto assunto);
    MyList<Assunto> get(int k);

};

void MyHash::inserir(int k, Assunto assunto)
{
    int index = funcaoHash(k);
    if(index<tamanho && index>=0){
        myHash[index].inserir(assunto);
    }
}

MyList<Assunto> MyHash::get(int k)
{
    int index = funcaoHash(k);
    return myHash[index];
}

#endif // MYHASH_H
