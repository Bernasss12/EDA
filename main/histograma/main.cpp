#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Rectangulo.h"
#include "Janela.h"
#include "Rede.h"

#define VERDE RGB(0,255,0)
#define AZUL RGB(0,0,255)
#define VERMELHO RGB(255,0,0)

#define RAIO 

void main()
{
	char fich_mapa[] = { "d:\\EDA\\Mapa.txt" };
	char fich_rede[] = { "d:\\EDA\\Rede.txt" };
	char imgpath[] = { "d:\\EDA\\MAPA.bmp" };

	Janela janela;
	HWND janelaId;

	Rede rede = Rede();
	rede.ObterNos(fich_mapa, fich_rede);

	if (janela.Criar((char*)"Arvore binaria", (char*)imgpath)) {
		if ((janelaId = janela.ObterId()) != NULL) {
			for (int i = 0; i < rede.nnos; i++) {
				rede.nos[i].Desenhar(janelaId);
			}
			rede.DesenharLinhas(janelaId);
			MSG msg;
			while (GetMessage(&msg, 0, 0, 0)) {
				DispatchMessage(&msg); 
				if (janela.Click()) {
				}
			}
		}
	}

	printf("\n\n\n\n\n");
}

