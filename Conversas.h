#pragma once
#ifndef __conversas_h__
#define __conversas_h__

#include "Pessoas.h"
#include "Grupos.h"
#include "Tipos.h"

typedef struct MENSAGENS{
   int id_c;
   int ID_remetente;
   char mensagem[LIM_MAX_MSG]; 
   bool_t valido_c;
   bool_t apagavel_c;
}Mensagens;

typedef struct CONVERSAS{
	int ID_conversa;
	int ID_pessoa1;
	int ID_pessoa2;
	int numMensagens;
	Mensagens *texto;
}Conversa;


Conversa * mod_conversas(Pessoa * pessoas, Grupo *grupo, Conversa * conversa, Mensagens ** mensagens, int *num_conversas, int num_p, int num_g);

#endif //__conversas_h__