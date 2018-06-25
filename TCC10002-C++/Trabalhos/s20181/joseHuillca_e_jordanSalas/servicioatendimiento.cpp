#include "servicioatendimiento.h"

servicioAtendimento::servicioAtendimento()
{
  // Random
  srand (time(NULL));

  // Create list listaTipoAssunto
  listaTipoAssunto = new TipoAssunto[MAX_SIZE_LIST];
  for(int i=0; i<MAX_SIZE_LIST; i++){
    ostringstream str1;
    str1<<i+1;
    int urgenciaRand = rand() % GRAU_URGENCIA + 1;
    TipoAssunto tipoAsuntoTemporal(i+1, "Asunto "+str1.str(), urgenciaRand);
    listaTipoAssunto[i] = tipoAsuntoTemporal;
  }

  listaEncerrar = MyHash(MAX_SIZE_LIST);
}

void servicioAtendimento::imprimirListaTipoAtendimento()
{
  for(int i=0; i<MAX_SIZE_LIST; i++){
    cout<<"Tipo Assunto: "<<listaTipoAssunto[i].getTitulo()<<
          " // urgencia: "<<listaTipoAssunto[i].getUrgencia()<<
       "// tipo-id: "<<listaTipoAssunto[i].getTipo()<<endl;
  }
  cout<<endl;
}

void servicioAtendimento::encerrar(Atendimento &atendimento)
{
    time_t tempoProvidencias;

    int num_assuntos = atendimento.getAssuntos().getTamanho();
    string aux_providencia;
    double horaInicio = atendimento.getHoraAtendimento();

    ostringstream str0;
    str0<<num_assuntos;
    cout<<" providências tomadas para atender as "<< str0.str() <<" demandas dos clientes: "<<endl;
    for(int i=0; i<num_assuntos; i++){
        ostringstream str1;
        str1<<i+1;
        cout<<" Asunto " + str1.str()<<" - Providencias: ";
        cin>>aux_providencia;

        Assunto assunto = atendimento.getAssuntos().get(i);
        assunto.setProvidencias(aux_providencia);
        time(&tempoProvidencias);
        double duracaoAtendimento = tempoProvidencias-horaInicio;
        ostringstream str2;
        str2<<assunto.getTipo().getTipo();
        cout<<" tempo de Assunto de tipo("<<str2.str()<<"): "<<duracaoAtendimento<<" segundos"<<endl<<endl;
        assunto.setDuracaoAtendimento(duracaoAtendimento);
        horaInicio += duracaoAtendimento;
        listaEncerrar.inserir(assunto.getTipo().getTipo(), assunto);
    }
    cout<<"Excluyendo de lista de atendimento";
    listaAtendimento.excluir(atendimento);
    cout<<"..."<<endl;
}

void servicioAtendimento::gerarEstatistica()
{
    cout<<" | --- Gerando estatísticas da minha listaEncerrar: --- |"<<endl;
    for(int i=1; i<=listaEncerrar.getTamanho();i++){
        ostringstream str1;
        str1<<i;
        float mediaAtendimento = 0.0;
        if(!listaEncerrar.get(i).estaVazio()){
            mediaAtendimento = listaEncerrar.get(i).mediaDuracaoAtendimento();
            cout<<" TipoAssunto " + str1.str() + " : "<<mediaAtendimento<< " segundos" <<endl;
        }else{
            cout<<" TipoAssunto " + str1.str() + " : -- " <<endl;
        }

    }
}

void servicioAtendimento::recepcionar(Cliente cliente_, MyList<Assunto> listaAssunto_)
{
  time_t tempoAgora;
  time(&tempoAgora);

  Atendimento Objeto_Atendimento(cliente_, listaAssunto_, tempoAgora);
  listaAtendimento.inserir(Objeto_Atendimento);
}

MyList<Assunto> servicioAtendimento::gerarListaAssunto(int cantidade)
{
  MyList<Assunto> lista_Assunto;
  for(int i=0; i<cantidade; i++){
    ostringstream str1;
    str1<<i+1;
    int tipoAssuntoRand = rand() % MAX_SIZE_LIST;
    Assunto Objecto_Assunto(listaTipoAssunto[tipoAssuntoRand], "testDescripcion "+str1.str());
    lista_Assunto.inserir(Objecto_Assunto);
  }
  return lista_Assunto;
}

Atendimento servicioAtendimento::atender()
{
  time_t tempoAgora;
  time(&tempoAgora);
  MyHeap heapTemporal;
  // Create Heap
  int tamanhoLista = listaAtendimento.getTamanho();
  for(int i=0; i<tamanhoLista; i++){
    Atendimento Objecto_Atendimento = listaAtendimento.get(i);
    Objecto_Atendimento.setHoraAtendimento(tempoAgora);
    Objecto_Atendimento.calcularPrioridade();
    heapTemporal.inserir(Objecto_Atendimento);
  }
  // Get max prioridade
  Atendimento atendimentoAtender = heapTemporal.excluir();
  return atendimentoAtender;
}

void servicioAtendimento::menu()
{
  int opcao;
  int cpf;
  int numeroAssuntos;
  string nome;

  do{
    cout<<endl<<" |------------------------------------------------------|"<<endl;
    cout<<" |                 SERVICO ATENDIMENTO                  |"<<endl;
    cout<<" |------------------------------------------------------|"<<endl<<endl;
    cout<<" 1 - Recepcionar"<<endl;
    cout<<" 2 - Atender e Encerrar"<<endl;
    cout<<" 3 - Gerar Estatistica"<<endl;
    cout<<" 0 - Sair"<<endl;
    cout<<" Clientes a espera: "<<listaAtendimento.getTamanho()<<endl;
    cout<<" Opcao: ";
    cin>>opcao;
    cout<<endl;
    switch(opcao)
    {
    case 1:
    {
        cout<<" Nome: ";
        cin>>nome;
        cout<<" CPF: ";
        cin>>cpf;
        cout<<" Numeros de assuntos: ";
        cin>>numeroAssuntos;
        recepcionar(Cliente(cpf, nome), gerarListaAssunto(numeroAssuntos));
        cout<<" |-------------- Atendimento Recepcionado --------------|"<<endl;
        break;
    }
    case 2:
    {
        if(listaAtendimento.getTamanho()==0){
            cout<<" Nenhum cliente esperando..."<<endl;
        }else{
            cout<<" |------------------ Atendendo Cliente -----------------|"<<endl;
            Atendimento Objeto_Atendimento = atender();
            string nomeCliente = Objeto_Atendimento.getCliente().getNome();
            float prioridadeCliente = Objeto_Atendimento.getPrioridade();
            int idade = Objeto_Atendimento.getCliente().getIdade();
            cout<<" Cliente: "<<nomeCliente<<endl;
            cout<<" Idade: "<<idade<<endl;
            cout<<" Prioridade: "<<prioridadeCliente<<endl<<endl;
            cout<<" |--------------- Encerrando Atendimento ---------------|"<<endl;
            encerrar(Objeto_Atendimento);
        }
        break;
    }
    case 3:
    {
        if(listaEncerrar.getTamanho()==0){
            cout<<" Nenhum cliente foi atendido..."<<endl;
        } else
            gerarEstatistica();
        break;
    }
    default:
        break;
    }
  } while(opcao != 0);
}


int main(){
  servicioAtendimento Objeto_SA;
  Objeto_SA.menu();

  //Objeto_SA.imprimirListaTipoAtendimento();
  cout<<"Termino todo"<<endl;
  return 0;
}
