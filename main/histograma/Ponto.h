#pragma once
class Ponto
{
private:
	int x, y;
public:
	Ponto();
	Ponto(int x1, int y1);

	void AtribuirXY(int x1, int y1);
	float ObterDistancia(Ponto p2);

	int ObterX();
	int ObterY();

	~Ponto();
};

