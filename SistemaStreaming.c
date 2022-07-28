#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Funcoes.h"

/* programa que simula um sistema de streaming de videos e gerenciamento de clientes,
feito na disciplina de Introducao a Engenharia de Software, Unioeste
Alunos do grupo: Guilherme Monsani e Davi Rafael Franke, sob a orientação do professor Newton Spolaor */

int main()
{
	system("chcp 1252 > nul");// para poder ler as strings corretamente no idioma portugues
	setlocale(LC_ALL, "portuguese");// ajusta a linguagem para portugues;
	SistemaStreaming sistema;//sistema sempre será 1, entao n precisa alocar memoria
	menu(&sistema);// executa o menu e submenus do sistema
	system("pause");
	return 0;
}