#ifndef SERVICIOATENDIMIENTO_H
#define SERVICIOATENDIMIENTO_H

#include "atendimento.h"
#include "Estructuras/myheap.h"
#include "Estructuras/mylist.h"
#include "Estructuras/myhash.h"
#include <time.h>   // rand, get Time Current
#include <sstream>  //Convert int to string
#include <iostream>
#include <stdlib.h> /* srand, rand */

using namespace std;

#define MAX_SIZE_LIST 10
#define GRAU_URGENCIA 10

class servicioAtendimento
{
  private:
    TipoAssunto *listaTipoAssunto;
    MyHash listaEncerrar;
    MyList<Atendimento> listaAtendimento;
    // MyHeap heapAtendimento;

  public:

    servicioAtendimento();
    void imprimirListaTipoAtendimento();
    void imprimirListaAtendimento();
    void recepcionar(Cliente, MyList<Assunto>);
    Atendimento atender();
    void encerrar(Atendimento &atendimento);
    void gerarEstatistica();

    MyList<Assunto> gerarListaAssunto(int);
    void menu();

    // inline void mostrarHeapAtenimento(){ heapAtendimento.mostrarHeap(); }
};

#endif // SERVICIOATENDIMIENTO_H
