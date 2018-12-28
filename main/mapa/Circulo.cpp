#include "Circulo.h"
#include <stdio.h>
#include <cmath>

Circulo::Circulo()
{
	centro = Ponto(0, 0);
	raio = 0;
	valor = 0;
}

Circulo::Circulo(Ponto c, int r, int v)
{
	centro = c;
	raio = r;
	valor = v;
}

void Circulo::Desenhar(HWND janelaId, long cor)
{
	if (janelaId != NULL)
	{
		HDC DrawHDC = GetDC(janelaId);
		// penstyle, width, color
		HPEN hNPen = CreatePen(PS_SOLID, 2, cor);
		HPEN hOPen = (HPEN)SelectObject(DrawHDC, hNPen);
		HBRUSH hOldBrush;
		HBRUSH hNewBrush;
		hNewBrush = CreateSolidBrush(cor);
		hOldBrush = (HBRUSH)SelectObject(DrawHDC, hNewBrush);
		Ellipse(DrawHDC, centro.ObterX() - raio, centro.ObterY() + raio,
			centro.ObterX() + raio, centro.ObterY() - raio);
		char str[80];
		sprintf_s(str, "%d", valor);
		SetBkMode(DrawHDC, TRANSPARENT);
		SetTextColor(DrawHDC, RGB(0, 0, 0));
		SetTextAlign(DrawHDC, TA_CENTER | TA_BOTTOM | TA_BASELINE);
		TextOut(DrawHDC, centro.ObterX(), centro.ObterY(), str, strlen(str));
		DeleteObject(SelectObject(DrawHDC, hOPen));
		DeleteObject(SelectObject(DrawHDC, hOldBrush));
		ReleaseDC(janelaId, DrawHDC);
	}
}

bool Circulo::Contem(Ponto p)
{
	return pow(p.ObterX() - centro.ObterX(), 2) + pow(p.ObterY() - centro.ObterY(), 2) < pow(raio, 2);
}


