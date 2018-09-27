#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>

float *valores;
int largura_coluna = 16;

int freqAbsoluta(int, int, int);
float freqRelativa(int, int, int);
void printCell(char[], char);
void printCabecalho();
void printLinha(int, int, int);
void printDiv(int, char);
std::string freqRelativaGrafica(int);

void main()
{
	FILE *pfile;
	char nome_ficheiro[] = { "d:\\EDA\\dados.txt" };
	int nlinhas; // Nº de dados que o ficheiro contém
	int nclasses; // Nº de classes do histograma
	int i;
				  
	pfile = fopen(nome_ficheiro, "r");
	if (pfile == NULL)
		printf("Erro na abertura do ficheiro: %s\n", nome_ficheiro);
	else
	{
		fscanf(pfile, "%d", &nclasses);
		fscanf(pfile, "%d", &nlinhas);
		valores = new float[nlinhas];
		for (i = 0; i < nlinhas; i++)
			fscanf(pfile, "%f", &valores[i]);
		printDiv(4, 'T');
		printCabecalho();
		printDiv(4, 'C');
		for(i = 0; i < nclasses; i++) printLinha(i, nclasses, nlinhas);
		printDiv(4, 'B');
		delete[] valores;
		system("pause");
	}
}

void hist(int classes, int linhas, float valores[])
{
	
}

int freqAbsoluta(int classe, int classes, int nValores)
{
	int min = (100 / classes) * classe;
	int max = (100 / classes) * (classe + 1);
	int count = 0;

	for(int i = 0; i < nValores; i++)
	{
		if ((valores[i] >= min) && (valores[i] < max)) count++;
		if ((classe + 1 == classes) && (valores[i] == max)) count++;
	}

	return count;
}

float freqRelativa(int classe, int classes, int nValores)
{
	return ((freqAbsoluta(classe, classes, nValores)/(float)nValores)*100);
}

void printRelativaGrafica(int freq_relativa)
{
	int espaco = largura_coluna - 10;
	int dez = ((int)freq_relativa) / 5;
	int uni = (int)freq_relativa - (10 * (2*dez));
	printf("%c", 186);
	for (int i = 0; i < ceil(espaco / 2); i++) printf(" ");
	for (int i = 0; i < dez; i++) printf("%c", 178);
	if (uni < 3) printf(" ");
	else if (uni > 3 && uni < 6) printf("%c", 177);
	else if (uni > 6)  printf("%c", 176);
	for (int i = 0; i < floor(espaco / 2) + (10 - dez - 1); i++) printf(" ");
}

void printCell(std::string string, char mode)
{	
	printf("%c", 186);
	int espaco = largura_coluna - std::strlen(string.c_str());
	switch (mode)
	{
	case 'L':
		printf(string.c_str());
		for (int i = 0; i < espaco; i++) printf(" ");
		break;
	case 'C':
		if ((std::strlen(string.c_str()) % 2) != 0) printf(" ");
		for (int i = 0; i < ceil(espaco / 2); i++) printf(" ");
		printf(string.c_str());
		for (int i = 0; i < floor(espaco / 2); i++) printf(" ");
		break;;
	case 'R':
		for (int i = 0; i < espaco; i++) printf(" ");
		printf(string.c_str());
		break;;
	case '%':
		espaco = largura_coluna - 6;
		for (int i = 0; i < ceil(espaco / 2); i++) printf(" ");
		std::string::size_type sz;		
		float val = std::stof(string, &sz);
		printf("%.2f%%", val);
		for (int i = 0; i < floor(espaco / 2); i++) printf(" ");
		break;;
	}
}

void printCabecalho()
{

	printCell("Valores", 'C');
	printCell("F. Absoluta", 'C');
	printCell("F. Relativa", 'C');
	printCell("Rep. Grafica", 'C');
	printf("%c\n", 186);
}

void printLinha(int linha, int nclasses, int nlinhas)
{
	std::string valor = (std::to_string((100 / nclasses)*linha)) + '-' + (std::to_string((100 / nclasses)*(linha+1)));
	printCell(valor.c_str(), 'C');
	std::string abs = std::to_string(freqAbsoluta(linha, nclasses, nlinhas));
	printCell(abs.c_str(), 'C');
	std::string rel = std::to_string(freqRelativa(linha, nclasses, nlinhas));
	printCell(rel.c_str(), '%');
	printRelativaGrafica(freqRelativa(linha, nclasses, nlinhas));
	printf("%c\n", 186);
}

void printDiv(int cols, char type)
{
	switch (type)
	{
	case 'T':
		printf("%c", 201);
		for(int c = 1; c <= cols; c++)
		{
			for (int i = 0; i < largura_coluna; i++) printf("%c", 205);
			if (c != cols) printf("%c", 203);
		}
		printf("%c\n", 187);
		break;
	case 'C':
		printf("%c", 204);
		for (int c = 1; c <= cols; c++)
		{
			for (int i = 0; i < largura_coluna; i++) printf("%c", 205);
			if (c != cols) printf("%c", 206);
		}
		printf("%c\n", 185);
		break;
	case 'B':
		printf("%c", 200);
		for (int c = 1; c <= cols; c++)
		{
			for (int i = 0; i < largura_coluna; i++) printf("%c", 205);
			if (c != cols) printf("%c", 202);
		}
		printf("%c\n", 188);
		break;
	}
}
