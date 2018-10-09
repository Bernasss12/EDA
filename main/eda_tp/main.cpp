#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <Windows.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

COORD localizacao_cursor = { 0, 0 };

float *valores;
int largura_coluna = 16;
float max, min, media_total, desvio_padrao;
float max_frequencia_relativa = 0;	
int nlinhas;
int nclasses;

int freqAbsoluta(int, int, int);
float freqRelativa(int, int, int);
void printCell(std::string, char, int);
void printCell(std::string, char, int, float);
void printCell(std::string, char, int, int);
void printErro(std::string, int);
void printInput(int);
void printCabecalho();
void maximoFreqRelativa(int, int);
void printLinha(int, int, int);
void printDiv(int, int, int, char);
std::string freqRelativaGrafica(int);
void hist(int, int);
float media(float, int);
float desvioPadrao(float, int);
void quebraLinha();
void lerFicheiro(char*);
void perguntarFicheiro();
void limpaLinhas(int);

COORD GetConsoleCursorPosition(HANDLE);

void main()
{
	char nome_ficheiro[] = { "d:\\EDA\\dados.txt" };
				  
	//perguntarFicheiro();
	
	lerFicheiro(nome_ficheiro);

	maximoFreqRelativa(nclasses, nlinhas);
	hist(nclasses, nlinhas);

	
	
	delete[] valores;
	printf("\n\n\n\n\n");
	system("pause");
}

void perguntarFicheiro()
{
	COORD start = { 0,  3};
	char drive;
	char pasta_opcao;
	int pasta = 0;
	char pastas[20];
	std::string caminho_final = "";
	printDiv(4, 1, 1, 'T');
	printCell((std::string)"Escolher o ficheiro", 'C', 4);	
	quebraLinha();
	printDiv(4, 1, 1, 'C');
	do //Pedir a drive
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), start);
		printf("\r");
		printCell((std::string)"Em que drive se encontra o ficheiro? [C, D ou E]", 'L', 4);
		quebraLinha();
		printInput(4);
		printDiv(4, 1, 1, 'B');
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), localizacao_cursor);
		std::cin.clear();         // Limpa buffer para evitar loops
		fflush(stdin);            // Limpa buffer para evitar loops
		scanf_s(" %c", &drive);
		drive = toupper(drive);
		if(drive != 'C' && drive != 'D' && drive != 'E')
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), start);
			printErro((std::string)"Drive invalida", 4);
			printDiv(4, 1, 1, 'B');
			limpaLinhas(5);
			Sleep(500);
		}
	} while (drive != 'C' && drive != 'D' && drive != 'E');
	do //Adicionar pastas ao caminho do ficheiro
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), start);
		printf("\r");
		printCell((std::string)"Deseja adicionar uma pasta ao caminho? (max. 5) [S, N]", 'L', 4);
		quebraLinha();
		printInput(4);
		printDiv(4, 1, 1, 'B');
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), localizacao_cursor);
		std::cin.clear();         // Limpa buffer para evitar loops
		fflush(stdin);            // Limpa buffer para evitar loops
		scanf_s(" %c", &pasta_opcao);
		pasta_opcao = toupper(pasta_opcao);
		if (pasta_opcao != 'S' && pasta_opcao != 'N')
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), start);
			printErro((std::string)"Opcao invalida, tente S ou N", 4);
			printDiv(4, 1, 1, 'B');
			limpaLinhas(5);
			Sleep(500);
		} else if( pasta_opcao == 'S')
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), start);
			printCell((std::string)"Escreva o nome da pasta:", 'L', 4);
			quebraLinha();
			printInput(4);
			printDiv(4, 1, 1, 'B');
			limpaLinhas(5);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), localizacao_cursor);
			std::cin.clear();         // Limpa buffer para evitar loops
			fflush(stdin);            // Limpa buffer para evitar loops
			//fgets(pastas);
			pasta++;
		}
	} while (pasta_opcao != 'N');
	printf(pastas);
}

void lerFicheiro(char* nome_ficheiro)
{
	FILE *pfile;
	pfile = fopen(nome_ficheiro, "r");
	if (pfile == NULL)
		printf("Erro na abertura do ficheiro: %s\n", nome_ficheiro);
	else
	{
		fscanf(pfile, "%d", &nclasses);
		fscanf(pfile, "%d", &nlinhas);
		valores = new float[nlinhas];

		max = min = 0;
		float soma = 0;

		for (int i = 0; i < nlinhas; i++) {
			fscanf(pfile, "%f", &valores[i]);
			if (valores[i] > max) max = valores[i];
			if (valores[i] < min || i == 0) min = valores[i];
			soma += valores[i];
		}

		media_total = media(soma, nlinhas);
		desvio_padrao = desvioPadrao(soma, nlinhas);

		fclose(pfile);
	}
}

void hist(int classes, int linhas)
{
	printDiv(4, 1, 1, 'T');
	printCell((std::string)"Histograma", 'C', 4);
	quebraLinha();
	printDiv(4, 1, 4, 'C');
	printCabecalho();
	printDiv(4, 4, 4, 'C');
	for (int i = 0; i < classes; i++) printLinha(i, classes, linhas);
	printDiv(4, 4, 1, 'C');
	printCell((std::string)"Amostras: ", 'O', 4, nlinhas);
	quebraLinha();
	printDiv(4, 1, 2, 'C');	
	printCell((std::string)"Minimo: ", 'O', 2, min);
	printCell((std::string)"Maximo: ", 'O', 2, max);	
	quebraLinha();
	printDiv(4, 2, 2, 'C');
	printCell((std::string)"Media: ", 'O', 2, media_total);
	printCell((std::string)"Desvio padrao: ", 'O', 2, desvio_padrao);
	quebraLinha();
	printDiv(4, 2, 1, 'B');
}

int freqAbsoluta(int classe, int classes, int nvalores)
{
	int cmin = ((max - min) / classes) * classe;
	int cmax = ((max - min) / classes) * (classe + 1);
	int count = 0;

	for(int i = 0; i < nvalores; i++)
	{
		if ((valores[i] >= cmin) && (valores[i] < cmax)) count++;
		if ((classe + 1 == classes) && (valores[i] == cmax)) count++;
	}

	return count;
}

float freqRelativa(int classe, int classes, int nvalores)
{
	return ((freqAbsoluta(classe, classes, nvalores) / (float)nvalores) * 100);
}

float media(float soma, int nvalores)
{
	return (soma / nvalores);
}

float desvioPadrao(float soma, int nvalores)
{
	float somatorio = 0;
	for (int i = 0; i < nvalores; i++) somatorio += pow((valores[i] - media_total), 2);
	return sqrt((somatorio / nvalores));
}

void maximoFreqRelativa(int classes, int nvalores)
{
	for(int i = 0; i < classes; i++)
	{
		if (freqRelativa(i, classes, nvalores) > max_frequencia_relativa) max_frequencia_relativa = freqRelativa(i, classes, nvalores);
	}
}

void printRelativaGrafica(int freq_relativa, int colspan)
{
	int espaco = (colspan * largura_coluna) - 2;
	int div = ceil(max_frequencia_relativa / espaco);
	int tamanho = freq_relativa / div;
	printf("%c ", 186);
	for (int i = 0; i < tamanho; i++) printf("%c", 178);
	for (int i = 0; i < espaco - tamanho; i++) printf("%c", 176);
	printf(" ");
}

void printCell(std::string string, char mode, int colspan)
{	
	printf("%c", 186);
	int espaco = (largura_coluna*colspan) + (colspan - 1) - std::strlen(string.c_str());
	switch (mode)
	{
	case 'L':
		printf(" ");
		printf(string.c_str());
		for (int i = 0; i < espaco-1 ; i++) printf(" ");
		break;
	case 'C':
		for (int i = 0; i < floor(espaco  / 2.0); i++) printf(" ");
		printf(string.c_str());
		for (int i = 0; i < ceil(espaco / 2.0); i++) printf(" ");
		break;;
	case 'R':
		for (int i = 0; i < espaco-1; i++) printf(" ");
		printf(string.c_str());
		printf(" ");
		break;;
	}
}

void printCell(std::string string, char mode, int colspan, float valor)
{
	float val = valor;
	int digitos = 0;
	if (val <= 0) digitos = 1;
	while (val >= 1) {
		val /= 10;
		digitos++;
	}
	int espaco = (largura_coluna * colspan + (colspan - 3)) - (digitos + 3) - (string.length());
	std::string resultado = string + "%.2f";
	printf("%c ", 186);
	printf(resultado.c_str(), valor);
	if (mode == '%') printf("%%");
	else printf(" ");
	for (int i = 0; i < espaco; i++) printf(" ");
}

void printCell(std::string string, char mode, int colspan, int valor)
{
	float val = valor;
	int digitos = 0;
	if (val < 0) digitos = 1;
	while (val >= 1) {
		val /= 10.0;
		digitos++;
	}
	int espaco = (largura_coluna * colspan) + (colspan - 1) - (digitos + 2) - (string.length());
	std::string resultado = string + "%d";
	printf("%c ", 186);
	printf(resultado.c_str(), valor);
	if (mode == '%') printf("%%");
	else printf(" ");
	for (int i = 0; i < espaco; i++) printf(" ");
}

void printErro(std::string string, int colspan)
{
	int espaco = (largura_coluna * colspan) + (colspan - 2) - (string.length());
	printf("\r%c ", 186);
	for (int i = 0; i < ceil(espaco / 2.0); i++) printf(" ");
	printf(string.c_str());
	for (int i = 0; i < floor(espaco / 2.0); i++) printf(" ");
	printf("%c\n", 186);
}

void printInput(int colspan)
{
	int espaco = (largura_coluna*colspan) + (colspan) - 1;
	printf("%c > ", 186);
	//Obter posicao do cursor;
	localizacao_cursor = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	for (int i = 0; i < espaco - 3; i++) printf(" ");
	printf("%c\n", 186);
}

void printCabecalho()
{

	printCell("Valores", 'C', 1);
	printCell("F. Absoluta", 'C', 1);
	printCell("F. Relativa", 'C', 1);
	printCell("Rep. Grafica", 'C', 1);
	printf("%c\n", 186);
}

void printLinha(int linha, int nclasses, int nlinhas)
{
	std::string valor = (std::to_string((int)ceil(((max-min) / nclasses)*linha))) + '-' + (std::to_string((int)ceil(((max-min) / nclasses)*(linha+1))));
	printCell(valor, 'L', 1);
	std::string abs = std::to_string(freqAbsoluta(linha, nclasses, nlinhas));
	printCell(abs, 'C', 1);
	printCell("", '%', 1, freqRelativa(linha, nclasses, nlinhas));
	printRelativaGrafica(freqRelativa(linha, nclasses, nlinhas), 1);
	printf("%c\n", 186);
}

void printDiv(int colspan, int cols_acima, int cols_abaixo, char type)
{
	int max_cols = colspan;
	switch (type)
	{
	case 'T':
		printf("%c", 201);
		for(int c = 1; c <= max_cols; c++)
		{
			for (int i = 0; i < largura_coluna; i++) printf("%c", 205);
			if (c != max_cols) {
				if(((c % (max_cols/cols_acima)) == 0) && ((c % (max_cols / cols_abaixo)) == 0)) printf("%c", 206);
				else if ((c % (max_cols / cols_acima)) == 0) printf("%c", 202);
				else if ((c % (max_cols / cols_abaixo)) == 0) printf("%c", 203);
				else printf("%c", 205);
			}
		}
		printf("%c\n", 187);
		break;
	case 'C':
		printf("%c", 204);
		for (int c = 1; c <= max_cols; c++)
		{
			for (int i = 0; i < largura_coluna; i++) printf("%c", 205);
			if (c != max_cols) {
				if (((c % (max_cols / cols_acima)) == 0) && ((c % (max_cols / cols_abaixo)) == 0)) printf("%c", 206);
				else if ((c % (max_cols / cols_acima)) == 0) printf("%c", 202);
				else if ((c % (max_cols / cols_abaixo)) == 0) printf("%c", 203);
				else printf("%c", 205);
			}
		}
		printf("%c\n", 185);
		break;
	case 'B':
		printf("%c", 200);
		for (int c = 1; c <= max_cols; c++)
		{
			for (int i = 0; i < largura_coluna; i++) printf("%c", 205);
			if (c != max_cols) {
				if (((c % (max_cols / cols_acima)) == 0) && ((c % (max_cols / cols_abaixo)) == 0)) printf("%c", 206);
				else if ((c % (max_cols / cols_acima)) == 0) printf("%c", 202);
				else if ((c % (max_cols / cols_abaixo)) == 0) printf("%c", 203);
				else printf("%c", 205);
			}
		}
		printf("%c\n", 188);
		break;
	}
}

void quebraLinha()
{
	printf("%c\n", 186);
}

void limpaLinhas(int linhas)
{
	for(int i = 0; i < linhas; i++)
	{
		printf("                                                                                   \n");
	}
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}
