#ifndef ATENDIMIENTO_H
#define ATENDIMIENTO_H

#include "cliente.h"
#include "assunto.h"
#include "Estructuras/mylist.h"

#define MAX_IDADE 65.0
#define MAX_MINUTOS 15.0
#define MAX_GRAU_URGENCIA 10.0

class Atendimento
{
private:
    Cliente cliente;
    MyList<Assunto> assuntos;
    double horaChegada;
    double horaAtendimento;
    float prioridade;
public:
    Atendimento(){}
    Atendimento(Cliente cliente_, MyList<Assunto> assuntos_, double horaChegada_) {
        cliente = cliente_;
        assuntos = assuntos_;
        horaChegada = horaChegada_;
        horaAtendimento = 0;
    }

    inline Cliente getCliente(){return cliente;}
    inline MyList<Assunto> getAssuntos(){return assuntos;}
    inline double getHoraChegada(){return horaChegada;}
    inline double getHoraAtendimento(){return horaAtendimento;}
    inline float getPrioridade(){return prioridade;}

    inline void setHoraChegada(double horaChegada_){horaChegada = horaChegada_;}
    inline void setHoraAtendimento(double horaAtendimento_){horaAtendimento = horaAtendimento_;}

    // Tiempo de espera esta en MINUTOS
    void calcularPrioridade(){
        float edade_media = cliente.getIdade()/MAX_IDADE;
        float espera_media = converterEmMinunutos(horaAtendimento-horaChegada)/MAX_MINUTOS;
        float assuntos_media = assuntos.mediaUrgencias()/MAX_GRAU_URGENCIA;

        prioridade = (edade_media+espera_media+assuntos_media)/3.0;
    }

    // o tempo sera em segundos
    float  converterEmMinunutos(float tempo){
        return tempo/60.0;
    }

    bool operator ==(Atendimento atendimentoX){
        if(this->getCliente().getCpf() == atendimentoX.getCliente().getCpf()){
            return true;
        }
        return false;
    }
};

#endif // ATENDIMIENTO_H
