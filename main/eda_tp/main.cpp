#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Ponto.h"
#include "Rectangulo.h"
#include "Janela.h"

#define VERDE RGB(0,255,0)
#define AZUL RGB(0,0,255)
#define VERMELHO RGB(255,0,0)

void main()
{
	Janela janela;
	HWND janelaId;
	printf("Programa que utiliza outra janela para os resultados.\n");
	if (janela.Criar((char*)"Minha Janela")) {
		if ((janelaId = janela.ObterId()) != NULL) {
			Rectangulo r(242, 177, 892, 377);
			printf("\nArea do rectangulo: %0.2f\n", r.ObterArea());
			printf("\nPerimetro do rectangulo: %d     %d\n", r.ObterPerimetro(), WM_DESTROY);
			r.Desenhar(janelaId, VERDE);
			MSG msg;
			while (GetMessage(&msg, 0, 0, 0)) {
				DispatchMessage(&msg);
				if (janela.Click()) {
					if (r.Contem(Ponto(janela.ObterPonto().ObterX(), janela.ObterPonto().ObterY())) == true)
						r.Desenhar(janelaId, VERDE);
					else
						r.Desenhar(janelaId, VERMELHO);
				}
			}
		}
	}
	printf("\n\n\n\n\n");
	system("pause");
}

