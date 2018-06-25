#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>

using namespace std;

template<typename T>
class MyList{
private:
    struct node{
      T cont;
      node *p_next;
      ~node(){
        if(p_next)
          delete[] p_next;
      }
    };
private:
    int tamanho;
    node *p_start;
    node *p_insert;

public:
    MyList(){p_start=0;p_insert=0;tamanho=0;}
    void inserir(T dato);
    void inserir2(T dato);
    void excluir(T dato);
    void excluir2(T dato);
    void myprint();

    inline int getTamanho(){return tamanho;}
    inline bool estaVazio(){return tamanho==0;}

    float mediaUrgencias();
    float mediaDuracaoAtendimento();

    T get(int posicao);
    T operator[](int posicao){return get(posicao);}
};

/** ------------------ FUNCTIONS ------------------------ **/
template<typename T>
void MyList<T>::inserir2(T dato){
    node *new_node = new node;
    new_node->cont = dato;
    new_node->p_next = 0;

    if(p_start == 0){
        p_start = new_node;
        p_insert = new_node;
        tamanho += 1;
    }
    else{
        p_insert->p_next = new_node;
        p_insert = p_insert->p_next;
        tamanho += 1;
    }
}

template<typename T>
void MyList<T>::inserir(T dato){
    node *new_node = new node;
    new_node->cont = dato;
    new_node->p_next = 0;

    if(p_start == 0){
        p_start = new_node;
        tamanho += 1;
    }
    else{
        node *p_temp = p_start;
        while (p_temp->p_next != 0) {
          p_temp = p_temp->p_next;
        }
        p_temp->p_next = new_node;
        tamanho += 1;
    }
}

template<typename T>
void MyList<T>::excluir2(T dato){
  if(p_start != 0){
    node *p_node = p_start;
    node *p_temp;
    for (int i=0; i<tamanho;i++) {
      if(p_node->cont == dato){
        if(i==0){
            p_start = p_node->p_next;
        }
        else{
            p_temp->p_next = p_node->p_next;
            p_node = p_node->p_next;
            if(i==tamanho-1){
                p_insert = p_temp;
            }
        }

        //cout<<"Eliminado:"<<endl;
        tamanho -=1;
        break;
      }
      else{
        p_temp = p_node;
        p_node = p_node->p_next;
      }
    }
  }
  else{
    cout<<"Lista vacia"<<endl;
  }
}

template<typename T>
void MyList<T>::excluir(T dato){
  node *p_ante;
  node * p_temp = p_start;

  if(p_start != 0){
    while (p_temp != 0) {
      if(p_temp->cont == dato){
        if(p_temp == p_start)
          p_start = p_start->p_next;
        else
          p_ante->p_next = p_temp->p_next;
        tamanho -=1;
      }
      p_ante = p_temp;
      p_temp = p_temp->p_next;
    }
  }
  else{
    cout<<"Lista vacia"<<endl;
  }
}

template<typename T>
void MyList<T>::myprint(){
  if(p_start != 0){
    cout<<"lista: ";
    node *p_node = p_start;
    while (p_node != 0) {
      cout<<p_node->cont<<" ";
      p_node = p_node->p_next;
    }
    cout<<endl;
  }
  else{
    cout<<"Lista vacia"<<endl;
  }
}

template<typename T>
T MyList<T>::get(int posicao)
{
    node *p_node = p_start;
    for (int i=0; i<posicao; i++) {
        p_node = p_node->p_next;
    }
    return p_node->cont;
}

/** -------- funcoes proprias da classe de ASSUNTO ------  **/
template<typename T>
float MyList<T>::mediaUrgencias(){
    int aux = 0;
    node *p_node = p_start;
    for (int i=0; i<tamanho; i++) {
        aux += p_node->cont.getTipo().getUrgencia();
        p_node = p_node->p_next;
    }
    return aux/tamanho*1.0;
}

template<typename T>
float MyList<T>::mediaDuracaoAtendimento()
{
    float aux = 0.0;
    node *p_node = p_start;
    for (int i=0; i<tamanho; i++) {
        aux += p_node->cont.getDuracaoAtendimento();
        p_node = p_node->p_next;
    }
    return aux/tamanho*1.0;
}

#endif
