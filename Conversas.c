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

Conversa* cria_conversa_privada(Conversa* conversa_pntr, Pessoa* pessoa, int* num_conversaAtual, int num_p) {
	int i, id_1, id_2;
	(*num_conversaAtual)++;
	printf("\n----Insira os IDs das duas pessoas que farao parte da conversa----\n");
	printf("Id 1\n> ");
	scanf("%d", &id_1);
	printf("Id 2\n> ");
	scanf("%d", &id_2);

	//Caso seja um id Falso ou um além do numero de pessoas ele não deixa abrir a mensagem
	if (id_1 > num_p || pessoa[id_1 - 1].valido_p == FALSE) {
		printf("O primeiro ID eh desconhecido\n\n");
		(*num_conversaAtual)--;
		return conversa_pntr;
	}
	else if (id_2 > num_p || pessoa[id_2 - 1].valido_p == FALSE) {
		printf("O segundo ID eh desconhecido\n\n");
		(*num_conversaAtual)--;
		return conversa_pntr;
	}
	else {   // se nenhum dos IDs extrapola a qntd de pessoa ou ja tenha sido removido, ele confere se a conversa ja existe. Conversa 1 e 2/ 2 e 1 sao iguais
		for (i = 0; i < *num_conversaAtual - 1; i++) {
			if (conversa_pntr[i].ID_pessoa1 == id_1 || conversa_pntr[i].ID_pessoa1 == id_2) {
				if (conversa_pntr[i].ID_pessoa2 == id_2 || conversa_pntr[i].ID_pessoa2 == id_1) {
					printf("Conversa ja existente\n\n");
					(*num_conversaAtual)--;
					return conversa_pntr;
				}
			}
		}
	}
	conversa_pntr = (Conversa*)realloc(conversa_pntr, (*num_conversaAtual) * sizeof(Conversa));
	conversa_pntr[(*num_conversaAtual) - 1].ID_conversa = *num_conversaAtual; //identifica o ID da conversa, ou seja, a posição
	//da conversa no vetor de conversas
	conversa_pntr[(*num_conversaAtual - 1)].ID_pessoa1 = id_1;
	conversa_pntr[(*num_conversaAtual - 1)].ID_pessoa2 = id_2;
	conversa_pntr[(*num_conversaAtual) - 1].numMensagens = 0;
	return conversa_pntr;
}

Conversa* cria_conversa_grupo(Conversa* conversa_pntr, Grupo* grupo, int* num_conversaAtual, int num_g) {
	int i, id_1, id_2;
	(*num_conversaAtual)++;
	printf("\n----Insira o ID do grupo----\n> ");
	scanf("%d", &id_1);
	id_2 = -1;
	//Caso seja um id Falso ou um além do numero de pessoas ele não deixa abrir a mensagem
	if (id_1 > num_g || grupo[id_1 - 1].valido_g == FALSE) {
		printf("Grupo nao encontrado\n\n");
		(*num_conversaAtual)--;
		return conversa_pntr;
	}
	else {     //se nenhum dos IDs extrapola a qntd de pessoa ou ja tenha sido removido, ele confere se a conversa ja existe.
		for (i = 0; i < *num_conversaAtual - 1; i++) {
			if (conversa_pntr[i].ID_pessoa1 == id_1) {
				if (id_2 == -1) {
					printf("Essa conversa de grupo ja existe\n\n");
					conversa_pntr = (Conversa*)realloc(conversa_pntr, ((*num_conversaAtual) - 1) * sizeof(Conversa));
					(*num_conversaAtual)--;
					return conversa_pntr;
				}
			}
		}
	}
	conversa_pntr = (Conversa*)realloc(conversa_pntr, (*num_conversaAtual) * sizeof(Conversa));
	conversa_pntr[(*num_conversaAtual) - 1].ID_conversa = *num_conversaAtual; //identifica o ID da conversa, ou seja, a posição
	//da conversa no vetor de conversas
	conversa_pntr[(*num_conversaAtual) - 1].ID_pessoa1 = id_1;
	conversa_pntr[(*num_conversaAtual) - 1].ID_pessoa2 = id_2;  // identifica q se trata de um grupo. OBS: não há ID -1
	conversa_pntr[(*num_conversaAtual) - 1].numMensagens = 0;
	return conversa_pntr;
}

void lista_conversas(Pessoa* pessoa, Grupo* grupo, Conversa* conversa, int num_conversas, int var_controle) {
	int i;
	printf("\n\t    Oquerrr\n");
	imprime_traco();
	printf("|ID\t|Conversa\n");
	imprime_traco();
	if (var_controle < 0) {   //Conversas de grupos
		for (i = 0; i < num_conversas; i++) {
			if (conversa[i].ID_pessoa2 > 0) {
				continue;
			}
			else {
				printf("|%d\t|%s\n", conversa[i].ID_conversa, grupo[conversa[i].ID_pessoa1 - 1].nome_g);
			}
		}
		imprime_traco();
	}
	else { //Conversa de pessoas
		for (i = 0; i < num_conversas; i++) {
			if (conversa[i].ID_pessoa2 < 0) {
				continue;
			}
			else {
				printf("|%d\t|%s - %s\n", conversa[i].ID_conversa, pessoa[conversa[i].ID_pessoa1 - 1].nome_p, pessoa[conversa[i].ID_pessoa2 - 1].nome_p);
			}
		}
		imprime_traco();
	}

}

void envia_mensagem(Mensagens* mensagens_conversa_atual, Conversa* conversas, Grupo* grupos, int num_Mensagens, int ID_conversa) {
	//modificar 
	int ID_remetente = 0, i = 0;
	bool_t confereID = FALSE;
	
	do {
		printf("\n\n0 - Retornar \n- ID do remetente: ");
		scanf("%d", &ID_remetente);

		if(conversas[num_Mensagens].ID_pessoa2 == -1){
			for(i = 0; i < grupos->num_pessoas; i++){
				if(ID_remetente == grupos[conversas[ID_conversa].ID_conversa].npessoa[i]){
					confereID = TRUE;
				}
				else if(ID_remetente == 0){
					break;
				}
			}
			if(ID_remetente == 0){
				break;
			}

			if(confereID == FALSE){
				printf("\n\nID nao encontrado nesse grupo\n\n");
			}
		}
		else {

			if (ID_remetente == conversas[num_Mensagens].ID_pessoa1 || ID_remetente == conversas[num_Mensagens].ID_pessoa2) {
				confereID = TRUE;
			}
			else if(ID_remetente == 0) {
				break;
			}
			else {
				confereID = FALSE;
				printf("\nID nao encontrado nessa conversa\n");
			}

		}

		if(ID_remetente == 0){
			break;
		}

	} while (confereID != TRUE || confereID == 0);

	if (ID_remetente != 0) {

		mensagens_conversa_atual = (Mensagens*)realloc(mensagens_conversa_atual, num_Mensagens * sizeof(Mensagens));
		mensagens_conversa_atual[num_Mensagens].ID_remetente = ID_remetente;
		mensagens_conversa_atual[num_Mensagens].id_c = num_Mensagens;

		printf("\nSua mensagem: ");
		fgets(mensagens_conversa_atual[num_Mensagens].mensagem, LIM_MAX_MSG, stdin);
		remove_enter(mensagens_conversa_atual[num_Mensagens].mensagem);

		mensagens_conversa_atual[num_Mensagens].valido_c = TRUE;
		mensagens_conversa_atual[num_Mensagens].apagavel_c = TRUE;
	}
}

void apaga_mensagem(Mensagens* mensagens_conversa_atual, int num_Mensagens) {
	int ID_mensagem = 0, i = 0;
	bool_t encontrado;

	printf("\n\nInsira o ID da mensagem que deseja apagar: ");
	scanf("%d", &ID_mensagem);

	for (i = 0; i < num_Mensagens; i++) {  //Busca a mensagem no vetor de mensagens da conversa e a marca como invalida
		if (ID_mensagem == mensagens_conversa_atual[i].id_c && mensagens_conversa_atual[i].apagavel_c == TRUE) {
			mensagens_conversa_atual[i].valido_c = FALSE;
			encontrado = TRUE;
			printf("\nMensagem apagada com sucesso!\n");
		}
		else {
			encontrado == FALSE;
		}
	}

	if (encontrado == FALSE) {
		printf("\nEssa mensagem nao existe ou ja nao pode ser apagada\n");
	}
}

void abre_conversa(Conversa* conversa_pntr, Pessoa* pessoas, Grupo* grupos, int num_conversas) {
	int i = 0, j = 0, opcao = 0, ID_conversa = 0;
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
				printf("\n\nConversa nao encontrada!\n\n");
				confereID_Conversa = FALSE;
			}
		}
		if (ID_conversa == 0) { //sai do do-while se ID_conversa == 0;
			break;
		}
	} while (confereID_Conversa != TRUE || confereID_Conversa == 0);

	do{
		if (ID_conversa == 0) {
			break;
		}

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
			envia_mensagem(conversa_pntr[ID_conversa].texto, conversa_pntr, grupos, conversa_pntr[ID_conversa].numMensagens, ID_conversa);
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

	//Define todas as mensagens até então escritas como não-apagáveis
	for (i = 0; i < num_conversas; i++) {
		for (j = 0; j < conversa_pntr[i].numMensagens; j++) {
			conversa_pntr[i].texto[j].apagavel_c = FALSE;
		}
	}
}

void abre_grupo(Grupo* grupos, Conversa* conversas, Pessoa* pessoas, int num_grupos, int num_conversas) {
	int ID_grupo = 0, i = 0, opcao = 0, j = 0;
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
				printf("\nGrupo nao encontrado!\n");
			}
		}
		if (confereID_grupo == 0) {
			break;
		}
	} while (confereID_grupo != TRUE || confereID_grupo != 0);

	do{
		if (confereID_grupo == 0) {
			break;
		}

		grupo_atual = &conversas[ID_grupo]; //coloca o grupo selecionado dentro de uma variavel, pra simplificar

		for (i = 0; i < grupo_atual->numMensagens; i++) { //imprime as mensagens do grupo;
			if (grupo_atual->texto[i].valido_c == TRUE) {
				printf("[%d]-[%s] [%s]\n", grupo_atual->texto[i].id_c, pessoas[grupo_atual->texto[i].ID_remetente].nome_p, grupo_atual->texto[i].mensagem);
			}
		}

		printf("\n0 - Voltar a seçao anterior \n1 - Enviar mensagem \n2 - Apagar mensagem\n");
		scanf("%d", &opcao);

		switch (opcao){
		case 0:
			break;
		case 1:
			envia_mensagem(grupo_atual->texto, conversas, grupos, grupo_atual->numMensagens, ID_grupo);
			break;
		case 2:
			apaga_mensagem(grupo_atual->texto, grupo_atual->numMensagens);
			break;
		default:
			printf("\n\nOpcao nao encontrada!\n\n");
			break;
		}

	} while (opcao != 0);

	//Define todas as mensagens até então escritas como não-apagáveis
	for (i = 0; i < num_conversas; i++) {
		for (j = 0; j < conversas[i].numMensagens; j++) {
			conversas[i].texto[j].apagavel_c = FALSE;
		}
	}
}

Conversa* qual_conversa(Pessoa* pessoas, Grupo* grupo, Conversa* conversa, int* num_conversas, int num_p, int num_g) {
	int opcao;
	printf("\n\t\tOquerrr\n\t\t(Conversas)\n");
	imprime_traco();
	printf("\t1 - Conversa Privada\n\n\t2 - Conversa de Grupo\n\n\t3 - Voltar sessao anterior\n> ");
	scanf("%d%*c", &opcao);
	switch (opcao) {
	case 3:
		break;
	case 1:
		conversa = cria_conversa_privada(conversa, pessoas, num_conversas, num_p);
		break;
	case 2:
		conversa = cria_conversa_grupo(conversa, grupo, num_conversas, num_g);
		break;
	default:
		break;
	}
	return conversa;
}

Conversa * mod_conversas(Pessoa * pessoas, Grupo * grupo, Conversa * conversa, int *num_conversas, int num_p, int num_g) {
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
				conversa = qual_conversa(pessoas, grupo, conversa, num_conversas, num_p, num_g);
				break;
			case 2:
				lista_conversas(pessoas, grupo, conversa, *num_conversas, 1);
				abre_conversa(conversa, pessoas, grupo, *num_conversas);
				break;
			case 3:
				lista_conversas(pessoas, grupo, conversa, *num_conversas, -1);
				abre_grupo(grupo, conversa, pessoas, num_g, *num_conversas);
				break;
			}
		} while (opcao != 4);
	return conversa;
}