#pragma once
class Dados
{
private:
	int* valores;
	int nclasses, nvalores, min, max, media;
public:
	Dados();
	~Dados();

	int Classes() {	return nclasses;}; //Devolve o numero de classes
	int* Valores() { return valores; }; //Devolve o numero de valores
	int* FreqAbsoluta(); //Devolve um vetor correspondente à frequencia absolula
	int* FreqRelativa(); //Devolce um vetor correspondente à frequencia relativa
	int* Ordenar(); //Devolve o vetor dos valores ordenado sem alterar o original
	float ObterMedia(); //Devolve a média dos valores
	float CalcularDesvioPadrao(); //Devolve o desvio padrao
	float ObterMediana(); //Devolve a mediana
	bool CarregarDadosFicheiro(char* path); //Carrega os valores apartir de um ficheiro
	bool DescarregarDadosFichriro(char* path);
	void ImprimirDados();
};

