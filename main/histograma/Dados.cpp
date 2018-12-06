#define _CRT_SECURE_NO_WARNINGS
#include "Dados.h"
#include <cstdio>
#include <algorithm>
#include <ctime>


Dados::Dados()
{
	int* valores = NULL;
	int nclasses = 0, nvalores = 0, min = 0, max = 0, media = 0;
}


Dados::~Dados()
{
}

int* Dados::FreqAbsoluta()
{
	Ordenar();
	int* freqAbs = new int[nclasses];
	for (int i = 0; i < nclasses; i++) freqAbs[i]=0;
	int range = max - min;
	float div = range / nclasses;
	for (int i = 0; i < nvalores; i++)
	{
		freqAbs[(int)(floor(valores[i]/div))]++;
		if (valores[i] == max) freqAbs[nclasses - 1]++;
	}
	return freqAbs;
}

int* Dados::FreqRelativa()
{
	int* freqRel = FreqAbsoluta();
	for(int i = 0; i < nclasses; i++)
	{
		if (i != 0) freqRel[i] += freqRel[i - 1];
	}
	return freqRel;
}

float Dados::CalcularDesvioPadrao()
{
	float somatorio = 0;
	for (int i = 0; i < nvalores; i++) somatorio += pow((valores[i] - ObterMedia()), 2);
	return sqrt((somatorio / nvalores));
}

float Dados::ObterMediana()
{
	int* med = Ordenar();
	if((nvalores%2) == 0)
	{
		return ((valores[(nvalores / 2)] + valores[(nvalores / 2)+1]) / 2);
	}else
	{
		return (valores[(int)ceil(nvalores / 2)]);
	}
	return 0;
}

int* Dados::Ordenar()
{
	int* sorted = valores;
	std::sort(sorted, sorted + nvalores);
	min = sorted[0];
	max = sorted[nvalores - 1];
	return sorted;
}

float Dados::ObterMedia()
{
	int sum = 0;
	for(int i = 0; i < nvalores; i++)
	{
		sum += valores[i];
	}
	return sum / nvalores;
}

bool Dados::CarregarDadosFicheiro(char* path)
{
		FILE *pfile;
		fopen_s(&pfile, path, "r");
		if (pfile == NULL)
			return false;
		else
		{
			fscanf_s(pfile, "%d", &nclasses);
			fscanf_s(pfile, "%d", &nvalores);
			valores = new int[nvalores];

			for (int i = 0; i < nvalores; i++) {
				fscanf_s(pfile, "%d", &valores[i]);
			}
			fclose(pfile);
			return true;
		}
}

bool Dados::DescarregarDadosFichriro(char* path)
{
	FILE *fp;
	

	if (!fopen_s(&fp, path, "a+")) {
		
		const  time_t  timer = time(NULL);
		tm* tm_ptr = gmtime(&timer);
		fprintf(fp, "************************** %02d/%02d/%4d  ", tm_ptr->tm_mday, tm_ptr->tm_mon + 1, 1900 + (tm_ptr->tm_year));
		fprintf(fp, "%02d:%02d:%02d **************************\n", tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);

		int* freq_abs = FreqAbsoluta();
		int* freq_rel = FreqRelativa();
		fprintf(fp, "N Valores: %d\nN Classes: %d\n", nvalores, nclasses);
		fprintf(fp, "Valores: (ordenados) = {");
		for (int i = 0; i < nvalores; i++)
		{
			if (i != nvalores - 1) fprintf(fp, "%d, ", valores[i]);
			else fprintf(fp, "%d}\n", valores[i]);
		}
		fprintf(fp, "Media: %0.2f \n Mediana: %.2f\n", ObterMedia(), ObterMediana());
		fprintf(fp, "Desvio padrao: %.3f\n", CalcularDesvioPadrao());
		fprintf(fp, "Freq. Relativa: (%d classes) = {", Classes());
		for (int i = 0; i < Classes(); i++)
		{
			if (i != Classes() - 1) fprintf(fp, "%d, ", freq_rel[i]);
			else fprintf(fp, "%d}\n", freq_rel[i]);
		}
		fprintf(fp, "Freq. Absoluta: (%d classes) = {", Classes());
		for (int i = 0; i < Classes(); i++)
		{
			if (i != Classes() - 1) fprintf(fp, "%d, ", freq_abs[i]);
			else fprintf(fp, "%d}\n", freq_abs[i]);
		}

		fprintf(fp, "**************************************************************************\n\n");

		fclose(fp);
		return true;
	}
	fclose(fp);
	return false;
}

void Dados::ImprimirDados()
{
	int* freq_abs = FreqAbsoluta();
	int* freq_rel = FreqRelativa();
	printf("----- Dados -----\n");
	printf("Valores: (ordenados) = {");
	for (int i = 0; i < nvalores; i++)
	{
		if (i != nvalores - 1) printf("%d, ", valores[i]);
		else printf("%d}\n", valores[i]);
	}
	printf("Media: %0.2f | Mediana: %.2f\n", ObterMedia(), ObterMediana());
	printf("Desvio padrao: %.3f\n", CalcularDesvioPadrao());
	printf("Freq. Relativa: (%d classes) = {", Classes());
	for(int i = 0; i < Classes(); i++)
	{
		if (i != Classes() - 1) printf("%d, ", freq_rel[i]);
		else printf("%d}\n", freq_rel[i]);
	}
	printf("Freq. Absoluta: (%d classes) = {", Classes());
	for (int i = 0; i < Classes(); i++)
	{
		if (i != Classes() - 1) printf("%d, ", freq_abs[i]);
		else printf("%d}\n", freq_abs[i]);
	}
}
