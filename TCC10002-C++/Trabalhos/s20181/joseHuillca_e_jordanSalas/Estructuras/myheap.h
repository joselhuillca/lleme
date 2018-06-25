#ifndef MYHEAP_H
#define MYHEAP_H

#include "../atendimento.h"
#include <iostream>

#define MAX_SIZE_HEAP 100

using namespace std;

class MyHeap
{
private:
    Atendimento *lista;
    int tamanho;
public:
    MyHeap(){lista = new Atendimento[MAX_SIZE_HEAP](); tamanho = 0;}
    //~myheap();

    void inserir(Atendimento atendimento);
    void subir(int posicao);

    void trocar(int i, int j);

    Atendimento excluir();
    void descer(int posicao);

    void mostrarHeap();
};

void MyHeap::inserir(Atendimento atendimento)
{
    if(tamanho >= MAX_SIZE_HEAP){
        //resizeMyHeap();
    }else{
        lista[tamanho] = atendimento;
        subir(tamanho);
        tamanho += 1;
    }
}

void MyHeap::subir(int posicao)
{
    int padre = (posicao-1)/2;
    if(lista[posicao].getPrioridade() > lista[padre].getPrioridade()){
        trocar(posicao, padre);
        subir(padre);
    }
}

void MyHeap::trocar(int i, int j)
{
    Atendimento aux = lista[i];
    lista[i] = lista[j];
    lista[j] = aux;
}

Atendimento MyHeap::excluir()
{
    if(tamanho>0){
        Atendimento aux = lista[0];
        tamanho -= 1;
        trocar(0, tamanho);
        descer(0);
        return aux;
    }
    return Atendimento();
}

void MyHeap::descer(int posicao)
{
    int izq = 2*posicao + 1;
    int der = 2*posicao + 2;
    int j = izq;

    if(izq < tamanho){
        if(der < tamanho){
            if(lista[der].getPrioridade() > lista[izq].getPrioridade()){
                j = der;
            }
        }
        if(lista[j].getPrioridade() > lista[posicao].getPrioridade()){
            trocar(j, posicao);
            descer(j);
        }
    }
}

void MyHeap::mostrarHeap()
{
    for(int i=0; i<tamanho; i++){
        cout<<"Cliente: "<<lista[i].getCliente().getNome()<<"  Prioridade: "<<lista[i].getPrioridade()<<endl;
    }
}

#endif // MYHEAP_H
