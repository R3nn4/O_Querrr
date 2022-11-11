#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Conversas.h"
#include "Pessoas.h"
#include "Grupos.h"
#include "Tipos.h"
#include "funcs_uteis.h"

//As mensagens serão guardadas em um pointer pointer, em que cada posição do primeiro nivel representa uma mensagem
//e cada posição do segundo nível representa a conversa à qual pertencem as mensagens.
//Pra isso serve o ID das conversas: sincronizar cada conversa com seu respectivo pointer de mensagens.


void cria_conversa_privada(Conversa* conversa_pntr, Pessoa * pessoa, int *num_conversaAtual, int num_p) {
	int i;

		conversa_pntr[(*num_conversaAtual)-1].ID_conversa = *num_conversaAtual; //identifica o ID da conversa, ou seja, a posição
																		//da conversa no vetor de conversas 
		printf("\n----Insira os IDs das duas pessoas que farao parte da conversa----\n");
			printf("Id 1\n> ");
			scanf("%d", &(conversa_pntr[(*num_conversaAtual)-1].ID_pessoa1));
			printf("Id 2\n> ");
			scanf("%d", &(conversa_pntr[(*num_conversaAtual)-1].ID_pessoa2));

		conversa_pntr[(*num_conversaAtual)-1].numMensagens = 0;
		//Caso seja um id Falso ou um além do numero de pessoas ele não deixa abrir a mensagem
		if(conversa_pntr[(*num_conversaAtual)-1].ID_pessoa1 > num_p || pessoa[conversa_pntr[(*num_conversaAtual)-1].ID_pessoa1 - 1].valido_p == FALSE){
			printf("O primeiro ID eh desconhecido\n\n");
			conversa_pntr = (Conversa *) realloc(conversa_pntr, ((*num_conversaAtual)-1) * sizeof(Conversa));
			if(conversa_pntr == NULL){
				conversa_pntr = (Conversa *) malloc(1 * sizeof(Conversa));
			}
			(*num_conversaAtual)--;
		} else if(conversa_pntr[(*num_conversaAtual)-1].ID_pessoa2 > num_p || pessoa[conversa_pntr[(*num_conversaAtual)-1].ID_pessoa2 - 1].valido_p == FALSE){
			printf("O segundo ID eh desconhecido\n\n");
			conversa_pntr = (Conversa *) realloc(conversa_pntr, ((*num_conversaAtual)-1) * sizeof(Conversa));
			if(conversa_pntr == NULL){
				conversa_pntr = (Conversa *) malloc(1 * sizeof(Conversa));
			}
			(*num_conversaAtual)--;
		}	else{
			for(i=0; i < *num_conversaAtual - 1; i++){
				if(conversa_pntr[i].ID_pessoa1 == conversa_pntr[(*num_conversaAtual)-1].ID_pessoa1 || conversa_pntr[i].ID_pessoa1 == conversa_pntr[(*num_conversaAtual)-1].ID_pessoa2 ){
					if(conversa_pntr[i].ID_pessoa2 == conversa_pntr[(*num_conversaAtual)-1].ID_pessoa2 || conversa_pntr[i].ID_pessoa2 == conversa_pntr[(*num_conversaAtual)-1].ID_pessoa1){
						printf("Conversa ja existente\n\n");
						conversa_pntr = (Conversa *) realloc(conversa_pntr, ((*num_conversaAtual)-1) * sizeof(Conversa));
						if(conversa_pntr == NULL){
							conversa_pntr = (Conversa *) malloc(1 * sizeof(Conversa));
						}
						(*num_conversaAtual)--;
					}
				}
			}
		}

		conversa_pntr[(*num_conversaAtual) - 1].texto = NULL;
}

void cria_conversa_grupo(Conversa* conversa_pntr, Grupo * grupo, int *num_conversaAtual, int num_g) {
	int i;
		conversa_pntr[(*num_conversaAtual)-1].ID_conversa = *num_conversaAtual; //identifica o ID da conversa, ou seja, a posição
																		//da conversa no vetor de conversas 
		printf("\n----Insira o ID do grupo----\n> ");
		scanf("%d", &(conversa_pntr[(*num_conversaAtual)-1].ID_pessoa1));
		conversa_pntr[(*num_conversaAtual)-1].ID_pessoa2 = -1;

		conversa_pntr[(*num_conversaAtual)-1].numMensagens = 0;
		//Caso seja um id Falso ou um além do numero de pessoas ele não deixa abrir a mensagem
		if(conversa_pntr[(*num_conversaAtual)-1].ID_pessoa1 > num_g || grupo[conversa_pntr[(*num_conversaAtual)-1].ID_pessoa1 - 1].valido_g == FALSE){
			printf("Grupo nao encontrado\n\n");
			conversa_pntr = (Conversa *) realloc(conversa_pntr, ((*num_conversaAtual)-1) * sizeof(Conversa));
			if(conversa_pntr == NULL){
				conversa_pntr = (Conversa *) malloc(1 * sizeof(Conversa));
			}
			(*num_conversaAtual)--;
		} else{
			for(i=0; i < *num_conversaAtual - 1; i++){
				if(conversa_pntr[i].ID_pessoa1 == conversa_pntr[(*num_conversaAtual)-1].ID_pessoa1){
					if(conversa_pntr[i].ID_pessoa2 == -1){
						printf("Conversa ja existente\n\n");
						conversa_pntr = (Conversa *) realloc(conversa_pntr, ((*num_conversaAtual)-1) * sizeof(Conversa));
						if(conversa_pntr == NULL){
						conversa_pntr = (Conversa *) malloc(1 * sizeof(Conversa));
						}
						(*num_conversaAtual)--;
					}
				}
			}
		}
}

void envia_mensagem(Mensagens* mensagens_conversa_atual, Conversa* conversas, int num_Mensagens) {
	//modificar 
	int ID_remetente = 0;
	bool_t confereID = FALSE;
	
	do {
		printf("\n\n0 - Retornar \n- ID do remetente: ");
		scanf("%d", &ID_remetente);

		if (ID_remetente == conversas[num_Mensagens].ID_pessoa1 || ID_remetente == conversas[num_Mensagens].ID_pessoa2) {
			confereID = TRUE;
		}
		else if(ID_remetente == 0) {
			break;
		}
		else {
			confereID = FALSE;
			printf("ID nao encontrado nessa conversa\n");
		}
		
	} while (confereID != TRUE || confereID == 0);

	mensagens_conversa_atual = (Mensagens*)realloc(mensagens_conversa_atual, num_Mensagens * sizeof(Mensagens));
	mensagens_conversa_atual[num_Mensagens].ID_remetente = ID_remetente;
	mensagens_conversa_atual[num_Mensagens].id_c = num_Mensagens;
	
	printf("\nSua mensagem: ");
	fgets(mensagens_conversa_atual[num_Mensagens].mensagem, LIM_MAX_MSG, stdin);
	remove_enter(mensagens_conversa_atual[num_Mensagens].mensagem);

	mensagens_conversa_atual[num_Mensagens].valido_c = TRUE;
	mensagens_conversa_atual[num_Mensagens].apagavel_c = TRUE;
}

void apaga_mensagem(Mensagens* mensagens_conversa_atual, int num_Mensagens) {
	int ID_mensagem = 0, i = 0;

	printf("\n\nInsira o ID da mensagem que deseja apagar: ");
	scanf("%d", &ID_mensagem);

	for (i = 0; i < num_Mensagens; i++) {  //Busca a mensagem no vetor de mensagens da conversa e a marca como invalida
		if (ID_mensagem == mensagens_conversa_atual[i].id_c && mensagens_conversa_atual[i].apagavel_c == TRUE) {
			mensagens_conversa_atual[i].valido_c = FALSE;
		}
		else {
			printf("\nMensagem nao encontrada.\n");
		}
	}
}

void abre_conversa(Conversa* conversa_pntr, Pessoa* pessoas, int num_conversas) {
	int i = 0, opcao = 0, ID_conversa = 0;
	bool_t confereID_Conversa;

	do {
		printf("\n0 - Voltar a seçao anterior \nInsira o ID da conversa que deseja abrir: ");
		scanf("%d", &ID_conversa);

		for (i = 0; i < num_conversas; i++) {  //Confere se o ID inserido pela pessoa é valido;
			if (ID_conversa == conversa_pntr[i].ID_conversa) {
				confereID_Conversa = TRUE;
			}
			else if (ID_conversa == 0) {
				break;
			}
			else {
				printf("Conversa nao encontrada!");
				confereID_Conversa = FALSE;
			}
		}
		if (ID_conversa == 0) { //sai do do-while se ID_convers == 0;
			break;
		}
	} while (confereID_Conversa != TRUE || confereID_Conversa == 0);

	if (ID_conversa == 0) {
		break;
	}

	do{
		for (i = 0; i <= conversa_pntr[ID_conversa].numMensagens; i++) {  //Imprime as mensagens passadas dessa conversa
			if (conversa_pntr[ID_conversa].texto[i].valido_c == TRUE) {
				printf("[%d]-[%s] %s\n", conversa_pntr[ID_conversa].texto[i].id_c, pessoas[conversa_pntr[ID_conversa].texto[i].ID_remetente].nome_p, conversa_pntr[ID_conversa].texto[i].mensagem);
			}
		}

		printf("\n\n1 - Enviar mensagem \n2 - Apagar mensagem \n3 - Voltar\n\n");
		scanf("%d", &opcao);

		switch (opcao) {
		case 1:
			conversa_pntr[ID_conversa].numMensagens++;
			conversa_pntr[ID_conversa].texto = mensagens[ID_conversa];
			envia_mensagem(conversa_pntr[ID_conversa].texto, conversa_pntr, conversa_pntr[ID_conversa].numMensagens);
			break;
		case 2:
			apaga_mensagem(conversa_pntr[ID_conversa].texto, conversa_pntr[ID_conversa].numMensagens);
			break;
		case 3:
			break;
		default:
			printf("\nOpcao nao encontrada!\n");
			break;
		}

	} while (opcao != 0);

	if (opcao == 3) {
		break;
	}
}

void abre_grupo(Grupo* grupos, Conversa* conversas, Pessoa* pessoas, int num_grupos) {
	int ID_grupo = 0, i = 0, opcao = 0;
	bool_t confereID_grupo;
	Conversa* grupo_atual;

	do {
		printf("\n\t0 - Voltar a seçao anterior \nInsira o ID do grupo que deseja abrir: ");
		scanf("%d", &ID_grupo);

		for (i = 0; i < num_grupos; i++) {
			if (ID_grupo == grupos[i].id_g) {
				confereID_grupo == TRUE;
			}
			else if (confereID_grupo == 0) {
				break;
			}
			else {
				printf("Grupo nao encontrado!\n");
			}
		}
		if (confereID_grupo == 0) {
			break;
		}
	} while (confereID_grupo != TRUE || confereID_grupo != 0);

	if (confereID_grupo == 0) {
		break;
	}

	do{
		grupo_atual = &conversas[ID_grupo]; //coloca o grupo selecionado dentro de uma variavel, pra simplificar

		for (i = 0; i < *grupo_atual->numMensagens; i++) {
			if (*grupo_atual->texto[i].valido_c == TRUE) {
				printf("[%d]-[%s] [%s]\n", grupo_atual->texto[i].id_c, pessoas[grupo_atual->texto[i].ID_remetente].nome_p, grupo_atual->texto[i].mensagem *);
			}
		}

		printf("0 - Voltar a seçao anterior \n1 - Enviar mensagem \n2 - Apagar mensagem");
		scanf("%d", &opcao);

		switch (opcao){
		case 0:
			break;
		case 1:
			//Modificar envia_mensagem;
			break;
		case 2:
			//Modificar apaga_mensagem;
			break;
		default:
			printf("Opcao nao encontrada!");
			break;
		}

	} while (opcao != 0);

	if (opcao == 0) {
		break;
	}
}

void qual_conversa(Pessoa * pessoas, Grupo *grupo, Conversa * conversa, int *num_conversas, int num_p, int num_g){
	int opcao;
		printf("\n\t\tOquerrr\n\t\t(Conversas)\n");
		imprime_traco();
		printf("\t1 - Conversa Privada\n\n\t2 - Conversa de Grupo\n\n\t3 - Voltar sessao anterior\n> ");
		scanf("%d%*c", &opcao);
			switch (opcao){
				case 3:
					break;
				case 1:
					cria_conversa_privada(conversa, pessoas, num_conversas, num_p);
					break;
				case 2:
					cria_conversa_grupo(conversa, grupo, num_conversas, num_g);
				break;
				default:
					break;
			}
}

Conversa * mod_conversas(Pessoa * pessoas, Grupo *grupo, Conversa * conversa, int *num_conversas, int num_p, int num_g) {
	int opcao = 0;

		do {
			printf("\n\t\tOquerrr\n\t\t(Conversas)\n");
			imprime_traco();
			printf("\t1 - Criar Conversa\n\n\t2 - Abrir Conversa Privada\n\n\t3 - Abrir Grupo\n\n\t4 - Voltar sessao anterior\n> ");
			scanf("%d%*c", &opcao);
			switch(opcao) {
			case 4:
				break;
			case 1: 
				(*num_conversas)++;
				conversa = (Conversa*) realloc(conversa, (*num_conversas) * sizeof(Conversa));
				qual_conversa(pessoas,grupo,conversa,num_conversas, num_p, num_g);
				break;
			case 2:
				abre_conversa(conversa, *num_conversas);
				break;
			case 3:
				abre_grupo(grupo, num_g);
				break;
			}
		} while (opcao != 4);
	return conversa;
}