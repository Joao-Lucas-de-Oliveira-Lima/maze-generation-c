#include "interface/stack/stack.h"
#include "interface/interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(){
	alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 0);
	system("cls");
	system("color 0F");
	int coordenada_x_menu_principal = 4, coordenada_y_menu_principal = 0, largura_atual = 40, altura_atual = 20, 
		largura_minima = 3, largura_maxima = 79, altura_minima = 3, altura_maxima = 32, coordenada_x_inicio_1 = 20, 
		coordenada_y_inicio_1 = 6, coordenada_x_inicio_2 = 21, coordenada_y_inicio_2 = 6, coordenada_x_fim_1 = 20, 
		coordenada_y_fim_1 = 7, coordenada_x_fim_2 = 21, coordenada_y_fim_2 = 7;
	desenhar_menu_principal(coordenada_x_menu_principal, coordenada_y_menu_principal, largura_minima, largura_maxima, altura_minima,
		altura_maxima, largura_atual, altura_atual, coordenada_x_inicio_1, coordenada_y_inicio_1, coordenada_x_inicio_2, 
		coordenada_y_inicio_2, coordenada_x_fim_1, coordenada_y_fim_1, coordenada_x_fim_2, coordenada_y_fim_2);
	alterar_o_tamanho_e_vizibilidade_do_indicador_do_console(1, 1);
	return 0;
}