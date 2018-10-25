#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

void main()
{
	char ficheiro_matriz[] = { "d:\\EDA\\dados1.txt" };

	Matriz matriz_a, matriz_b, matriz_c;

	if (!matriz_a.Ler(ficheiro_matriz))
	{
		printf("Falhou a leitura da matriz.");
		system("pause");
		exit(1);
	}

	matriz_a.Escrever();

	matriz_c = matriz_a.DecomporLU();

	matriz_c.Escrever();

	printf("\n\n\n\n\n");
	system("pause");
}

