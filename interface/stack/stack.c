#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

lista_sequencial* alocar_dinamicamente_uma_lista_sequencial(int capacidade){
	lista_sequencial* a = (lista_sequencial*)malloc(sizeof(lista_sequencial));
	a->vetor = (coordenada*)malloc(sizeof(coordenada)*capacidade);
	a->capacidade = capacidade;
	a->tamanho = 0;
	return a;	
}

void aumentar_a_capacidade_da_lista_sequencial(lista_sequencial* lista, int nova_capacidade){
	coordenada* copia_do_vetor = lista->vetor;
	lista->vetor = (coordenada*)realloc(lista->vetor, sizeof(coordenada)*nova_capacidade);
	lista->capacidade = nova_capacidade;
}

void diminuir_a_capacidade_da_lista_sequencial(lista_sequencial* lista, int nova_capacidade){
	lista->vetor = (coordenada*)realloc(lista->vetor, sizeof(coordenada)*nova_capacidade);
	lista->capacidade = nova_capacidade;
}

void inseir_coordenada_na_lista_sequencial(lista_sequencial* lista, int* total_de_alocacoes_de_memoria, 
	int coordenada_x_1, int coordenada_y_1){
	int copia_do_tamanho = lista->tamanho;
	if(copia_do_tamanho == lista->capacidade){
		aumentar_a_capacidade_da_lista_sequencial(lista, lista->capacidade*2);
		*total_de_alocacoes_de_memoria+=1;
	}
	lista->vetor[copia_do_tamanho].coordenada_x_1 = coordenada_x_1;
	lista->vetor[copia_do_tamanho].coordenada_y_1 = coordenada_y_1;
	lista->tamanho+=1;
}

void remover_coordenada_da_lista_sequencial(lista_sequencial* lista, int* total_de_desalocacoes_de_memoria){
	if(lista->tamanho == lista->capacidade/3) {
		diminuir_a_capacidade_da_lista_sequencial(lista, lista->capacidade/2);
		*total_de_desalocacoes_de_memoria+=1;
	}
	lista->tamanho-=1;
}

void desalocar_dinamicamente_lista_sequencial(lista_sequencial* lista){
	free(lista->vetor);
	free(lista);
}
