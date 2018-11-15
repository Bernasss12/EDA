#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Ponto.h"
#include "Rectangulo.h"

void main()
{
	Rectangulo rect = Rectangulo(-5, -5, 5, 5);

	printf("%f, %d", rect.ObterArea(), rect.ObterPerimetro());

	printf("\n\n\n\n\n");
	system("pause");
}

