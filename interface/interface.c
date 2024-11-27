#include "interface.h"
#include "stack/stack.h" 
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

void reposicionar_indicador_do_console(int coordenada_x, int coordenada_y){
	COORD coordenada = {coordenada_x, coordenada_y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenada);
}

void alterar_a_cor(cor cor_do_texto, cor cor_da_celula){
	WORD palavra = ((cor_da_celula & 0x0f) << 4) + (cor_do_texto & 0x0f);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), palavra); 
}

void alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(int tamanho, int vizibilidade){
	CONSOLE_CURSOR_INFO a = {tamanho, vizibilidade};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
}

void desenhar_bordas_da_matriz(int apagar_bordas, int coordenada_x, int coordenada_y, int largura, int altura, 
	char caractere_utilizado_nas_bordas, cor cor_das_bordas){
	int coordenada_y_backup = coordenada_y, coordenada_x_backup = coordenada_x;
	largura+=2;
	altura+=2;
	char caractere_1, caractere_2, caractere_3, caractere_4, caractere_5, caractere_6, caractere_7, caractere_8;
	if(apagar_bordas == 1){
		caractere_1 = caractere_2 = caractere_3 = caractere_4 = caractere_5 = caractere_6 = 0;
		alterar_a_cor(preto, preto);
	}else{
		if(caractere_utilizado_nas_bordas == -60){
			caractere_1 = 218; caractere_2 = 179; caractere_3 = 192; caractere_4 = 196; caractere_5 = 217; caractere_6 = 191;	
		}else if(caractere_utilizado_nas_bordas == -51){
			caractere_1 = 201; caractere_2 = 186; caractere_3 = 200; caractere_4 = 205; caractere_5 = 188; caractere_6 = 187;
		}else if(caractere_utilizado_nas_bordas == -80){
			caractere_1 = caractere_2 = caractere_3 = caractere_4 = caractere_5 = caractere_6 = -80;
		}else if(caractere_utilizado_nas_bordas == -79){
			caractere_1 = caractere_2 = caractere_3 = caractere_4 = caractere_5 = caractere_6 = -79;
		}else if(caractere_utilizado_nas_bordas == -78){
			caractere_1 = caractere_2 = caractere_3 = caractere_4 = caractere_5 = caractere_6 = -78;
		}else if(caractere_utilizado_nas_bordas == -37){
			caractere_1 = caractere_2 = caractere_3 = caractere_4 = caractere_5 = caractere_6 = -37;
		}else{
			caractere_1 = caractere_2 = caractere_3 = caractere_4 = caractere_5 = caractere_6 = caractere_utilizado_nas_bordas;
		}
		alterar_a_cor(cor_das_bordas, preto);
	}
	reposicionar_indicador_do_console(coordenada_x, coordenada_y);
	printf("%c", caractere_1);
	for(int k=0; k<altura-2; k++){
		coordenada_y++;
		reposicionar_indicador_do_console(coordenada_x, coordenada_y);
		printf("%c", caractere_2);
	}
	coordenada_y++;
	reposicionar_indicador_do_console(coordenada_x, coordenada_y);
	printf("%c", caractere_3);
	for(int k=0; k<largura-2; k++){
		coordenada_x++;
		reposicionar_indicador_do_console(coordenada_x, coordenada_y);
		printf("%c", caractere_4);
	}
	coordenada_x++;
	reposicionar_indicador_do_console(coordenada_x, coordenada_y);
	printf("%c", caractere_5);
	for(int k=coordenada_y; k>coordenada_y_backup+1; k--){
		coordenada_y--;
		reposicionar_indicador_do_console(coordenada_x, coordenada_y);
		printf("%c", caractere_2);
	}
	coordenada_y--;
	reposicionar_indicador_do_console(coordenada_x, coordenada_y);
	printf("%c", caractere_6);
	for(int k=coordenada_x; k>coordenada_x_backup+1; k--){
		coordenada_x--;
		reposicionar_indicador_do_console(coordenada_x, coordenada_y);
		printf("%c", caractere_4);
	}
	alterar_a_cor(branco, preto);
}

int converter_string_para_int(char string[], int tamanho){
	int resultado = 0;
	for(int k=0; string[k] && k<tamanho; k++) resultado = resultado*10 + string[k] - '0';
	return resultado;
}

int inserir_e_analisar_entrada_do_usuario(int coordenada_x, int coordenada_y, int limite_da_analise_na_string){
	int contador = 0;
	char entrada_de_um_caractere = '\0', valor_numerico_final[3];
	valor_numerico_final[0] = '\0'; valor_numerico_final[1] = '\0'; valor_numerico_final[2] = '\0';
	reposicionar_indicador_do_console(coordenada_x, coordenada_y);
	while(entrada_de_um_caractere != 13){
		entrada_de_um_caractere = getch();
		if(valor_numerico_final[0] == '\0' && entrada_de_um_caractere == 13){
			reposicionar_indicador_do_console(coordenada_x, coordenada_y);
			return -1;
		}else if(entrada_de_um_caractere >= '0' && entrada_de_um_caractere <= '9' && contador < limite_da_analise_na_string){
			printf("%c", entrada_de_um_caractere);
			valor_numerico_final[contador] = entrada_de_um_caractere;
			contador++; coordenada_x++;
		}else if(entrada_de_um_caractere == '\b' && contador > 0){
			reposicionar_indicador_do_console(coordenada_x-1, coordenada_y);
			printf(" ");
			coordenada_x--;
			reposicionar_indicador_do_console(coordenada_x, coordenada_y);
			valor_numerico_final[contador-1] = '\0';
			contador--;
		}else if(entrada_de_um_caractere == 27){
			return-1;
		}
	}
	return converter_string_para_int(valor_numerico_final, limite_da_analise_na_string);
}

int desenhar_seta(int coordenada_x, int coordenada_y, int* opcao_escolhida, int opcao_escolhida_auxiliar, 
	int limite_de_opcoes_vertical, int limite_de_opcoes_horizontal, int* botao_enter_acionado, int* botao_esc_acionado, 
	int condicao_para_navegar_no_menu_usando_as_setas, int condicao_para_voltar_no_menu_usando_a_seta_esquerda, 
	int condicao_para_voltar_no_menu_usando_a_seta_direita, int condicao_para_considerar_a_cor_preta){
	reposicionar_indicador_do_console(coordenada_x+opcao_escolhida_auxiliar*6, coordenada_y+*opcao_escolhida);
	printf("->");
	int nova_opcao_escolhida = getch();
	if(nova_opcao_escolhida == 224) nova_opcao_escolhida = getch();
	if(nova_opcao_escolhida == 72){
		nova_opcao_escolhida = *opcao_escolhida-1;
		if(nova_opcao_escolhida < 0 && opcao_escolhida_auxiliar == 3 && condicao_para_considerar_a_cor_preta == 0) 
			nova_opcao_escolhida = limite_de_opcoes_vertical-2;
		else if(nova_opcao_escolhida < 0) nova_opcao_escolhida = limite_de_opcoes_vertical-1;
		reposicionar_indicador_do_console(coordenada_x+opcao_escolhida_auxiliar*6, coordenada_y+*opcao_escolhida);
		printf("  ");
		 *opcao_escolhida = nova_opcao_escolhida;
	}else if(nova_opcao_escolhida == 80){
		nova_opcao_escolhida = *opcao_escolhida+1;
		if(nova_opcao_escolhida == limite_de_opcoes_vertical-1 && opcao_escolhida_auxiliar == 3 && 
			condicao_para_considerar_a_cor_preta == 0) nova_opcao_escolhida = 0;
		else if(nova_opcao_escolhida == limite_de_opcoes_vertical) nova_opcao_escolhida = 0;
		reposicionar_indicador_do_console(coordenada_x+opcao_escolhida_auxiliar*6, coordenada_y+*opcao_escolhida);
		printf("  ");
		*opcao_escolhida = nova_opcao_escolhida;
	}else if(nova_opcao_escolhida == 75 && condicao_para_navegar_no_menu_usando_as_setas == 0){
		nova_opcao_escolhida = opcao_escolhida_auxiliar-1;
		if(nova_opcao_escolhida < 0 && *opcao_escolhida == 3 && condicao_para_considerar_a_cor_preta == 0) 
			nova_opcao_escolhida = limite_de_opcoes_horizontal-2;
		else if(nova_opcao_escolhida < 0) nova_opcao_escolhida = limite_de_opcoes_horizontal-1;
		reposicionar_indicador_do_console(coordenada_x+opcao_escolhida_auxiliar*6, coordenada_y+*opcao_escolhida);
		printf("  ");
		opcao_escolhida_auxiliar = nova_opcao_escolhida;
	}else if(nova_opcao_escolhida == 77 && condicao_para_navegar_no_menu_usando_as_setas == 0){
		nova_opcao_escolhida = opcao_escolhida_auxiliar+1;
		if(nova_opcao_escolhida == limite_de_opcoes_horizontal-1 && *opcao_escolhida == 3 && 
			condicao_para_considerar_a_cor_preta == 0) 
			nova_opcao_escolhida = 0;
		else if(nova_opcao_escolhida == limite_de_opcoes_vertical) nova_opcao_escolhida = 0;
		reposicionar_indicador_do_console(coordenada_x+opcao_escolhida_auxiliar*6, coordenada_y+*opcao_escolhida);
		printf("  ");
		opcao_escolhida_auxiliar = nova_opcao_escolhida;
	}else if(nova_opcao_escolhida == 13 || (nova_opcao_escolhida == 77 && condicao_para_voltar_no_menu_usando_a_seta_direita == 1)){ 
		*botao_enter_acionado = 1;
	}else if(nova_opcao_escolhida == 27 || (nova_opcao_escolhida == 75 && condicao_para_voltar_no_menu_usando_a_seta_esquerda == 1)){ 
		*botao_esc_acionado = 1;
	}
	return opcao_escolhida_auxiliar;
}

void desenhar_retangulo(int coordenada_x_1, int coordenada_y_1, int coordenada_x_2, int coordenada_y_2, cor cor_do_marcador, 
	char caractere_utilizado_nas_paredes){
	reposicionar_indicador_do_console(coordenada_x_1, coordenada_y_1);
	alterar_a_cor(cor_do_marcador, preto);
	printf("%c", caractere_utilizado_nas_paredes);
	reposicionar_indicador_do_console(coordenada_x_2, coordenada_y_2);
	printf("%c", caractere_utilizado_nas_paredes);
	alterar_a_cor(branco, preto);
}

void desenhar_menu_de_selecao_de_cores(int coordenada_x, int coordenada_y, int condicao_para_mostrar_barras_verticais){
	reposicionar_indicador_do_console(coordenada_x, coordenada_y);
	alterar_a_cor(azul, preto);
	printf("   %c%c", 219, 219);
	alterar_a_cor(verde, preto);
	printf("    %c%c", 219, 219);
	alterar_a_cor(ciano, preto);
	printf("    %c%c", 219, 219);
	alterar_a_cor(vermelho, preto);
	printf("    %c%c      ", 219, 219);
	reposicionar_indicador_do_console(coordenada_x, coordenada_y+1);
	alterar_a_cor(roxo, preto);
	printf("   %c%c", 219, 219);
	alterar_a_cor(amarelo, preto);
	printf("    %c%c", 219, 219);
	alterar_a_cor(cinza_claro, preto);
	printf("    %c%c", 219, 219);
	alterar_a_cor(cinza_escuro, preto);
	printf("    %c%c      ", 219, 219);
	reposicionar_indicador_do_console(coordenada_x, coordenada_y+2);
	alterar_a_cor(azul_brilhante, preto);
	printf("   %c%c", 219, 219);
	alterar_a_cor(verde_brilhante, preto);
	printf("    %c%c", 219, 219);
	alterar_a_cor(ciano_brilhante, preto);
	printf("    %c%c", 219, 219);
	alterar_a_cor(vermelho_brilhante, preto);
	printf("    %c%c                                   ", 219, 219);
	reposicionar_indicador_do_console(coordenada_x, coordenada_y+3);
	alterar_a_cor(roxo_brilhante, preto);
	printf("   %c%c", 219, 219);
	alterar_a_cor(amarelo_brilhante, preto);
	printf("    %c%c", 219, 219);
	alterar_a_cor(branco, preto);
	if(condicao_para_mostrar_barras_verticais == 0) printf("    %c%c                                           ", 219, 219);
	else printf("    %c%c   |  |                                    ", 219, 219);
}

void mostrar_opcao_atual_no_menu_de_selecao_de_cores(int coordenada_x, int coordenada_y, int cor_atual, int apagar, 
	int condicao_para_considerar_a_cor_preta){
	char caractere;
	alterar_a_cor(verde_brilhante, preto);
	if(apagar == 1){
		if(condicao_para_considerar_a_cor_preta == 0) caractere = '\0';
		else if(condicao_para_considerar_a_cor_preta == 1 && cor_atual == preto) caractere = '|';
	}else{
		 if(cor_atual != preto) caractere = 35;
		 else caractere = '|';
	}
	if(cor_atual == azul){
		reposicionar_indicador_do_console(coordenada_x+2, coordenada_y);
		printf("%c", caractere);
	}else if(cor_atual == roxo){
		reposicionar_indicador_do_console(coordenada_x+2, coordenada_y+1);
		printf("%c", caractere);
	}else if(cor_atual == azul_brilhante){
		reposicionar_indicador_do_console(coordenada_x+2, coordenada_y+2);
		printf("%c", caractere);
	}else if(cor_atual == roxo_brilhante){
		reposicionar_indicador_do_console(coordenada_x+2, coordenada_y+3);
		printf("%c", caractere);
	}else if(cor_atual == verde){
		reposicionar_indicador_do_console(coordenada_x+8, coordenada_y);
		printf("%c", caractere);
	}else if(cor_atual == amarelo){
		reposicionar_indicador_do_console(coordenada_x+8, coordenada_y+1);
		printf("%c", caractere);
	}else if(cor_atual == verde_brilhante){
		reposicionar_indicador_do_console(coordenada_x+8, coordenada_y+2);
		printf("%c", caractere);
	}else if(cor_atual == amarelo_brilhante){
		reposicionar_indicador_do_console(coordenada_x+8, coordenada_y+3);
		printf("%c", caractere);
	}else if(cor_atual == ciano){
		reposicionar_indicador_do_console(coordenada_x+14, coordenada_y);
		printf("%c", caractere);
	}else if(cor_atual == cinza_claro){
		reposicionar_indicador_do_console(coordenada_x+14, coordenada_y+1);
		printf("%c", caractere);
	}else if(cor_atual == ciano_brilhante){
		reposicionar_indicador_do_console(coordenada_x+14, coordenada_y+2);
		printf("%c", caractere);
	}else if(cor_atual == branco){
		reposicionar_indicador_do_console(coordenada_x+14, coordenada_y+3);
		printf("%c", caractere);
	}else if(cor_atual == vermelho){
		reposicionar_indicador_do_console(coordenada_x+20, coordenada_y);
		printf("%c", caractere);
	}else if(cor_atual == cinza_escuro){
		reposicionar_indicador_do_console(coordenada_x+20, coordenada_y+1);
		printf("%c", caractere);
	}else if(cor_atual == vermelho_brilhante){
		reposicionar_indicador_do_console(coordenada_x+20, coordenada_y+2);
		printf("%c", caractere);
	}else if(cor_atual == preto){
		reposicionar_indicador_do_console(coordenada_x+20, coordenada_y+3);
		if(apagar == 1) alterar_a_cor(branco, preto);
		printf("%c  %c", caractere, caractere);
	}
	alterar_a_cor(branco, preto);
}

void imprimir_string_desligado_ou_ligado(int coordenada_x, int coordenada_y, int condicional, cor cor_do_texto_ligado, 
	cor cor_do_fundo_ligado, cor cor_do_texto_desligado, cor cor_do_fundo_desligado){
	reposicionar_indicador_do_console(coordenada_x, coordenada_y);
	if(condicional == 1){
		alterar_a_cor(cor_do_texto_ligado, cor_do_fundo_ligado);
		printf("ON");
		alterar_a_cor(branco, preto);
		printf("   ");
	}else{
		alterar_a_cor(cor_do_texto_desligado, cor_do_fundo_desligado);
		printf("OFF");
		alterar_a_cor(branco, preto);
	}
}

void desenhar_ou_apagar_o_aviso_sobre_problemas_visuais_entre_matriz_e_labirinto(int coordenada_x, int coordenada_y, 
	int condicao_para_apagar_texto){
	reposicionar_indicador_do_console(coordenada_x, coordenada_y);
	if(condicao_para_apagar_texto == 0) printf(" Aviso:");
	else printf("       ");
	reposicionar_indicador_do_console(coordenada_x, coordenada_y+1);
	if(condicao_para_apagar_texto == 0)
		printf(" \tUma largura e altura do labirinto superiores respectivamente a 53 e 16,");
	else printf(" \t                                                                       ");
	reposicionar_indicador_do_console(coordenada_x, coordenada_y+2);
	if(condicao_para_apagar_texto == 0)
		printf(" n%co permitir%c com que a matriz e o labirinto sejam desenhados sem que ocorram", 198, 160);
	else printf("                                                                              ");
	reposicionar_indicador_do_console(coordenada_x, coordenada_y+3);
	if(condicao_para_apagar_texto == 0)
		printf(" problemas visuais. Voc%c deseja ativar essa op%c%co assim mesmo?", 136, 135, 198);
	else printf("                                                              ");
	reposicionar_indicador_do_console(coordenada_x, coordenada_y+4);
	if(condicao_para_apagar_texto == 0) printf("    Sim");
	else printf("       ");
	reposicionar_indicador_do_console(coordenada_x, coordenada_y+5);
	if(condicao_para_apagar_texto == 0) printf("    N%co  ", 198);
	else printf("       "); 
	reposicionar_indicador_do_console(coordenada_x, coordenada_y+6);
	if(condicao_para_apagar_texto == 0) printf("    Ativar e mudar a largura para 53");
	else printf("                                    ");
	reposicionar_indicador_do_console(coordenada_x, coordenada_y+7);
	if(condicao_para_apagar_texto == 0) printf("    Ativar e mudar a altura para 16");
	else printf("                                   ");
}

sentido decidir_caminho_a_ser_tomado(int** matriz, int coordenada_x, int coordenada_y, int largura, int altura, 
	int vetor_de_possibilidades[], int* primeira_execulcao_da_funcao, 
	int* total_de_possibilidades_analisadas_na_movimentacao_do_labirinto){
	int condicao_para_analisar_todas_as_possibilidades = 0, posicao_atual_do_vetor_de_possibilidades = 0;
	for(int a=0; a<=4; a++){
		if(a == 4) condicao_para_analisar_todas_as_possibilidades = 1;
		if(*primeira_execulcao_da_funcao == 1){
			*primeira_execulcao_da_funcao = 0;
			*total_de_possibilidades_analisadas_na_movimentacao_do_labirinto+=1;
			if(coordenada_y == 0){
				if(matriz[coordenada_y+1][coordenada_x] == 0) return baixo;
				if(coordenada_x > 0 && matriz[coordenada_y][coordenada_x-1] == 0) return esquerda;
				else return direita;
			}else if(coordenada_y == altura-1){
				if(matriz[coordenada_y-1][coordenada_x] == 0) return cima;
				if(coordenada_x > 0 && matriz[coordenada_y][coordenada_x-1] == 0) return esquerda;
				else return direita;
			}else if(coordenada_x == 0){
				if(matriz[coordenada_y][coordenada_x+1] == 0) return direita;
				if(coordenada_y > 0 && matriz[coordenada_y-1][coordenada_x] == 0) return cima;
				else return baixo;
			}else if(coordenada_x == largura-1){
				if(matriz[coordenada_y][coordenada_x-1] == 0) return esquerda;
				if(coordenada_y > 0 && matriz[coordenada_y-1][coordenada_x] == 0) return cima;
				else return baixo;
			}
		}else{
			*total_de_possibilidades_analisadas_na_movimentacao_do_labirinto+=1;
			if(vetor_de_possibilidades[posicao_atual_do_vetor_de_possibilidades] == 0 || condicao_para_analisar_todas_as_possibilidades == 1){
				if(coordenada_y > 1 && coordenada_y-1 > 0 && matriz[coordenada_y-1][coordenada_x] == 0 && 
					(matriz[coordenada_y-2][coordenada_x] == 0 || matriz[coordenada_y-2][coordenada_x] == 4) && coordenada_x > 0 && 
					coordenada_x < largura-1 && (matriz[coordenada_y-1][coordenada_x-1] == 0 || 
					matriz[coordenada_y-1][coordenada_x-1] == 4) && (matriz[coordenada_y-1][coordenada_x+1] == 0 || 
					matriz[coordenada_y-1][coordenada_x+1] == 4)) return cima;
			}
			*total_de_possibilidades_analisadas_na_movimentacao_do_labirinto+=1;
			if(vetor_de_possibilidades[posicao_atual_do_vetor_de_possibilidades] == 1 || condicao_para_analisar_todas_as_possibilidades == 1){
				if(coordenada_x < largura-2 && coordenada_x+1 < largura-1 && matriz[coordenada_y][coordenada_x+1] == 0 &&
					(matriz[coordenada_y][coordenada_x+2] == 0 || matriz[coordenada_y][coordenada_x+2] == 4) &&
					coordenada_y > 0 && coordenada_y < altura-1 && (matriz[coordenada_y-1][coordenada_x+1] == 0 || 
					matriz[coordenada_y-1][coordenada_x+1] == 4) && (matriz[coordenada_y+1][coordenada_x+1] == 0 ||
					matriz[coordenada_y+1][coordenada_x+1] == 4)) return direita;
			}
			*total_de_possibilidades_analisadas_na_movimentacao_do_labirinto+=1;
			if(vetor_de_possibilidades[posicao_atual_do_vetor_de_possibilidades] == 2 || condicao_para_analisar_todas_as_possibilidades == 1){
				if(coordenada_x > 1 && coordenada_x-1 > 0 && matriz[coordenada_y][coordenada_x-1] == 0 && 
					(matriz[coordenada_y][coordenada_x-2] == 0 || matriz[coordenada_y][coordenada_x-2] == 4) && 
					coordenada_y > 0 && coordenada_y < altura-1 && (matriz[coordenada_y-1][coordenada_x-1] == 0 || 
					matriz[coordenada_y-1][coordenada_x-1] == 4) && (matriz[coordenada_y+1][coordenada_x-1] == 0 || 
					matriz[coordenada_y+1][coordenada_x-1] == 4)) return esquerda;
			}
			*total_de_possibilidades_analisadas_na_movimentacao_do_labirinto+=1;
			if(vetor_de_possibilidades[posicao_atual_do_vetor_de_possibilidades] == 3 || condicao_para_analisar_todas_as_possibilidades == 1){
				if(coordenada_y < altura-2 && coordenada_y+1 < altura-1 && matriz[coordenada_y+1][coordenada_x] == 0 &&
					(matriz[coordenada_y+2][coordenada_x] == 0 || matriz[coordenada_y+2][coordenada_x] == 4) &&
					coordenada_x > 0 && coordenada_x < largura-1 && (matriz[coordenada_y+1][coordenada_x-1] == 0 || 
					matriz[coordenada_y+1][coordenada_x-1] == 4) && (matriz[coordenada_y+1][coordenada_x+1] == 0 || 
					matriz[coordenada_y+1][coordenada_x+1] == 4)) return baixo;
			}
		}
		if(a != 4) posicao_atual_do_vetor_de_possibilidades++;
	}
	return -1;
}

/*int decidir_caminho_a_ser_tomado(int** matriz, int coordenada_x_inicial, int coordenada_y_inicial, int largura, int altura, int rand, int* comeco){
	int condicional = 0;
	int x;
	for(int k=4; k>=0; k--){
		rand = (56683+rand)%4;
		//Começos especiais
		if(*comeco == 1 && coordenada_y_inicial == 0 && matriz[coordenada_y_inicial+1][coordenada_x_inicial] == 0 && 
		(matriz[coordenada_y_inicial+2][coordenada_x_inicial] == 0 || matriz[coordenada_y_inicial+2][coordenada_x_inicial] == 2)){
			*comeco = 0;
			return baixo;
		}
		if(*comeco == 1 && coordenada_y_inicial == altura-1 && matriz[coordenada_y_inicial-1][coordenada_x_inicial] == 0 && 
		(matriz[coordenada_y_inicial-2][coordenada_x_inicial] == 0 || matriz[coordenada_y_inicial-2][coordenada_x_inicial] == 2)){
			*comeco = 0;
			return cima;
		}
		if(*comeco == 1 && coordenada_x_inicial == largura-1 && matriz[coordenada_y_inicial][coordenada_x_inicial-1] == 0 && 
		(matriz[coordenada_y_inicial][coordenada_x_inicial-2] == 0 || matriz[coordenada_y_inicial][coordenada_x_inicial-2] == 2)){
			*comeco = 0;
			return esquerda;
		}
		if(*comeco == 1 && coordenada_x_inicial == 0 && matriz[coordenada_y_inicial][coordenada_x_inicial+1] == 0 && 
		(matriz[coordenada_y_inicial][coordenada_x_inicial+2] == 0 || matriz[coordenada_y_inicial][coordenada_x_inicial+2] == 2)){
			*comeco = 0;
			return direita;
		}
		//Parte difícil
		if(rand == 3 || condicional == 1){
			if(coordenada_x_inicial < largura-2 && matriz[coordenada_y_inicial][coordenada_x_inicial+1] == 0 && 
			(matriz[coordenada_y_inicial][coordenada_x_inicial+2] == 0 || matriz[coordenada_y_inicial][coordenada_x_inicial+2] == 2)){
				if((matriz[coordenada_y_inicial+1][coordenada_x_inicial+1] == 0 || matriz[coordenada_y_inicial+1][coordenada_x_inicial+1] == 2) 
				&& (matriz[coordenada_y_inicial-1][coordenada_x_inicial+1] == 0 || matriz[coordenada_y_inicial-1][coordenada_x_inicial+1] == 0))  return direita;
			}
		}
		if(rand == 2 || condicional == 1){
			if(coordenada_y_inicial < altura-2 && matriz[coordenada_y_inicial+1][coordenada_x_inicial] == 0 && 
			(matriz[coordenada_y_inicial+2][coordenada_x_inicial] == 0 || matriz[coordenada_y_inicial+2][coordenada_x_inicial] == 2))
				if((matriz[coordenada_y_inicial+1][coordenada_x_inicial+1] == 0 || matriz[coordenada_y_inicial+1][coordenada_x_inicial+1] == 2)
				&& (matriz[coordenada_y_inicial+1][coordenada_x_inicial-1] == 0 || matriz[coordenada_y_inicial+1][coordenada_x_inicial-1] == 2)){
					return baixo;	 
			}
		}
		if(rand ==1 || condicional == 1){
			if(coordenada_x_inicial > 1 && matriz[coordenada_y_inicial][coordenada_x_inicial-1] == 0 && 
			(matriz[coordenada_y_inicial][coordenada_x_inicial-2] == 0 || matriz[coordenada_y_inicial][coordenada_x_inicial-2] == 0)){
				if((matriz[coordenada_y_inicial+1][coordenada_x_inicial-1] == 0 || matriz[coordenada_y_inicial+1][coordenada_x_inicial-1] == 2)
				&& (matriz[coordenada_y_inicial-1][coordenada_x_inicial-1] == 0 || matriz[coordenada_y_inicial-1][coordenada_x_inicial-1] == 2))
					return esquerda;
			}
		}
		if(rand==0 || condicional == 1){
			if(coordenada_y_inicial > 1 && matriz[coordenada_y_inicial-1][coordenada_x_inicial] == 0 && 
			(matriz[coordenada_y_inicial-2][coordenada_x_inicial] == 0 || matriz[coordenada_y_inicial-2][coordenada_x_inicial] == 2)){
				if((matriz[coordenada_y_inicial-1][coordenada_x_inicial+1] == 0 || matriz[coordenada_y_inicial-1][coordenada_x_inicial+1] == 2)
				&& (matriz[coordenada_y_inicial-1][coordenada_x_inicial-1] == 0 || matriz[coordenada_y_inicial-1][coordenada_x_inicial-1] == 2))
					return cima;		
			}
		}
		if(k==0) condicional = 1;
	}
	return -1;
}	
*/
void inserir_dados(int coordenada_x_menu_principal, int coordenada_y_menu_principal, int opcao_escolhida, int largura_minima, 
	int largura_maxima, int altura_minima, int altura_maxima, int* largura_atual, int* altura_atual, 
	cor* cor_do_retangulo_inicial, cor* cor_do_retangulo_final, cor* cor_das_paredes_intermediarias, 
	cor* cor_das_paredes_intermediarias_segunda_passada, cor* cor_das_bordas, char* caractere_utilizado_nas_bordas, 
	char* caractere_utilizado_nas_paredes, int* sleep, int* coordenada_x_inicio_1, int* coordenada_y_inicio_1, 
	int* coordenada_x_inicio_2, int* coordenada_y_inicio_2, int* coordenada_x_fim_1, int* coordenada_y_fim_1, 
	int* coordenada_x_fim_2, int* coordenada_y_fim_2, int* mostrar_matriz, int* mostrar_tamanho_da_pilha, 
	int* mostrar_capacidade_da_pilha, int* mostrar_coordenada_atual, int* mostrar_valor_da_variavel_sleep, 
	int* mostrar_total_de_alocacoes_e_desalocacoes, int* mostrar_total_de_possibilidades_analisadas, 
	int* confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto){
	int opcao_escolhida_menu_secundario = 0, botao_esc_acionado = 0, botao_enter_acionado = 0;
	if(opcao_escolhida == 0){
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
		printf("Change reference coordinates:                                                                ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
		printf("   Change maze start   == (%d, %d)  ", *coordenada_x_inicio_1, *coordenada_y_inicio_1);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
		printf("   Change maze end     == (%d, %d)        ", *coordenada_x_fim_1, *coordenada_y_fim_2);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+3);
		printf("                       ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+4);
		printf("Axis x: from 0 to %d                                                       ",*largura_atual-1);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
		printf("Axis y: from 0 to %d                          ", *altura_atual-1);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+6);
		printf("Current maze width == %d       ", *largura_atual);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
		printf("Current maze height == %d", *altura_atual);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+8);
		printf("Press ESC to return to the main menu");
		while(botao_esc_acionado != 1){
			desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, &opcao_escolhida_menu_secundario, 0, 2,
				0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
			if(opcao_escolhida_menu_secundario == 0 && botao_enter_acionado == 1){
				reposicionar_indicador_do_console(coordenada_x_menu_principal+26, coordenada_y_menu_principal+1);
				printf("         ");
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
				int entrada_de_dados_processada = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+27, 
					coordenada_y_menu_principal+1, 2);
				if(entrada_de_dados_processada >= 0 && entrada_de_dados_processada < *largura_atual){
					if(entrada_de_dados_processada == *coordenada_x_fim_1 && *coordenada_y_inicio_1 == *coordenada_y_fim_1){
						int auxiliar = *coordenada_x_inicio_1;
						*coordenada_x_inicio_1 = *coordenada_x_fim_1;
						*coordenada_x_fim_1 = auxiliar;
						auxiliar = *coordenada_x_inicio_2;
						*coordenada_x_inicio_2 = *coordenada_x_fim_2;
						*coordenada_x_fim_2 = auxiliar;
						auxiliar = *coordenada_y_inicio_1;
						*coordenada_y_inicio_1 = *coordenada_y_fim_1;
						*coordenada_y_fim_1 = auxiliar;
						auxiliar = *coordenada_y_inicio_2;
						*coordenada_y_inicio_2 = *coordenada_y_fim_2;
						*coordenada_y_fim_2 = auxiliar;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
							(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, 
							*caractere_utilizado_nas_paredes);
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
						reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
						printf("   Change maze end     == (%d, %d)        ", *coordenada_x_fim_1, *coordenada_y_fim_2);
					}else{
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
							(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, preto, 
							*caractere_utilizado_nas_paredes);
						*coordenada_x_inicio_1 = entrada_de_dados_processada;
						*coordenada_x_inicio_2 = entrada_de_dados_processada+1;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
							(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, 
							*caractere_utilizado_nas_paredes);
					}
				}
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
				printf("-> Change maze start   ==  %d, ", *coordenada_x_inicio_1 );
				int contador = 0, auxiliar;
				if(entrada_de_dados_processada == -1) auxiliar = *coordenada_x_inicio_1;
				else auxiliar = entrada_de_dados_processada;
				while(auxiliar != 0){
					auxiliar /= 10;
					contador++;
				}
				if(contador <= 1) entrada_de_dados_processada = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+30, 
					coordenada_y_menu_principal+1, 2);
				else entrada_de_dados_processada = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+31, 
					coordenada_y_menu_principal+1, 2);
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
				if(entrada_de_dados_processada >= 0 && entrada_de_dados_processada < *altura_atual){
					if(entrada_de_dados_processada == *coordenada_y_fim_1 && *coordenada_x_inicio_1 == *coordenada_x_fim_1){
						int auxiliar = *coordenada_x_inicio_1;
						*coordenada_x_inicio_1 = *coordenada_x_fim_1;
						*coordenada_x_fim_1 = auxiliar;
						auxiliar = *coordenada_x_inicio_2;
						*coordenada_x_inicio_2 = *coordenada_x_fim_2;
						*coordenada_x_fim_2 = auxiliar;
						auxiliar = *coordenada_y_inicio_1;
						*coordenada_y_inicio_1 = *coordenada_y_fim_1;
						*coordenada_y_fim_1 = auxiliar;
						auxiliar = *coordenada_y_inicio_2;
						*coordenada_y_inicio_2 = *coordenada_y_fim_2;
						*coordenada_y_fim_2 = auxiliar;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
							(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, 
							*caractere_utilizado_nas_paredes);
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
						reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
						printf("   Change maze end     == (%d, %d)        ", *coordenada_x_fim_1, *coordenada_y_fim_2);
					}else{
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
							(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, preto, 
							*caractere_utilizado_nas_paredes);
						*coordenada_y_inicio_1 = entrada_de_dados_processada;
						*coordenada_y_inicio_2 = entrada_de_dados_processada;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
							(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, 
							*caractere_utilizado_nas_paredes);
					}	
				}
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
				printf("   Change maze start   == (%d, %d)  ", *coordenada_x_inicio_1, *coordenada_y_inicio_1);
			}
			if(opcao_escolhida_menu_secundario == 1 && botao_enter_acionado == 1){
				char entrada_de_dados_posicao_x[50];
				char entrada_de_dados_posicao_y[50];
				reposicionar_indicador_do_console(coordenada_x_menu_principal+26, coordenada_y_menu_principal+2);
				printf("         ");
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
				int entrada_de_dados_processada = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+27, 
					coordenada_y_menu_principal+2, 2);
				if(entrada_de_dados_processada >= 0 && entrada_de_dados_processada < *largura_atual){
					if(entrada_de_dados_processada == *coordenada_x_inicio_1 && *coordenada_y_fim_1 == *coordenada_y_inicio_1){
						int auxiliar = *coordenada_x_inicio_1;
						*coordenada_x_inicio_1 = *coordenada_x_fim_1;
						*coordenada_x_fim_1 = auxiliar;
						auxiliar = *coordenada_x_inicio_2;
						*coordenada_x_inicio_2 = *coordenada_x_fim_2;
						*coordenada_x_fim_2 = auxiliar;
						auxiliar = *coordenada_y_inicio_1;
						*coordenada_y_inicio_1 = *coordenada_y_fim_1;
						*coordenada_y_fim_1 = auxiliar;
						auxiliar = *coordenada_y_inicio_2;
						*coordenada_y_inicio_2 = *coordenada_y_fim_2;
						*coordenada_y_fim_2 = auxiliar;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
							(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, 
							*caractere_utilizado_nas_paredes);
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
						reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
						printf("   Change maze start   == (%d, %d)  ", *coordenada_x_inicio_1, *coordenada_y_inicio_1);
					}else{
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, preto, *caractere_utilizado_nas_paredes);
							*coordenada_x_fim_1 = entrada_de_dados_processada;
							*coordenada_x_fim_2 = entrada_de_dados_processada+1;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
					}
				}
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
				printf("-> Change maze end     ==  %d, ", *coordenada_x_fim_1 );
				int contador = 0, auxiliar;
				if(entrada_de_dados_processada == -1) auxiliar = *coordenada_x_fim_1;
				else auxiliar = entrada_de_dados_processada;
				while(auxiliar != 0){
					auxiliar /= 10;
					contador++;
				}
				if(contador <= 1) entrada_de_dados_processada = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+30, 
					coordenada_y_menu_principal+2, 2);
				else entrada_de_dados_processada = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+31, 
					coordenada_y_menu_principal+2, 2);
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
				if(entrada_de_dados_processada >= 0 && entrada_de_dados_processada < *altura_atual){
					if(entrada_de_dados_processada == *coordenada_y_inicio_1 && *coordenada_x_fim_1 == *coordenada_x_inicio_1){
						int auxiliar = *coordenada_x_inicio_1;
						*coordenada_x_inicio_1 = *coordenada_x_fim_1;
						*coordenada_x_fim_1 = auxiliar;
						auxiliar = *coordenada_x_inicio_2;
						*coordenada_x_inicio_2 = *coordenada_x_fim_2;
						*coordenada_x_fim_2 = auxiliar;
						auxiliar = *coordenada_y_inicio_1;
						*coordenada_y_inicio_1 = *coordenada_y_fim_1;
						*coordenada_y_fim_1 = auxiliar;
						auxiliar = *coordenada_y_inicio_2;
						*coordenada_y_inicio_2 = *coordenada_y_fim_2;
						*coordenada_y_fim_2 = auxiliar;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
							(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, 
							*caractere_utilizado_nas_paredes);
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
						reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
						printf("   Change maze start   == (%d, %d)  ", *coordenada_x_inicio_1, *coordenada_y_inicio_1);
					}else{
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, preto, *caractere_utilizado_nas_paredes);
							*coordenada_y_fim_1 = entrada_de_dados_processada;
							*coordenada_y_fim_2 = entrada_de_dados_processada;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
					}	
				}
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
				printf("   Change maze end     == (%d, %d) ", *coordenada_x_fim_1, *coordenada_y_fim_1);
			}
			botao_enter_acionado = 0;
		}
	}
	if(opcao_escolhida == 1){
		printf("Resize borders:                                                                         ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
		printf("   Change maze width    == %d       ", *largura_atual);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
		printf("   Change maze height   == %d         ", *altura_atual);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+3);
		printf("                       ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+4);
		printf("Min width == %d                                                    ", largura_minima);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
		printf("Max width == %d             ", largura_maxima);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+6);
		printf("Min height == %d                    ", altura_minima);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
		printf("Max height == %d", altura_maxima);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+8);
		printf("Press ESC to return to the main menu");
		while(botao_esc_acionado != 1){
			desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, &opcao_escolhida_menu_secundario, 0, 2,
				0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
			if(opcao_escolhida_menu_secundario == 0 && botao_enter_acionado == 1){
				reposicionar_indicador_do_console(coordenada_x_menu_principal+27, coordenada_y_menu_principal+1);
				printf("  ");
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
				int entrada_de_dados_processada = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+27, 
					coordenada_y_menu_principal+1, 2);
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
				if(entrada_de_dados_processada >= largura_minima && entrada_de_dados_processada <= largura_maxima && 
				   entrada_de_dados_processada != *largura_atual){
				   	if(entrada_de_dados_processada > 53 && *altura_atual > 16 && 
						*confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto == 0 && *mostrar_matriz == 1){
						desenhar_ou_apagar_o_aviso_sobre_problemas_visuais_entre_matriz_e_labirinto(coordenada_x_menu_principal+35, 
							coordenada_y_menu_principal+1, 0);
						reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
						printf("  ");
						int opcao_escolhida_menu_terciario = 0;
						botao_enter_acionado = 0;
						while(botao_esc_acionado != 1 && botao_enter_acionado != 1){
							desenhar_seta(coordenada_x_menu_principal+36, coordenada_y_menu_principal+5, 
								&opcao_escolhida_menu_terciario, 0, 4, 0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
							if(opcao_escolhida_menu_terciario == 0 && botao_enter_acionado == 1){
								int opcao_escolhida_menu_quartenario = 0;
								botao_enter_acionado = 0;
								reposicionar_indicador_do_console(coordenada_x_menu_principal+35, coordenada_y_menu_principal+5);
								printf("    Sim > Deseja n%co receber mais esse aviso?", 198);
								reposicionar_indicador_do_console(coordenada_x_menu_principal+39, coordenada_y_menu_principal+6);
								printf("         Sim");
								reposicionar_indicador_do_console(coordenada_x_menu_principal+39, coordenada_y_menu_principal+7);
								printf("         N%co                    ", 198);
								reposicionar_indicador_do_console(coordenada_x_menu_principal+39, coordenada_y_menu_principal+8);
								printf("                                   ");
								while(botao_esc_acionado != 1 && botao_enter_acionado != 1){
									desenhar_seta(coordenada_x_menu_principal+45, coordenada_y_menu_principal+6, 
										&opcao_escolhida_menu_quartenario, 0, 2, 0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
									if(opcao_escolhida_menu_quartenario == 0 && botao_enter_acionado == 1){
										*confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto = 1;
										reposicionar_indicador_do_console(coordenada_x_menu_principal+48, coordenada_y_menu_principal+6);
										printf("Sim > Essa op%c%co poder%c ser desfeita posterimoente no menu de ajustes", 135, 198, 160);	
										alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
										getch();
										alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
										reposicionar_indicador_do_console(coordenada_x_menu_principal+48, coordenada_y_menu_principal+6);
										printf("                                                                     ");
										botao_enter_acionado = 1;
										desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
											*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
										*largura_atual = entrada_de_dados_processada;
									}else if(opcao_escolhida_menu_quartenario == 1 && botao_enter_acionado == 1){
										desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
											*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
										*largura_atual = entrada_de_dados_processada;
									}
									if(botao_esc_acionado == 1){
										botao_esc_acionado = botao_enter_acionado = 0;
										break;
									}
								}
								reposicionar_indicador_do_console(coordenada_x_menu_principal+35, 
									coordenada_y_menu_principal+5);
								printf("    Sim                                      ");
								reposicionar_indicador_do_console(coordenada_x_menu_principal+35, 
									coordenada_y_menu_principal+6);
								printf("    N%co            ", 198);
								reposicionar_indicador_do_console(coordenada_x_menu_principal+35, 
									coordenada_y_menu_principal+7);
								printf("    Ativar e mudar a largura para 53");
								reposicionar_indicador_do_console(coordenada_x_menu_principal+35, 
									coordenada_y_menu_principal+8);
								printf("    Ativar e mudar a altura para 16");
							}else if(opcao_escolhida_menu_terciario == 1 && botao_enter_acionado == 1) break;
							else if(opcao_escolhida_menu_terciario == 2 && botao_enter_acionado == 1){
								desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
									*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
								*largura_atual = 53;
							}else if(opcao_escolhida_menu_terciario == 3 && botao_enter_acionado == 1){
								desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
									*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
								*largura_atual = entrada_de_dados_processada;
								*altura_atual = 16;
								reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
								printf("   Change maze height   == %d         ", *altura_atual);
							}
						}
						botao_enter_acionado = 0;
						desenhar_ou_apagar_o_aviso_sobre_problemas_visuais_entre_matriz_e_labirinto(coordenada_x_menu_principal+36, 
							coordenada_y_menu_principal+1, 1);
						reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+8);
						printf("Aperte ESC para retornar ao menu principal");
					}else{
						desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, *largura_atual*2,
				   			*altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
						*largura_atual = entrada_de_dados_processada;
					}
					if(botao_esc_acionado != 1){
						if(*coordenada_x_inicio_1 >= *largura_atual){
							desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
								*coordenada_y_inicio_2+10, preto, *caractere_utilizado_nas_paredes);
							if(*coordenada_x_fim_1 >= *largura_atual-1 && *coordenada_y_inicio_1 == *coordenada_y_fim_1){
								*coordenada_x_inicio_1 = *largura_atual-2;
								*coordenada_x_inicio_2 = *largura_atual-1;
							}else{
								*coordenada_x_inicio_1 = *largura_atual-1;
								*coordenada_x_inicio_2 = *largura_atual;
							}
							desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
								*coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, *caractere_utilizado_nas_paredes);
						}
						if(*coordenada_x_fim_1 >= *largura_atual){
							desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
								*coordenada_y_fim_2+10, preto, *caractere_utilizado_nas_paredes);
							if(*coordenada_x_inicio_1 >= *largura_atual-1 && *coordenada_y_inicio_1 == *coordenada_y_fim_1){
								*coordenada_x_fim_1 = *largura_atual-2;
								*coordenada_x_fim_2 = *largura_atual-1;
							}else{
								*coordenada_x_fim_1 = *largura_atual-1;
								*coordenada_x_fim_2 = *largura_atual;
							}
							desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
								*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);	
						}
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, *largura_atual*2,
							*altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}
				}
				if(botao_esc_acionado == 1) botao_esc_acionado = 0;
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
				printf("   Change maze width    == %d ", *largura_atual);
			}else if(opcao_escolhida_menu_secundario == 1 && botao_enter_acionado == 1){
				reposicionar_indicador_do_console(coordenada_x_menu_principal+27, coordenada_y_menu_principal+2);
				printf("  ");
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
				int entrada_de_dados_processada = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+27, 
					coordenada_y_menu_principal+2, 2);
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
				if(entrada_de_dados_processada >= altura_minima && entrada_de_dados_processada <= altura_maxima && 
					entrada_de_dados_processada != *altura_atual){
					if(entrada_de_dados_processada > 16 && *largura_atual > 53 && 
						*confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto == 0 && *mostrar_matriz == 1){
						desenhar_ou_apagar_o_aviso_sobre_problemas_visuais_entre_matriz_e_labirinto(coordenada_x_menu_principal+35, 
							coordenada_y_menu_principal+1, 0);
						reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
						printf("  ");
						int opcao_escolhida_menu_terciario = 0;
						botao_enter_acionado = 0;
						while(botao_esc_acionado != 1 && botao_enter_acionado != 1){
							desenhar_seta(coordenada_x_menu_principal+36, coordenada_y_menu_principal+5, 
								&opcao_escolhida_menu_terciario, 0, 4, 0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
							if(opcao_escolhida_menu_terciario == 0 && botao_enter_acionado == 1){
								int opcao_escolhida_menu_quartenario = 0;
								botao_enter_acionado = 0;
								reposicionar_indicador_do_console(coordenada_x_menu_principal+35, coordenada_y_menu_principal+5);
								printf("    Sim > Deseja n%co receber mais esse aviso?", 198);
								reposicionar_indicador_do_console(coordenada_x_menu_principal+39, coordenada_y_menu_principal+6);
								printf("         Sim");
								reposicionar_indicador_do_console(coordenada_x_menu_principal+39, coordenada_y_menu_principal+7);
								printf("         N%co                    ", 198);
								reposicionar_indicador_do_console(coordenada_x_menu_principal+39, coordenada_y_menu_principal+8);
								printf("                                   ");
								while(botao_esc_acionado != 1 && botao_enter_acionado != 1){
									desenhar_seta(coordenada_x_menu_principal+45, coordenada_y_menu_principal+6, 
										&opcao_escolhida_menu_quartenario, 0, 2, 0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
									if(opcao_escolhida_menu_quartenario == 0 && botao_enter_acionado == 1){
										*confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto = 1;
										reposicionar_indicador_do_console(coordenada_x_menu_principal+48, coordenada_y_menu_principal+6);
										printf("Sim > Essa op%c%co poder%c ser desfeita posterimoente no menu de ajustes", 135, 198, 160);	
										alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
										getch();
										alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
										reposicionar_indicador_do_console(coordenada_x_menu_principal+48, coordenada_y_menu_principal+6);
										printf("                                                                     ");
										botao_enter_acionado = 1;
										desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
											*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
										*altura_atual = entrada_de_dados_processada;
									}else if(opcao_escolhida_menu_quartenario == 1 && botao_enter_acionado == 1){
										desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
											*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
										*altura_atual = entrada_de_dados_processada;
									}
									if(botao_esc_acionado == 1){
										botao_esc_acionado = botao_enter_acionado = 0;
										break;
									}
								}
								reposicionar_indicador_do_console(coordenada_x_menu_principal+35, 
									coordenada_y_menu_principal+5);
								printf("    Sim                                      ");
								reposicionar_indicador_do_console(coordenada_x_menu_principal+35, 
									coordenada_y_menu_principal+6);
								printf("    N%co            ", 198);
								reposicionar_indicador_do_console(coordenada_x_menu_principal+35, 
									coordenada_y_menu_principal+7);
								printf("    Ativar e mudar a largura para 53");
								reposicionar_indicador_do_console(coordenada_x_menu_principal+35, 
									coordenada_y_menu_principal+8);
								printf("    Ativar e mudar a altura para 16");
							}else if(opcao_escolhida_menu_terciario == 1 && botao_enter_acionado == 1) break;
							else if(opcao_escolhida_menu_terciario == 2 && botao_enter_acionado == 1){
								desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
									*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
								*largura_atual = 53;
								*altura_atual = entrada_de_dados_processada;
								reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
								printf("   Change maze width    == %d       ", *largura_atual);
							}else if(opcao_escolhida_menu_terciario == 3 && botao_enter_acionado == 1){
								desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
									*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
								*altura_atual = 16;
							}
						}
						botao_enter_acionado = 0;
						desenhar_ou_apagar_o_aviso_sobre_problemas_visuais_entre_matriz_e_labirinto(coordenada_x_menu_principal+36, 
							coordenada_y_menu_principal+1, 1);
						reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+8);
						printf("Aperte ESC para retornar ao menu principal");
					}else{
						desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, *largura_atual*2,
				   			*altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
						*altura_atual = entrada_de_dados_processada;
					}
					if(botao_esc_acionado != 1){
						if(*coordenada_y_inicio_1 >= *altura_atual){
							desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
								*coordenada_y_inicio_2+10, preto, *caractere_utilizado_nas_paredes);
							if(*coordenada_y_fim_1 >= *altura_atual-1 && *coordenada_x_inicio_1 == *coordenada_x_fim_1){
								*coordenada_y_inicio_1 = *altura_atual-2;
								*coordenada_y_inicio_2 = *altura_atual-2;
							}else{
								*coordenada_y_inicio_1 = *altura_atual-1;
								*coordenada_y_inicio_2 = *altura_atual-1;
							}
							desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
								*coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, *caractere_utilizado_nas_paredes);
						}
						if(*coordenada_y_fim_1 >= *altura_atual){
							desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
								*coordenada_y_fim_2+10, preto, *caractere_utilizado_nas_paredes);
							if(*coordenada_y_inicio_1 >= *altura_atual-1 && *coordenada_x_inicio_1 == *coordenada_x_fim_1){
								*coordenada_y_fim_1 = *altura_atual-2;
								*coordenada_y_fim_2 = *altura_atual-2;
							}else{
								*coordenada_y_fim_1 = *altura_atual-1;
								*coordenada_y_fim_2 = *altura_atual-1;
							}
							desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
								*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
						}
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, *largura_atual*2,
							*altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);	
					}
				}
				if(botao_esc_acionado == 1) botao_esc_acionado = 0;
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
				printf("   Change maze height   == %d", *altura_atual);
			}
			botao_enter_acionado = 0;
		}
	}
	if(opcao_escolhida == 2){
		int opcao_escolhida_menu_terciario = 0, limite_de_opcoes;
		while(botao_esc_acionado != 1){
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
			printf("Change border chars, walls and sleep var adjustment:                                          ");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
			printf("   Border style                                        ");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
			printf("   Wall char used                   ");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+3);
			printf("   Sleep variable == %d           ", *sleep);
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+4);
			printf("   Show warning messages ");
			if(*confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto == 1){
				alterar_a_cor(branco, vermelho);
				printf("OFF");
				alterar_a_cor(branco, preto);
				printf("                       ");
		}	else{
				alterar_a_cor(branco, verde);
				printf("ON");
				alterar_a_cor(branco, preto);
				printf("                          ");
			}
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
			printf("                           ");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+6);
			printf("                                       ");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
			printf("The higher the value of the sleep var, the slower the maze drawing will be", 160, 160);
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+8);
			printf("Press ESC to return to the main menu");
			desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, &opcao_escolhida_menu_secundario, 0, 4,
				0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
			if(opcao_escolhida_menu_secundario == 0 && botao_enter_acionado == 1){
				while(botao_esc_acionado != 1){
					botao_enter_acionado = 0;
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
					printf("   Border style                                        ");
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
					if(*caractere_utilizado_nas_bordas != -60 && *caractere_utilizado_nas_bordas != -51 && 
						*caractere_utilizado_nas_bordas != -80 && *caractere_utilizado_nas_bordas != -79 &&
						*caractere_utilizado_nas_bordas != -78 && *caractere_utilizado_nas_bordas != -37){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("Choose a character by code  > %c <   ", *caractere_utilizado_nas_bordas);
					}else{
						printf("   Choose a character by code  > %c <   ", *caractere_utilizado_nas_bordas);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
					if(*caractere_utilizado_nas_bordas == -60){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("%c%c%c%c%c%c%c%c%c | Ready Template      ", 196, 196, 196, 196, 196, 196, 196, 196, 196);	
					}else{
						printf("   %c%c%c%c%c%c%c%c%c | Ready Template      ", 196, 196, 196, 196, 196, 196, 196, 196, 196);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+3);
					if(*caractere_utilizado_nas_bordas == -51){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("%c%c%c%c%c%c%c%c%c | Ready Template", 205, 205, 205, 205, 205, 205, 205, 205, 205);
					}else{
						printf("   %c%c%c%c%c%c%c%c%c | Ready Template", 205, 205, 205, 205, 205, 205, 205, 205, 205);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+4);
					if(*caractere_utilizado_nas_bordas == -80){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("%c%c%c%c%c%c%c%c%c                           ", 176, 176, 176, 176, 176, 176, 176, 176, 176);
					}else{
						printf("   %c%c%c%c%c%c%c%c%c                           ", 176, 176, 176, 176, 176, 176, 176, 176, 176);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
					if(*caractere_utilizado_nas_bordas == -79){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("%c%c%c%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177, 177, 177, 177);
					}else{
						printf("   %c%c%c%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177, 177, 177, 177);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+6);
					if(*caractere_utilizado_nas_bordas == -78){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("%c%c%c%c%c%c%c%c%c", 178, 178, 178, 178, 178, 178, 178, 178, 178);
					}else{
						printf("   %c%c%c%c%c%c%c%c%c", 178, 178, 178, 178, 178, 178, 178, 178, 178);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
					if(*caractere_utilizado_nas_bordas == -37){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("%c%c%c%c%c%c%c%c%c                                                                              ", 219, 219, 219, 219, 219, 219, 219, 219, 219);
					}else{
						printf("   %c%c%c%c%c%c%c%c%c                                                                              ", 219, 219, 219, 219, 219, 219, 219, 219, 219);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+8);
					printf("Press ESC to return to the main menu");
					desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, &opcao_escolhida_menu_terciario, 0, 
						7, 0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
					if(opcao_escolhida_menu_terciario == 0 && botao_enter_acionado == 1){
						reposicionar_indicador_do_console(coordenada_x_menu_principal+31, coordenada_y_menu_principal+1);
						printf("      ");
						alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
						int valor_auxiliar = -1;
						valor_auxiliar = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+33, 
							coordenada_y_menu_principal+1, 3);
						if(valor_auxiliar >= 0){
							*caractere_utilizado_nas_bordas = valor_auxiliar;
							desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
								*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
						}
						alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
					}else if(opcao_escolhida_menu_terciario == 1 && botao_enter_acionado == 1){
						*caractere_utilizado_nas_bordas = -60;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, *largura_atual*2,
				   			*altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 2 && botao_enter_acionado == 1){
						*caractere_utilizado_nas_bordas = -51;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, *largura_atual*2,
				   			*altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 3 && botao_enter_acionado == 1){
						*caractere_utilizado_nas_bordas = -80;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, *largura_atual*2,
				   			*altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 4 && botao_enter_acionado == 1){
						*caractere_utilizado_nas_bordas = -79;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, *largura_atual*2,
				   			*altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 5 && botao_enter_acionado == 1){
						*caractere_utilizado_nas_bordas = -78;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, *largura_atual*2,
				   			*altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 6 && botao_enter_acionado == 1){
						*caractere_utilizado_nas_bordas = -37;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, *largura_atual*2,
				   			*altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(botao_esc_acionado == 1){
						botao_esc_acionado = 0;
						opcao_escolhida_menu_terciario = 0;
						break;
					}
				}
			}
			if(opcao_escolhida_menu_secundario == 1 && botao_enter_acionado == 1){
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
				printf("                                                                                          ");
				while(botao_esc_acionado != 1){
					botao_enter_acionado = 0;
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
					printf("Character used in the maze walls:                                  "); 
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
					if(*caractere_utilizado_nas_paredes != -80 && *caractere_utilizado_nas_paredes != -79 &&
						*caractere_utilizado_nas_paredes != -78 && *caractere_utilizado_nas_paredes != -37){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("Choose a character by code  > %c <   ", *caractere_utilizado_nas_paredes);
						
					}else{
						printf("   Choose a character by code  > %c <   ", *caractere_utilizado_nas_paredes);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
					if(*caractere_utilizado_nas_paredes == -80){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("%c%c%c%c%c%c%c%c%c                      ", 176, 176, 176, 176, 176, 176, 176, 176, 176);
					}else{
						printf("   %c%c%c%c%c%c%c%c%c                      ", 176, 176, 176, 176, 176, 176, 176, 176, 176);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+3);
					if(*caractere_utilizado_nas_paredes == -79){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("%c%c%c%c%c%c%c%c%c            ", 177, 177, 177, 177, 177, 177, 177, 177, 177);
					}else{
						printf("   %c%c%c%c%c%c%c%c%c            ", 177, 177, 177, 177, 177, 177, 177, 177, 177);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+4);
					if(*caractere_utilizado_nas_paredes == -78){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("%c%c%c%c%c%c%c%c%c                           ", 178, 178, 178, 178, 178, 178, 178, 178, 178);
					}else{
						printf("   %c%c%c%c%c%c%c%c%c                           ", 178, 178, 178, 178, 178, 178, 178, 178, 178);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
					if(*caractere_utilizado_nas_paredes == -37){
						alterar_a_cor(verde_brilhante, preto);
						printf("  %c", 35);
						alterar_a_cor(branco, preto);
						printf("%c%c%c%c%c%c%c%c%c                                                                              ", 219, 219, 219, 219, 219, 219, 219, 219, 219);
					}else{
						printf("   %c%c%c%c%c%c%c%c%c                                                                              ", 219, 219, 219, 219, 219, 219, 219, 219, 219);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+8);
					printf("Press ESC to return to the main menu");
					desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, &opcao_escolhida_menu_terciario, 0, 
						5, 0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
					if(opcao_escolhida_menu_terciario == 0 && botao_enter_acionado == 1){
						reposicionar_indicador_do_console(coordenada_x_menu_principal+31, coordenada_y_menu_principal+1);
						printf("      ");
						alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
						int valor_auxiliar = -1;
						valor_auxiliar = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+33, 
							coordenada_y_menu_principal+1, 3);
						if(valor_auxiliar >= 0){
							*caractere_utilizado_nas_paredes = valor_auxiliar;
							desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
								(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, 
								*caractere_utilizado_nas_paredes);
							desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, 
								(*coordenada_x_fim_2*2)+4, *coordenada_y_fim_2+10, *cor_do_retangulo_final, 
								*caractere_utilizado_nas_paredes);
						}
						alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
					}else if(opcao_escolhida_menu_terciario == 1 && botao_enter_acionado == 1){
						*caractere_utilizado_nas_paredes = -80;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, *caractere_utilizado_nas_paredes);
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
								*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 2 && botao_enter_acionado == 1){
						*caractere_utilizado_nas_paredes = -79;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, *caractere_utilizado_nas_paredes);
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
								*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 3 && botao_enter_acionado == 1){
						*caractere_utilizado_nas_paredes = -78;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, *caractere_utilizado_nas_paredes);
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
								*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 4 && botao_enter_acionado == 1){
						*caractere_utilizado_nas_paredes = -37;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, *caractere_utilizado_nas_paredes);
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
								*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
					}else if(botao_esc_acionado == 1){
						botao_esc_acionado = 0;
						opcao_escolhida_menu_terciario = 0;
						break;
					}
				}
			}
			if(opcao_escolhida_menu_secundario == 2 && botao_enter_acionado == 1){
				reposicionar_indicador_do_console(coordenada_x_menu_principal+21, coordenada_y_menu_principal+3);
				printf("   ");
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
				int auxiliar = inserir_e_analisar_entrada_do_usuario(coordenada_x_menu_principal+21, coordenada_y_menu_principal+3, 
					3);
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
				if(auxiliar >= 0){
					*sleep = auxiliar;
				}
			}
			if(opcao_escolhida_menu_secundario == 3 && botao_enter_acionado == 1){
				if(*confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto == 0){
					*confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto = 1;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+31, coordenada_y_menu_principal+4, 
						0, branco, verde, branco, vermelho);
				}else{
					*confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto = 0;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+31, coordenada_y_menu_principal+4, 
						1, branco, verde, branco, vermelho);
				}
			}
			botao_enter_acionado = 0;
		}
	}
	if(opcao_escolhida == 3){
		while(botao_esc_acionado != 1){
			int opcao_escolhida_menu_terciario = 0, posicao_da_seta_na_horizontal = 0;
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
			printf("Change color scheme:                                                                         ");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
			printf("   Start of the maze   > ");

			alterar_a_cor(*cor_do_retangulo_inicial, preto);
			printf("%c%c", 219, 219);
			alterar_a_cor(branco, preto);
			printf(" <");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
			printf("   End of the maze     > ");
			alterar_a_cor(*cor_do_retangulo_final, preto);
			printf("%c%c", 219, 219);
			alterar_a_cor(branco, preto);
			printf(" <         ");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+3);
			printf("   Intermediate maze walls - Moving forward    > ", 160, 166);
			alterar_a_cor(*cor_das_paredes_intermediarias, preto);
			printf("%c%c", 219, 219);
			alterar_a_cor(branco, preto);
			printf(" <     ");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+4);
			if(*cor_das_paredes_intermediarias_segunda_passada == preto){
				printf("   Intermediate maze walls - Returning         > ");
				printf("|  |");
				printf("<                        ");
			}else{
				printf("   Intermediate maze walls - Returning         > ");
				alterar_a_cor(*cor_das_paredes_intermediarias_segunda_passada, preto);
				printf("%c%c", 219, 219);
				alterar_a_cor(branco, preto);
				printf(" <                        ");
			}
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
			printf("   Maze edges          > ");
			alterar_a_cor(*cor_das_bordas, preto);
			printf("%c%c", 219, 219);
			alterar_a_cor(branco, preto);
			printf(" <");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+6);
			printf("                                                                                                                            ");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
			printf("                                                                                                               ");
			reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+8);
			printf("Press ESC to return to the main menu");
			desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, &opcao_escolhida_menu_secundario, 0, 
				5, 0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
			if(opcao_escolhida_menu_secundario == 0 && botao_enter_acionado == 1){
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
				printf("Start of the maze:               ");
				desenhar_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 0);
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
				printf("                             ");
				int copia_posicao_da_seta_na_horizontal = 0;
				while(botao_esc_acionado != 1){
					botao_enter_acionado = 0;
					mostrar_opcao_atual_no_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
						*cor_do_retangulo_inicial, 0, 0);
					posicao_da_seta_na_horizontal = desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
					&opcao_escolhida_menu_terciario, posicao_da_seta_na_horizontal, 
				    4, 4, &botao_enter_acionado, &botao_esc_acionado, 0, 1, 1, 0);
					cor cor_auxiliar = *cor_do_retangulo_inicial;
					if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = azul;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, azul, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = roxo;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, roxo, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = azul_brilhante;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, azul_brilhante, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = roxo_brilhante;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, roxo_brilhante, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = verde;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, verde, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = amarelo;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, amarelo, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = verde_brilhante;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, verde_brilhante, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = amarelo_brilhante;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, amarelo_brilhante, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = ciano;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, ciano, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = cinza_claro;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, cinza_claro, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = ciano_brilhante;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, ciano_brilhante, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = branco;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, branco, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = vermelho;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, vermelho, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = cinza_escuro;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, cinza_escuro, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_do_retangulo_inicial = vermelho_brilhante;
						desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, (*coordenada_x_inicio_2*2)+4, 
							*coordenada_y_inicio_2+10, vermelho_brilhante, *caractere_utilizado_nas_paredes);
					}
					mostrar_opcao_atual_no_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
						cor_auxiliar, 1, 0);
					if(botao_esc_acionado == 1){
						botao_esc_acionado = 0;
						botao_enter_acionado = 0;
						break;
					}
				}
			}
			if(opcao_escolhida_menu_secundario == 1 && botao_enter_acionado == 1){
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
				printf("End of the maze:                  ");
				desenhar_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 0);
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
				printf("                                                          ");
				int copia_posicao_da_seta_na_horizontal = 0;
				while(botao_esc_acionado != 1){
					botao_enter_acionado = 0;
					mostrar_opcao_atual_no_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
						*cor_do_retangulo_final, 0, 0);
					posicao_da_seta_na_horizontal = desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
					&opcao_escolhida_menu_terciario, posicao_da_seta_na_horizontal, 
				    4, 4, &botao_enter_acionado, &botao_esc_acionado, 0, 1, 1, 0);
					cor cor_auxiliar = *cor_do_retangulo_final;
					if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = azul;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, azul, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = roxo;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, roxo, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = azul_brilhante;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, azul_brilhante, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = roxo_brilhante;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, roxo_brilhante, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = verde;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, verde, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = amarelo;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, amarelo, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = verde_brilhante;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, verde_brilhante, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = amarelo_brilhante;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, amarelo_brilhante, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = ciano;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, ciano, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = cinza_claro;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, cinza_claro, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = ciano_brilhante;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, ciano_brilhante, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = branco;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, branco, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = vermelho;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, vermelho, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = cinza_escuro;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, cinza_escuro, *caractere_utilizado_nas_paredes);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_do_retangulo_final = vermelho_brilhante;
						desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
							*coordenada_y_fim_2+10, vermelho_brilhante, *caractere_utilizado_nas_paredes);
					}
					mostrar_opcao_atual_no_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
						cor_auxiliar, 1, 0);
					if(botao_esc_acionado == 1){
						botao_esc_acionado = 0;
						botao_enter_acionado = 0;
						break;
					}
				}
			}
			if(opcao_escolhida_menu_secundario == 2 && botao_enter_acionado == 1){
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
				printf("   Intermediate maze walls - Moving forward:          ");
				desenhar_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 0);
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
				printf("                                                          ");
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+6);
				printf("The algorithm analyzes which of the available paths it can move through, building walls in the process (1st pass), ", 161, 161, 135, 166);
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
				printf("when there are no more valid paths, it backtracks through the walls already built (2nd pass)", 198, 160, 160, 130, 160, 161, 166);
				int copia_posicao_da_seta_na_horizontal = 0;
				while(botao_esc_acionado != 1){
					botao_enter_acionado = 0;
					mostrar_opcao_atual_no_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
						*cor_das_paredes_intermediarias, 0, 0);
					posicao_da_seta_na_horizontal = desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
					&opcao_escolhida_menu_terciario, posicao_da_seta_na_horizontal, 
				    4, 4, &botao_enter_acionado, &botao_esc_acionado, 0, 1, 1, 0);
				    cor cor_auxiliar = *cor_das_paredes_intermediarias;
					if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = azul;
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = roxo;
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = azul_brilhante;
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = roxo_brilhante;
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = verde;
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = amarelo;
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = verde_brilhante;
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = amarelo_brilhante;
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = ciano;
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = cinza_claro;
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = ciano_brilhante;
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = branco;
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = vermelho;
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = cinza_escuro;
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias = vermelho_brilhante;
					}
					mostrar_opcao_atual_no_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
						cor_auxiliar, 1, 0);
					if(botao_esc_acionado == 1){
						botao_esc_acionado = 0;
						botao_enter_acionado = 0;
						break;
					}
				}
			}
			if(opcao_escolhida_menu_secundario == 3 && botao_enter_acionado == 1){
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
				printf("   Intermediate maze walls - Returning:             ");
				desenhar_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 1);
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
				printf("                                                          ");
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+6);
				printf("The Algorithm analyzes which of the available paths it can advance through, building walls in the process (1st pass), ");
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
				printf("when there are no more valid paths, it backtracks through the walls already built (2nd pass)");
				int copia_posicao_da_seta_na_horizontal = 0;
				while(botao_esc_acionado != 1){
					botao_enter_acionado = 0;
					mostrar_opcao_atual_no_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
						*cor_das_paredes_intermediarias_segunda_passada, 0, 1);
					posicao_da_seta_na_horizontal = desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
					&opcao_escolhida_menu_terciario, posicao_da_seta_na_horizontal, 
				    4, 4, &botao_enter_acionado, &botao_esc_acionado, 0, 1, 1, 1);
				    cor cor_auxiliar = *cor_das_paredes_intermediarias_segunda_passada;
					if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = azul;
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = roxo;
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = azul_brilhante;
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = roxo_brilhante;
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = verde;
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = amarelo;
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = verde_brilhante;
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = amarelo_brilhante;
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = ciano;
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = cinza_claro;
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = ciano_brilhante;
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = branco;
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = vermelho;
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = cinza_escuro;
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = vermelho_brilhante;
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_das_paredes_intermediarias_segunda_passada = preto;
					}
					mostrar_opcao_atual_no_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
						cor_auxiliar, 1, 1);
					if(botao_esc_acionado == 1){
						botao_esc_acionado = 0;
						botao_enter_acionado = 0;
						break;
					}
				}
			}
			if(opcao_escolhida_menu_secundario == 4 && botao_enter_acionado == 1){
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
				printf("Maze edges:          ");
				desenhar_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 0);
				reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
				printf("                                                          ");
				int copia_posicao_da_seta_na_horizontal = 0;
				while(botao_esc_acionado != 1){
					botao_enter_acionado = 0;
					mostrar_opcao_atual_no_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
						*cor_das_bordas, 0, 0);
					posicao_da_seta_na_horizontal = desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
					&opcao_escolhida_menu_terciario, posicao_da_seta_na_horizontal, 
				    4, 4, &botao_enter_acionado, &botao_esc_acionado, 0, 1, 1, 0);
				    cor cor_auxiliar = *cor_das_bordas;
					if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_bordas = azul;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_bordas = roxo;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_bordas = azul_brilhante;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 0 && botao_enter_acionado == 1){
						*cor_das_bordas = roxo_brilhante;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_bordas = verde;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_bordas = amarelo;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_bordas = verde_brilhante;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 1 && botao_enter_acionado == 1){
						*cor_das_bordas = amarelo_brilhante;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_bordas = ciano;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_bordas = cinza_claro;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_bordas = ciano_brilhante;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 3 && posicao_da_seta_na_horizontal == 2 && botao_enter_acionado == 1){
						*cor_das_bordas = branco;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 0 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_das_bordas = vermelho;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 1 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_das_bordas = cinza_escuro;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}else if(opcao_escolhida_menu_terciario == 2 && posicao_da_seta_na_horizontal == 3 && botao_enter_acionado == 1){
						*cor_das_bordas = vermelho_brilhante;
						desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
							*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
					}
					mostrar_opcao_atual_no_menu_de_selecao_de_cores(coordenada_x_menu_principal, coordenada_y_menu_principal+1, 
						cor_auxiliar, 1, 0);
					if(botao_esc_acionado == 1){
						botao_esc_acionado = 0;
						botao_enter_acionado = 0;
						break;
					}
				}
			}
		}
	}
	if(opcao_escolhida == 4){
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
		printf("   Show general information                                                    ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
		printf("   Show matrix    ");
		if(*mostrar_matriz == 0){
			printf("                 ");
			alterar_a_cor(branco, vermelho);
			printf("OFF");
			alterar_a_cor(branco, preto);
		}else{
			printf("                 ");
			alterar_a_cor(branco, verde);
			printf("ON");
			alterar_a_cor(branco, preto);
		}
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
		printf("   Show stack size          ");
		if(*mostrar_tamanho_da_pilha == 0){
			printf("       ");
			alterar_a_cor(branco, vermelho);
			printf("OFF");
			alterar_a_cor(branco, preto);
		}else{
			printf("       ");
			alterar_a_cor(branco, verde);
			printf("ON");
			alterar_a_cor(branco, preto);
		}
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+3);
		printf("   Show stack capacity         ");

		if(*mostrar_capacidade_da_pilha == 0){
			printf("    ");
			alterar_a_cor(branco, vermelho);
			printf("OFF");
			alterar_a_cor(branco, preto);
		}else{
			printf("    ");
			alterar_a_cor(branco, verde);
			printf("ON");
			alterar_a_cor(branco, preto);
		}
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+4);
		printf("   Show current coordinate  ");

		if(*mostrar_coordenada_atual == 0){
			printf("       ");
			alterar_a_cor(branco, vermelho);
			printf("OFF");
			alterar_a_cor(branco, preto);
			printf("                          ");
		}else{
			printf("       ");
			alterar_a_cor(branco, verde);
			printf("ON");
			alterar_a_cor(branco, preto);
			printf("                         ");
		}
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
		printf("   Show sleep value                ");
		if(*mostrar_valor_da_variavel_sleep == 0){
			alterar_a_cor(branco, vermelho);
			printf("OFF");
			alterar_a_cor(branco, preto);
		}else{
			alterar_a_cor(branco, verde);
			printf("ON");
			alterar_a_cor(branco, preto);
		}
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+6);
		printf("   Show total memory allocations and deallocations      ");

		if(*mostrar_total_de_alocacoes_e_desalocacoes == 0){
			printf("      ");
			alterar_a_cor(branco, vermelho);
			printf("OFF");
			alterar_a_cor(branco, preto);
		}else{
			printf("      ");
			alterar_a_cor(branco, verde);
			printf("ON");
			alterar_a_cor(branco, preto);
		}
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
		printf("   Show total of analyzed movement possibilities              ");
		if(*mostrar_total_de_possibilidades_analisadas == 0){
			alterar_a_cor(branco, vermelho);
			printf("OFF");
			alterar_a_cor(branco, preto);
		}else{
			alterar_a_cor(branco, verde);
			printf("ON");
			alterar_a_cor(branco, preto);
		}
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+8);
		printf("Press ESC to return to the main menu");
		while(botao_esc_acionado != 1){
			desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+1, &opcao_escolhida_menu_secundario, 0, 
				7, 0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
			if(opcao_escolhida_menu_secundario == 0 && botao_enter_acionado == 1){
				if(*largura_atual > 53 && *altura_atual > 16 && *confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto == 0
					&& *mostrar_matriz == 0){
					botao_enter_acionado = 0;
					int opcao_escolhida_menu_terciario = 0;
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
					printf("  ");
					desenhar_ou_apagar_o_aviso_sobre_problemas_visuais_entre_matriz_e_labirinto(coordenada_x_menu_principal+62, 
						coordenada_y_menu_principal+1, 0);
					while(botao_esc_acionado != 1 && botao_enter_acionado != 1){
						desenhar_seta(coordenada_x_menu_principal+63, coordenada_y_menu_principal+5, 
							&opcao_escolhida_menu_terciario, 0, 4, 0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
						if(opcao_escolhida_menu_terciario == 1 && botao_enter_acionado == 1) break;
						else if(opcao_escolhida_menu_terciario == 0 && botao_enter_acionado == 1){
							int opcao_escolhida_menu_quartenario = 0;
							botao_enter_acionado = 0;
							reposicionar_indicador_do_console(coordenada_x_menu_principal+62, coordenada_y_menu_principal+5);
							printf("    Sim > Deseja n%co receber mais esse aviso?", 198);
							reposicionar_indicador_do_console(coordenada_x_menu_principal+62, coordenada_y_menu_principal+6);
							printf("             Sim");
							reposicionar_indicador_do_console(coordenada_x_menu_principal+62, coordenada_y_menu_principal+7);
							printf("             N%co                    ", 198);
							reposicionar_indicador_do_console(coordenada_x_menu_principal+62, coordenada_y_menu_principal+8);
							printf("                                   ");
							while(botao_esc_acionado != 1 && botao_enter_acionado != 1){
								desenhar_seta(coordenada_x_menu_principal+72, coordenada_y_menu_principal+6, 
									&opcao_escolhida_menu_quartenario, 0, 2, 0, &botao_enter_acionado, &botao_esc_acionado, 1, 1, 1, 0);
								if(opcao_escolhida_menu_quartenario == 0 && botao_enter_acionado == 1){ 
									*confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto = 1;
									reposicionar_indicador_do_console(coordenada_x_menu_principal+62, coordenada_y_menu_principal+6);
									printf("             Sim > Essa op%c%co poder%c ser desfeita posterimoente no menu de ajustes", 135, 198, 160);	
									alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
									getch();
									alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
									reposicionar_indicador_do_console(coordenada_x_menu_principal+79, coordenada_y_menu_principal+6);
									printf("                                                                 ");
									botao_enter_acionado = 1;
									if(*mostrar_matriz == 0){
										*mostrar_matriz = 1;
										imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+1, 
											1, branco, verde, branco, vermelho);
									}
									else{
										*mostrar_matriz = 0;
										imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+1, 
											0, branco, verde, branco, vermelho);
									}
								}else if(opcao_escolhida_menu_quartenario == 1 && botao_enter_acionado == 1){
									botao_enter_acionado = 1;
									if(*mostrar_matriz == 0){
										*mostrar_matriz = 1;
										imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+1, 
											1, branco, verde, branco, vermelho);
									}
									else{
										*mostrar_matriz = 0;
										imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+1, 
											0, branco, verde, branco, vermelho);
									}
								}
								if(botao_esc_acionado == 1){
									botao_esc_acionado = botao_enter_acionado = 0;
									break;
								}
							}
							reposicionar_indicador_do_console(coordenada_x_menu_principal+62, coordenada_y_menu_principal+5);
							printf("    Sim                                      ");
							reposicionar_indicador_do_console(coordenada_x_menu_principal+62, coordenada_y_menu_principal+6);
							printf("    N%co         ", 198);
							reposicionar_indicador_do_console(coordenada_x_menu_principal+62, coordenada_y_menu_principal+7);
							printf("    Ativar e mudar a largura para 53");
							reposicionar_indicador_do_console(coordenada_x_menu_principal+62, coordenada_y_menu_principal+8);
							printf("    Ativar e mudar a altura para 16");
						}else if(opcao_escolhida_menu_terciario == 2 && botao_enter_acionado == 1){
							desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
								*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
							*largura_atual = 53;
							if(*coordenada_x_inicio_1 >= *largura_atual){
								desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
									(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, preto, 
									*caractere_utilizado_nas_paredes);
								if(*coordenada_x_fim_1 >= *largura_atual-1 && *coordenada_y_inicio_1 == *coordenada_y_fim_1){
									*coordenada_x_inicio_1 = *largura_atual-2;
									*coordenada_x_inicio_2 = *largura_atual-1;
								}else{
									*coordenada_x_inicio_1 = *largura_atual-1;
									*coordenada_x_inicio_2 = *largura_atual;
								}
								desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
									(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, 
									*caractere_utilizado_nas_paredes);
							}
							if(*coordenada_x_fim_1 >= *largura_atual){
								desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
									*coordenada_y_fim_2+10, preto, *caractere_utilizado_nas_paredes);
								if(*coordenada_x_inicio_1 >= *largura_atual-1 && *coordenada_y_inicio_1 == *coordenada_y_fim_1){
									*coordenada_x_fim_1 = *largura_atual-2;
									*coordenada_x_fim_2 = *largura_atual-1;
								}else{
									*coordenada_x_fim_1 = *largura_atual-1;
									*coordenada_x_fim_2 = *largura_atual;
								}
								desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
									*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);	
							}
							desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
								*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
							if(*mostrar_matriz == 0){
								*mostrar_matriz = 1;
								imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+1, 
									1, branco, verde, branco, vermelho);
							}
							else{
								*mostrar_matriz = 0;
								imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+1, 
									0, branco, verde, branco, vermelho);
							}
						}else if(opcao_escolhida_menu_terciario == 3 && botao_enter_acionado == 1){
							desenhar_bordas_da_matriz(1, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
								*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
							*altura_atual = 16;
							if(*coordenada_y_inicio_1 >= *altura_atual){
								desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
									(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, preto, 
									*caractere_utilizado_nas_paredes);
								if(*coordenada_y_fim_1 >= *altura_atual-1 && *coordenada_x_inicio_1 == *coordenada_x_fim_1){
									*coordenada_y_inicio_1 = *altura_atual-2;
									*coordenada_y_inicio_2 = *altura_atual-2;
								}else{
									*coordenada_y_inicio_1 = *altura_atual-1;
									*coordenada_y_inicio_2 = *altura_atual-1;
								}
								desenhar_retangulo((*coordenada_x_inicio_1*2)+5, *coordenada_y_inicio_1+10, 
									(*coordenada_x_inicio_2*2)+4, *coordenada_y_inicio_2+10, *cor_do_retangulo_inicial, 
									*caractere_utilizado_nas_paredes);
							}
							if(*coordenada_y_fim_1 >= *altura_atual){
								desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
									*coordenada_y_fim_2+10, preto, *caractere_utilizado_nas_paredes);
								if(*coordenada_y_inicio_1 >= *altura_atual-1 && *coordenada_x_inicio_1 == *coordenada_x_fim_1){
									*coordenada_y_fim_1 = *altura_atual-2;
									*coordenada_y_fim_2 = *altura_atual-2;
								}else{
									*coordenada_y_fim_1 = *altura_atual-1;
									*coordenada_y_fim_2 = *altura_atual-1;
								}
								desenhar_retangulo((*coordenada_x_fim_1*2)+5, *coordenada_y_fim_1+10, (*coordenada_x_fim_2*2)+4, 
									*coordenada_y_fim_2+10, *cor_do_retangulo_final, *caractere_utilizado_nas_paredes);
							}
							desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
								*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
							if(*mostrar_matriz == 0){
								*mostrar_matriz = 1;
								imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+1, 
									1, branco, verde, branco, vermelho);
							}
							else{
								*mostrar_matriz = 0;
								imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+1, 
									0, branco, verde, branco, vermelho);
							}
						}
					}
					desenhar_ou_apagar_o_aviso_sobre_problemas_visuais_entre_matriz_e_labirinto(coordenada_x_menu_principal+62, 
						coordenada_y_menu_principal+1, 1);
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+6);
					printf("   Mostrar total de aloca%c%ces e desaloca%c%ces de mem%cria ", 135, 228, 135, 228, 162);
					if(*mostrar_total_de_alocacoes_e_desalocacoes == 0){
						printf("      ");
						alterar_a_cor(branco, vermelho);
						printf("DESLIGADO");
						alterar_a_cor(branco, preto);
					}else{
						alterar_a_cor(branco, verde);
						printf("LIGADO");
						alterar_a_cor(branco, preto);
					}
					reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
					printf("   Mostrar total de possibilidades analisadas na movimenta%c%co ",135, 198);
					if(*mostrar_total_de_possibilidades_analisadas == 0){
						alterar_a_cor(branco, vermelho);
						printf("DESLIGADO");
						alterar_a_cor(branco, preto);
					}else{
						alterar_a_cor(branco, verde);
						printf("LIGADO");
						alterar_a_cor(branco, preto);
					}
					if(botao_esc_acionado == 1) botao_esc_acionado = 0;
				}else{
					if(*mostrar_matriz == 0){
						*mostrar_matriz = 1;
						imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+1, 
							1, branco, verde, branco, vermelho);
					}
					else{
						*mostrar_matriz = 0;
						imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+1, 
							0, branco, verde, branco, vermelho);
					}
				}
			}else if(opcao_escolhida_menu_secundario == 1 && botao_enter_acionado == 1){
				if(*mostrar_tamanho_da_pilha == 0){
					*mostrar_tamanho_da_pilha = 1;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+2, 
						1, branco, verde, branco, vermelho);
				}else{
					*mostrar_tamanho_da_pilha = 0;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+2, 
						0, branco, verde, branco, vermelho);
				}
			}else if(opcao_escolhida_menu_secundario == 2 && botao_enter_acionado == 1){
				if(*mostrar_capacidade_da_pilha == 0){
					*mostrar_capacidade_da_pilha = 1;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+3, 
						1, branco, verde, branco, vermelho);
				}else{
					*mostrar_capacidade_da_pilha = 0;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+3, 
						0, branco, verde, branco, vermelho);
				}
			}else if(opcao_escolhida_menu_secundario == 3 && botao_enter_acionado == 1){
				if(*mostrar_coordenada_atual == 0){
					*mostrar_coordenada_atual = 1;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+4, 
						1, branco, verde, branco, vermelho);
				}else{
					*mostrar_coordenada_atual = 0;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+4, 
						0, branco, verde, branco, vermelho);
				}
			}else if(opcao_escolhida_menu_secundario == 4 && botao_enter_acionado == 1){
				if(*mostrar_valor_da_variavel_sleep == 0){
					*mostrar_valor_da_variavel_sleep = 1;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+5, 
						1, branco, verde, branco, vermelho);
				}else{
					*mostrar_valor_da_variavel_sleep = 0;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+35, coordenada_y_menu_principal+5, 
						0, branco, verde, branco, vermelho);
				}
			}else if(opcao_escolhida_menu_secundario == 5 && botao_enter_acionado == 1){
				if(*mostrar_total_de_alocacoes_e_desalocacoes == 0){
					*mostrar_total_de_alocacoes_e_desalocacoes = 1;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+62, coordenada_y_menu_principal+6, 
						1, branco, verde, branco, vermelho);
				}else{
					*mostrar_total_de_alocacoes_e_desalocacoes = 0;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+62, coordenada_y_menu_principal+6, 
						0, branco, verde, branco, vermelho);
				}
			}else if(opcao_escolhida_menu_secundario == 6 && botao_enter_acionado == 1){
				if(*mostrar_total_de_possibilidades_analisadas == 0){
					*mostrar_total_de_possibilidades_analisadas = 1;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+62, coordenada_y_menu_principal+7, 
						1, branco, verde, branco, vermelho);
				}else{
					*mostrar_total_de_possibilidades_analisadas = 0;
					imprimir_string_desligado_ou_ligado(coordenada_x_menu_principal+62, coordenada_y_menu_principal+7, 
						0, branco, verde, branco, vermelho);
				}
			}
			botao_enter_acionado = 0;
		}
	}
	if(opcao_escolhida == 5){
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
		printf("  ");
		lista_sequencial* memoria = alocar_dinamicamente_uma_lista_sequencial(*altura_atual);
		int total_de_alocacoes = 3+*altura_atual, total_de_desalocacoes = 0, 
		total_de_possibilidades_analisadas_na_movimentacao_do_labirinto = 0;
		inseir_coordenada_na_lista_sequencial(memoria, &total_de_alocacoes, *coordenada_x_inicio_1, *coordenada_y_inicio_1);
		int** matriz = (int**)malloc(*altura_atual*sizeof(int*));
		for(int a=0; a<*altura_atual; a++) matriz[a] = calloc(*largura_atual, sizeof(int));
		matriz[*coordenada_y_inicio_1][*coordenada_x_inicio_1] = 1;
		matriz[*coordenada_y_fim_1][*coordenada_x_fim_1] = 4;
		int variavel_de_ajuste_do_printf_da_matriz_nas_colunas, variavel_de_ajuste_do_printf_da_matriz_nas_linhas;
		if((*largura_atual > 53 && *altura_atual <= 16) || (*largura_atual > 53 && *altura_atual > 16)){
			variavel_de_ajuste_do_printf_da_matriz_nas_colunas = coordenada_x_menu_principal+2;
			variavel_de_ajuste_do_printf_da_matriz_nas_linhas = coordenada_y_menu_principal+*altura_atual+11;
		}else if((*largura_atual <= 53 && *altura_atual > 16) || (*largura_atual <= 53 && *altura_atual <= 16)){
			variavel_de_ajuste_do_printf_da_matriz_nas_colunas = coordenada_x_menu_principal+*largura_atual*2+3;
			variavel_de_ajuste_do_printf_da_matriz_nas_linhas = coordenada_y_menu_principal+10;
		}
		if(*mostrar_matriz == 1){
			for(int a=0; a<*altura_atual; a++){
				for(int b=0; b<*largura_atual; b++){
					reposicionar_indicador_do_console(variavel_de_ajuste_do_printf_da_matriz_nas_colunas+b, 
						variavel_de_ajuste_do_printf_da_matriz_nas_linhas+a);
					printf("%d", matriz[a][b]);
				}
			}
		}
		int posicoes_das_informacoes_ligadas[7];
		for(int a=0; a<7; a++) posicoes_das_informacoes_ligadas[a] = 0;
		int contador = 0, coordendada_x_base_para_visualizar_dados = coordenada_x_menu_principal+74;
		if(*mostrar_tamanho_da_pilha == 1){
			 posicoes_das_informacoes_ligadas[contador] = 1;
			 contador++;
		}
		if(*mostrar_capacidade_da_pilha == 1){
			posicoes_das_informacoes_ligadas[contador] = 2;
			contador++;	
		}
		if(*mostrar_coordenada_atual == 1){
			posicoes_das_informacoes_ligadas[contador] = 3;
			contador++;	
		}
		if(*mostrar_valor_da_variavel_sleep == 1){
			posicoes_das_informacoes_ligadas[contador] = 4;
			contador++;	
		}
		if(*mostrar_total_de_alocacoes_e_desalocacoes == 1){
			posicoes_das_informacoes_ligadas[contador] = 5;
			contador++;
			posicoes_das_informacoes_ligadas[contador] = 6;
			contador++;
		}
		if(*mostrar_total_de_possibilidades_analisadas == 1){
			posicoes_das_informacoes_ligadas[contador] = 7;
			contador++;	
		}
		contador = 8;
		int auxiliar_1, auxiliar_2, auxiliar_3, auxiliar_4, auxiliar_5, auxiliar_6, auxiliar_7;
		for(int a=6; a>=0; a--){
			if(posicoes_das_informacoes_ligadas[a] == 7){
				auxiliar_7 = contador;
				contador--;
			}else if(posicoes_das_informacoes_ligadas[a] == 6){
				auxiliar_6 = contador;
				contador--;
			}else if(posicoes_das_informacoes_ligadas[a] == 5){
				auxiliar_5 = contador;
				contador--;
			}else if(posicoes_das_informacoes_ligadas[a] == 4){
				auxiliar_4 = contador;
				contador--;
			}else if(posicoes_das_informacoes_ligadas[a] == 3){
				auxiliar_3 = contador;
				contador--;
			}else if(posicoes_das_informacoes_ligadas[a] == 2){
				auxiliar_2 = contador;
				contador--;
			}else if(posicoes_das_informacoes_ligadas[a] == 1){
				auxiliar_1 = contador;
				contador--;
			}
		}
		if(*mostrar_tamanho_da_pilha == 1){
			reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_1);
			printf("Stack size == %d", memoria->tamanho);
		}
		if(*mostrar_capacidade_da_pilha == 1){
			reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_2);
			printf("Stack capacity == %d", memoria->capacidade);
		}
		if(*mostrar_coordenada_atual == 1){
			reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_3);
			printf("Current coordinate == (%d, %d)", *coordenada_x_inicio_1, *coordenada_y_inicio_1);
		}
		if(*mostrar_valor_da_variavel_sleep == 1){
			reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_4);
			printf("Sleep == %d", *sleep);
		}
		if(*mostrar_total_de_alocacoes_e_desalocacoes == 1){
			reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_5);
			printf("Total of memory allocations == %d", total_de_alocacoes);

		}
		if(*mostrar_total_de_alocacoes_e_desalocacoes == 1){
			reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_6);
			printf("Total of memory deallocations == %d", total_de_desalocacoes);
		}
		if(*mostrar_total_de_possibilidades_analisadas == 1){
			reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_7);
			printf("Total possibilities analyzed in the maze movement == %d", total_de_possibilidades_analisadas_na_movimentacao_do_labirinto);
		}
		srand(time(0));
		int quatro_proximas_possibilidades_a_serem_analisadas[4], primeira_execulcao_da_funcao_decidir_caminho_a_ser_tomado = 1,
			caminho_escolhido;
		for(int a=0; a<4; a++) quatro_proximas_possibilidades_a_serem_analisadas[a] = rand()%4;
		int coordenada_x_ini_1_copia = *coordenada_x_inicio_1, coordenada_y_ini_1_copia = *coordenada_y_inicio_1,
			coordenada_x_ini_2_copia = *coordenada_x_inicio_2, coordenada_y_ini_2_copia = *coordenada_y_inicio_2;
		while(memoria->tamanho != 0){
			while(!kbhit() && memoria->tamanho != 0){
				for(int a=0; a<4; a++) quatro_proximas_possibilidades_a_serem_analisadas[a] = rand()%4;
				caminho_escolhido = decidir_caminho_a_ser_tomado(matriz, memoria->vetor[(memoria->tamanho)-1].coordenada_x_1, 
					memoria->vetor[(memoria->tamanho)-1].coordenada_y_1, *largura_atual, *altura_atual, 
					quatro_proximas_possibilidades_a_serem_analisadas, &primeira_execulcao_da_funcao_decidir_caminho_a_ser_tomado, 
					&total_de_possibilidades_analisadas_na_movimentacao_do_labirinto);
				if(caminho_escolhido == cima){
					coordenada_y_ini_1_copia--;
					coordenada_y_ini_2_copia--;
					matriz[coordenada_y_ini_1_copia][coordenada_x_ini_1_copia] = 2;
					inseir_coordenada_na_lista_sequencial(memoria, &total_de_alocacoes, coordenada_x_ini_1_copia, 
						coordenada_y_ini_1_copia);
					desenhar_retangulo((coordenada_x_ini_1_copia*2)+5, coordenada_y_ini_1_copia+10, (coordenada_x_ini_2_copia*2)+4, 
						coordenada_y_ini_2_copia+10, *cor_das_paredes_intermediarias, *caractere_utilizado_nas_paredes);
				}else if(caminho_escolhido == baixo){
					coordenada_y_ini_1_copia++;
					coordenada_y_ini_2_copia++;
					matriz[coordenada_y_ini_1_copia][coordenada_x_ini_1_copia] = 2;
					inseir_coordenada_na_lista_sequencial(memoria, &total_de_alocacoes, coordenada_x_ini_1_copia, 
						coordenada_y_ini_1_copia);
					desenhar_retangulo((coordenada_x_ini_1_copia*2)+5, coordenada_y_ini_1_copia+10, (coordenada_x_ini_2_copia*2)+4, 
						coordenada_y_ini_2_copia+10, *cor_das_paredes_intermediarias, *caractere_utilizado_nas_paredes);
				}else if(caminho_escolhido == direita){
					coordenada_x_ini_1_copia++;
					coordenada_x_ini_2_copia++;
					matriz[coordenada_y_ini_1_copia][coordenada_x_ini_1_copia] = 2;
					inseir_coordenada_na_lista_sequencial(memoria, &total_de_alocacoes, coordenada_x_ini_1_copia, 
						coordenada_y_ini_1_copia);
					desenhar_retangulo((coordenada_x_ini_1_copia*2)+5, coordenada_y_ini_1_copia+10, (coordenada_x_ini_2_copia*2)+4, 
						coordenada_y_ini_2_copia+10, *cor_das_paredes_intermediarias, *caractere_utilizado_nas_paredes);
				}else if(caminho_escolhido == esquerda){
					coordenada_x_ini_1_copia--;
					coordenada_x_ini_2_copia--;
					matriz[coordenada_y_ini_1_copia][coordenada_x_ini_1_copia] = 2;
					inseir_coordenada_na_lista_sequencial(memoria, &total_de_alocacoes, coordenada_x_ini_1_copia, 
						coordenada_y_ini_1_copia);
					desenhar_retangulo((coordenada_x_ini_1_copia*2)+5, coordenada_y_ini_1_copia+10, (coordenada_x_ini_2_copia*2)+4, 
						coordenada_y_ini_2_copia+10, *cor_das_paredes_intermediarias, *caractere_utilizado_nas_paredes);
				}else if(caminho_escolhido == -1){
					if(memoria->tamanho > 1){
						desenhar_retangulo((coordenada_x_ini_1_copia*2)+5, coordenada_y_ini_1_copia+10, (coordenada_x_ini_2_copia*2)+4, 
						coordenada_y_ini_2_copia+10, *cor_das_paredes_intermediarias_segunda_passada, *caractere_utilizado_nas_paredes);
						remover_coordenada_da_lista_sequencial(memoria, &total_de_desalocacoes);
						coordenada_x_ini_1_copia = memoria->vetor[(memoria->tamanho)-1].coordenada_x_1;
						coordenada_x_ini_2_copia = coordenada_x_ini_1_copia+1;
						coordenada_y_ini_1_copia = memoria->vetor[(memoria->tamanho)-1].coordenada_y_1;
						coordenada_y_ini_2_copia = coordenada_y_ini_1_copia;
					}else memoria->tamanho = 0;
				}
				if(*mostrar_matriz == 1){
					reposicionar_indicador_do_console(variavel_de_ajuste_do_printf_da_matriz_nas_colunas+memoria->vetor[(memoria->tamanho)-1].coordenada_x_1, 
						variavel_de_ajuste_do_printf_da_matriz_nas_linhas+memoria->vetor[(memoria->tamanho)-1].coordenada_y_1);
					if(caminho_escolhido == -1 && memoria->tamanho > 1) printf("3");
					else if(caminho_escolhido != -1) printf("2");
				}
				if(*mostrar_tamanho_da_pilha == 1){
					reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_1);
					printf("Stack size == %d  ", memoria->tamanho);
				}
				if(*mostrar_capacidade_da_pilha == 1){
					reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_2);
					printf("Stack capacity == %d  ", memoria->capacidade);
				}
				if(*mostrar_coordenada_atual == 1){
					reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_3);
					printf("Current coordinate == (%d, %d)  ", coordenada_x_ini_1_copia, coordenada_y_ini_1_copia);
				}
				if(*mostrar_valor_da_variavel_sleep == 1){
					reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_4);
					printf("Sleep == %d", *sleep);	
				}
				if(*mostrar_total_de_alocacoes_e_desalocacoes == 1){
					reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_5);
					printf("Total of memory allocations == %d  ", total_de_alocacoes);
				}
				if(*mostrar_total_de_alocacoes_e_desalocacoes == 1){
					reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_6);
					printf("Total of memory deallocations == %d  ", total_de_desalocacoes);

				}
				if(*mostrar_total_de_possibilidades_analisadas == 1){
					reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_7);
					printf("Total possibilities analyzed in the maze movement == %d", total_de_possibilidades_analisadas_na_movimentacao_do_labirinto);
				}
				Sleep(*sleep);
			}
			if(memoria->tamanho == 0){
				if(*mostrar_total_de_alocacoes_e_desalocacoes == 1){
					total_de_desalocacoes = total_de_desalocacoes + 3 + *altura_atual;
					reposicionar_indicador_do_console(coordendada_x_base_para_visualizar_dados, auxiliar_6);
					printf("Total of memory deallocations == %d", total_de_desalocacoes);
				}
				reposicionar_indicador_do_console(coordenada_x_menu_principal, *altura_atual+variavel_de_ajuste_do_printf_da_matriz_nas_linhas+1);
				printf("Maze drawing completed  ");

				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
				getch();
				alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
				break;
			}
			int a = getch();
			if(a == 27) break;
		}
		system("cls");
		desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, 
			*largura_atual*2, *altura_atual, *caractere_utilizado_nas_bordas, *cor_das_bordas);
		desalocar_dinamicamente_lista_sequencial(memoria);
		for(int a=0; a<*altura_atual; a++) free(matriz[a]);
		free(matriz);
	}

	botao_enter_acionado = 0;
}

void desenhar_menu_principal(int coordenada_x_menu_principal, int coordenada_y_menu_principal, int largura_minima, 
	int largura_maxima, int altura_minima, int altura_maxima, int largura_atual, int altura_atual, int coordenada_x_inicio_1, 
	int coordenada_y_inicio_1, int coordenada_x_inicio_2, int coordenada_y_inicio_2, int coordenada_x_fim_1, 
	int coordenada_y_fim_1, int coordenada_x_fim_2, int coordenada_y_fim_2){
	int opcao_escolhida = 5, limite_de_opcoes = 6, botao_esc_acionado = 0, botao_enter_acionado = 0, sleep = 80; 
	int mostrar_matriz = 0, mostrar_tamanho_da_pilha = 0, mostrar_capacidade_da_pilha = 0,
		mostrar_coordenada_atual = 0, mostrar_valor_da_variavel_sleep = 0, 
		mostrar_total_de_alocacoes_e_desalocacoes = 0, mostrar_total_de_possibilidades_analisadas = 0, 
		confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto = 0; 
	cor cor_padrao_do_retangulo_inicial = azul, cor_padrao_do_ratangulo_final = amarelo, 
	cor_padrao_das_paredes_intermediarias = vermelho, cor_padrao_das_paredes_intermediarias_segunda_passada = roxo, 
	cor_padrao_das_bordas = branco;
	char caractere_padrao_utilizado_nas_bordas = 196, caractere_padrao_utilizado_nas_paredes = 219;
	desenhar_bordas_da_matriz(0, coordenada_x_menu_principal, coordenada_y_menu_principal+9, largura_atual*2, altura_atual, 
		caractere_padrao_utilizado_nas_bordas, cor_padrao_das_bordas);
	while(botao_esc_acionado != 1){
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal);
		printf("When you're ready, press ENTER on the option \"Start\" to start drawing the maze", 135, 198, 135);
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+1);
		printf("Main menu:                                 ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+2);
		printf("   Change reference coordinates            ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+3);
		printf("   Resize borders                                             ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+4);
		printf("   Change drawing characters and general adjustments         ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+5);
		printf("   Change color scheme                     ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+6);
		printf("   Show general information                                          ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+7);
		printf("   Start                                                                                ");
		reposicionar_indicador_do_console(coordenada_x_menu_principal, coordenada_y_menu_principal+8);
		printf("Press ESC to exit the program       ");
		desenhar_retangulo((coordenada_x_inicio_1*2)+5, coordenada_y_inicio_1+10, (coordenada_x_inicio_2*2)+4, 
			coordenada_y_inicio_2+10, cor_padrao_do_retangulo_inicial, caractere_padrao_utilizado_nas_paredes);
		desenhar_retangulo((coordenada_x_fim_1*2)+5, coordenada_y_fim_1+10, (coordenada_x_fim_2*2)+4, coordenada_y_fim_2+10, 
			cor_padrao_do_ratangulo_final, caractere_padrao_utilizado_nas_paredes);
		desenhar_seta(coordenada_x_menu_principal, coordenada_y_menu_principal+2, &opcao_escolhida, 0, limite_de_opcoes, 
			0, &botao_enter_acionado, &botao_esc_acionado, 1, 0, 1, 0);
		if(botao_enter_acionado == 1){
			inserir_dados(coordenada_x_menu_principal, coordenada_y_menu_principal, opcao_escolhida, largura_minima, 
				largura_maxima, altura_minima, altura_maxima, &largura_atual, &altura_atual, &cor_padrao_do_retangulo_inicial, 
				&cor_padrao_do_ratangulo_final, &cor_padrao_das_paredes_intermediarias, 
				&cor_padrao_das_paredes_intermediarias_segunda_passada, &cor_padrao_das_bordas, 
				&caractere_padrao_utilizado_nas_bordas, &caractere_padrao_utilizado_nas_paredes, &sleep, &coordenada_x_inicio_1, 
				&coordenada_y_inicio_1, &coordenada_x_inicio_2, &coordenada_y_inicio_2, &coordenada_x_fim_1, &coordenada_y_fim_1, 
				&coordenada_x_fim_2, &coordenada_y_fim_2, &mostrar_matriz, &mostrar_tamanho_da_pilha, 
				&mostrar_capacidade_da_pilha, &mostrar_coordenada_atual, &mostrar_valor_da_variavel_sleep, 
				&mostrar_total_de_alocacoes_e_desalocacoes, &mostrar_total_de_possibilidades_analisadas, 
				&confirmacao_de_sim_do_aviso_sobre_matriz_e_tamanho_do_labirinto);	
			botao_enter_acionado = 0;
		}else if(botao_esc_acionado == 1) reposicionar_indicador_do_console(0, coordenada_y_menu_principal+10+altura_atual);
	}
}
