#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

void main()
{
	char ficheiro_matriz_a[] = { "d:\\EDA\\dados1.txt" };
	char ficheiro_matriz_b[] = { "d:\\EDA\\dados2.txt" };

	Matriz matriz_a, matriz_b;

	if (!matriz_a.Ler(ficheiro_matriz_a))
	{
		printf("Falhou a leitura da matriz A.");
		system("pause");
		exit(1);
	}
	if (!matriz_b.Ler(ficheiro_matriz_b))
	{
		printf("Falhou a leitura da matriz B.");
		system("pause");
		exit(1);
	}

	//Determinante
	printf("Matriz A: \n");
	matriz_a.Escrever();
	float determinante = matriz_a.calcularDet();
	printf("Determinante de A:\n %.2f", determinante);

	//Inversa
	printf("\n\nMatriz B: \n");
	matriz_b.Escrever();
	printf("Inversa de B: \n");
	matriz_b.obterInversa().Escrever();

	printf("\n\n\n\n\n");
	system("pause");
}

