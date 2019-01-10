#pragma once
#include "Pieces.h"
#include <windows.h>
class Dessiner
{
protected:
	HDC hdc;     
	HWND hWnd;   
	RECT rect;  
	int largeur;
	int hauteur;
public:
	Dessiner(HDC hdc, HWND hwnd, int pxPerBlock = 200, int largeur = 10, int hauteur = 20) : hdc(hdc), hWnd(hwnd), largeur(largeur), hauteur(hauteur)
	{
		GetClientRect(hwnd, &rect);
		SaveDC(hdc);
		SetMapMode(hdc, MM_ISOTROPIC);
		SetViewportExtEx(hdc, pxPerBlock, pxPerBlock, 0);
		SetWindowExtEx(hdc, 1, -1, 0);
		SetViewportOrgEx(hdc, 0, rect.bottom, 0);
		SetTextColor(hdc, RGB(125, 0, 0));
		SetBkColor(hdc, RGB(255,255,255));
	}
	void dessinerBloc(int x, int y, COLORREF couleur);
	void dessinerInterface();
	void dessinerTexte(const TCHAR *Texte, int x, int y) const;
	void dessinerPiece(Piece &piece, int x, int y);
	void dessinerPoint(int pt, int x, int y) const;
	void dessinerVit(int vitesse, int x, int y) const;
	~Dessiner()
	{
		RestoreDC(hdc, -1);
	}
};