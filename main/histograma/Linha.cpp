#include "Linha.h"
#include <cmath>

Linha::Linha() {
	pi = Ponto(0, 0);
	pf = Ponto(0, 0);
}
Linha::Linha(Ponto p1, Ponto p2) {
	pi = p1;
	pf = p2;
}
void Linha::Desenhar(HWND janelaId, long cor)
{
	if (janelaId != NULL)
	{
		HPEN hOPen;
		// penstyle, width, color
		HPEN hNPen = CreatePen(PS_SOLID, 2, cor);
		HDC DrawHDC = GetDC(janelaId);
		hOPen = (HPEN)SelectObject(DrawHDC, hNPen);
		// starting point of line
		MoveToEx(DrawHDC, pi.ObterX(), pi.ObterY(), NULL);
		// ending point of line
		LineTo(DrawHDC, pf.ObterX(), pf.ObterY());
		DeleteObject(SelectObject(DrawHDC, hOPen));
		ReleaseDC(janelaId, DrawHDC);
	}
}

float Linha::ObterComprimento()
{
	return sqrt(pow(pi.ObterX() - pf.ObterX(), 2) + pow(pi.ObterY() - pf.ObterY(), 2));
}
