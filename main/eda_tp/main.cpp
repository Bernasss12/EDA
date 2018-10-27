#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

//Caso as os codigos ANSI nao funcionem no seu command line comente a linha seguinte.
//#define COM_CORES

#define RED ""
#define BLUE ""
#define CLEAR ""

#ifdef COM_CORES
	#define RED "\u001b[31m"
	#define BLUE "\u001b[34m"
	#define CLEAR "\u001b[0m"
#endif




void main()
{
	char ficheiro_matriz_a[] = { "d:\\EDA\\dados1.txt" };
	char ficheiro_matriz_b[] = { "d:\\EDA\\dados2.txt" };

	Matriz matriz_a, matriz_b, matriz_c;

	if (!matriz_a.Ler(ficheiro_matriz_a))
	{
		printf(RED "Falhou a leitura da matriz A.\n" CLEAR);
		system("pause");
		exit(1);
	}
	if (!matriz_b.Ler(ficheiro_matriz_b))
	{
		printf(RED "Falhou a leitura da matriz B.\n" CLEAR);
		system("pause");
		exit(1);
	}

	//Teste de Leitura e Impressao
	printf(BLUE "Leitura das Matrizes apartir de ficheiros:\nMatriz A:\n" CLEAR);
	matriz_a.Escrever();
	printf(BLUE "Matriz B:\n" CLEAR);
	matriz_b.Escrever();
	system("pause");
	system("cls");

	//Teste de Atribuicao, Soma e Multiplicacao;
	printf(BLUE "Matriz C = Matriz A:\nMatriz C Antes:\n" CLEAR);
	matriz_c = Matriz(3, 3);
	matriz_c.Escrever();
	matriz_c = matriz_a;
	printf(BLUE "Matriz C Depois:\n" CLEAR);
	matriz_c.Escrever();

	printf(BLUE "Matriz A + Matriz B:\n" CLEAR);
	matriz_c = matriz_a + matriz_b;
	matriz_c.Escrever();
	printf(BLUE "Matriz A * Matriz B:\n" CLEAR);
	matriz_c = matriz_a * matriz_b;
	matriz_c.Escrever();
	system("pause");
	system("cls");

	//Teste de DecomposiçãoLU
	printf(BLUE "Teste de Decomposicao LU:\nMatriz LU da matriz A:\n" CLEAR);
	matriz_c = matriz_a.DecomporLU();
	matriz_c.Escrever();
	printf(BLUE "Matriz L da matriz A:\n" CLEAR);
	matriz_c = matriz_a.DecomporLU('L');
	matriz_c.Escrever();
	printf(BLUE "Matriz U da matriz A:\n" CLEAR);
	matriz_c = matriz_a.DecomporLU('U');
	matriz_c.Escrever();
	system("pause");
	system("cls");

}

