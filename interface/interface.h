#ifndef INTERFACE_H
#define INTERFACE_H

#define cor int
#define preto 0
#define azul 1
#define verde 2
#define ciano 3
#define vermelho 4
#define roxo 5
#define amarelo 6
#define cinza_claro 7
#define cinza_escuro 8
#define azul_brilhante 9
#define verde_brilhante 10
#define ciano_brilhante 11
#define vermelho_brilhante 12
#define roxo_brilhante 13
#define amarelo_brilhante 14
#define branco 15

#define sentido int
#define cima 0
#define direita 1
#define esquerda 2
#define baixo 3

void reposicionar_indicador_do_console(int coordenada_x, int coordenada_y);
void alterar_a_cor(cor cor_do_texto, cor cor_da_celula);
void alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(int vizibilidade, int tamanho);
void desenhar_bordas_da_matriz(int apagar_bordas, int coordenada_x, int coordenada_y, int largura, int altura, 
	char caractere_utilizado_nas_bordas, cor cor_das_bordas);
int converter_string_para_int(char string[], int tamanho);
int inserir_e_analisar_entrada_do_usuario(int coordenada_x, int coordenada_y, int limite_da_analise_na_string);
void desenhar_retangulo(int coordenada_x_1, int coordenada_y_1, int coordenada_x_2, int coordenada_y_2, cor cor_do_marcador, 
	char caractere_utilizado_nas_paredes);
void desenhar_menu_de_selecao_de_cores(int coordenada_x, int coordenada_y, int condicao_para_mostrar_barras_verticais);
void mostrar_opcao_atual_no_menu_de_selecao_de_cores(int coordenada_x, int coordenada_y, int cor_atual, int apagar, 
	int condicao_para_considerar_a_cor_preta);
void imprimir_string_desligado_ou_ligado(int coordenada_x, int coordenada_y, int condicional, cor cor_de_texto_ligado, 
	cor cor_de_fundo_ligado, cor cor_do_texto_desligado, cor cor_de_fundo_desligado);
void desenhar_ou_apagar_o_aviso_sobre_problemas_visuais_entre_matriz_e_labirinto(int coordenada_x, int coordenada_y, 
	int condicao_para_apagar_texto);
int desenhar_seta(int coordenada_x, int coordenada_y, int* opcao_escolhida, int opcao_escolhida_auxiliar, 
	int limite_de_opcoes_vertical, int limite_de_opcoes_horizontal, int* botao_enter_acionado, int* botao_esc_acionado, 
	int condicao_para_navegar_no_menu_usando_as_setas, int condicao_para_voltar_no_menu_usando_a_seta_esquerda, 
	int condicao_para_voltar_no_menu_usando_a_seta_direita, int condicao_para_considerar_a_cor_preta);
void inserir_dados(int coordenada_x_menu_principal, int coordenada_y_menu_principal, int opcao_escolhida, int largura_minima, 
	int largura_maxima, int altura_minima, int altura_maxima, int* largura_atual, int* altura_atual, 
	cor* cor_do_retangulo_inicial, cor* cor_do_retangulo_final, cor* cor_das_paredes_intermediarias, 
	cor* cor_das_paredes_intermediarias_segunda_passada, cor* cor_das_bordas, char* caractere_utilizado_nas_bordas, 
	char* caractere_utilizado_nas_paredes, int* sleep, int* coordenada_x_inicio_1, int* coordenada_y_inicio_1, 
	int* coordenada_x_inicio_2, int* coordenada_y_inicio_2, int* coordenada_x_fim_1, int* coordenada_y_fim_1, 
	int* coordenada_x_fim_2, int* coordenada_y_fim_2, int* mostrar_matriz, int* mostrar_tamanho_da_pilha, 
	int* mostrar_capacidade_da_pilha, int* mostrar_coordenada_atual, int* mostrar_valor_da_variavel_sleep, 
	int* mostrar_total_de_alocacoes_e_desalocacoes, int* mostrar_total_de_possibilidades_analisadas, 
	int* confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto);
sentido decidir_caminho_a_ser_tomado(int** matriz, int coordenada_x, int coordenada_y, int largura, int altura, 
	int vetor_de_possibilidades[], int* primeira_execulcao_da_funcao, 
	int* total_de_possibilidades_analisadas_na_movimentacao_do_labirinto);
void desenhar_menu_principal(int coordenada_x_menu_principal, int coordenada_y_menu_principal, int largura_minima, 
	int largura_maxima, int altura_minima, int altura_maxima, int largura_atual, int altura_atual, int coordenada_x_inicio_1, 
	int coordenada_y_inicio_1, int coordenada_x_inicio_2, int coordenada_y_inicio_2, int coordenada_x_fim_1, int coordenada_y_fim_1, int coordenada_x_fim_2, 
	int coordenada_y_fim_2);

#endif
