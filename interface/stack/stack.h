#ifndef PILHA_H
#define PILHA_H

typedef struct{
	int coordenada_x_1;
	int coordenada_y_1;
} coordenada;

typedef struct{
	coordenada* vetor;
	int tamanho;
	int capacidade;
} lista_sequencial;

lista_sequencial* alocar_dinamicamente_uma_lista_sequencial(int capacidade);
void aumentar_a_capacidade_da_lista_sequencial(lista_sequencial* lista, int nova_capacidade);
void diminuir_a_capacidade_da_lista_sequencial(lista_sequencial* lista, int nova_capacidade);
void inseir_coordenada_na_lista_sequencial(lista_sequencial* lista, int* total_de_alocacoes_de_memoria, 
	int coordenada_x_1, int coordenada_y_1);
void remover_coordenada_da_lista_sequencial(lista_sequencial* lista, int* total_de_desalocacoes_de_memoria);
void desalocar_dinamicamente_lista_sequencial(lista_sequencial* lista);

#endif