#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Ponto.h"
#include "Rectangulo.h"
#include "Janela.h"
#include "Hist.h"
#include "Dados.h"

#define VERDE RGB(0,255,0)
#define AZUL RGB(0,0,255)
#define VERMELHO RGB(255,0,0)

void main()
{
	char fich_leitura[] = { "d:\\EDA\\dados.txt" };
	char fich_escrita[] = { "d:\\EDA\\dados_processados.txt" };
	Janela janela;
	HWND janelaId;
	Dados dados;
	if (dados.CarregarDadosFicheiro(fich_leitura));
	else{
		printf("Carregamento falhou.");
		system("pause");
	}

	dados.ImprimirDados();
	if (!dados.DescarregarDadosFichriro(fich_escrita)) printf("Erro ao imprimir para o ficheiro");

	Hist h(dados.FreqAbsoluta(), dados.Classes());
	h.SetCorBins(RGB(200, 0, 0));
	h.SetCorEixos(RGB(200, 200, 200));
	if (janela.Criar((char*)"Minha Janela")) {
		if ((janelaId = janela.ObterId()) != NULL) {
			h.Desenhar(&janela);
			MSG msg;
			while (GetMessage(&msg, 0, 0, 0)) {
				DispatchMessage(&msg);
			}
			printf("O programa terminou\n");
		}
	}
	printf("\n\n\n\n\n");
	system("pause");
}

