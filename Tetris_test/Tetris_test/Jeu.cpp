#include "Jeu.h"
#include <iostream>

using namespace std;

bool Jeu::toucher(WPARAM vk)
{
	if (vk != VK_PAUSE && vk != VK_RETURN && this->etrePause)
		return false;
	switch (vk)
	{
	case VK_UP:
		niv2->tourner();
		break;
	case VK_DOWN:
		niv2->deplacer(0, -1);
		break;
	case VK_LEFT:
		niv2->deplacer(-1, 0);
		break;
	case VK_RIGHT:
		niv2->deplacer(1, 0);
		break;
	case VK_SPACE:
		niv2->tourner();
		break;
	case VK_PAUSE:
		pause(!etrePause);
		break;
	case 0x57:
		niv->tourner();
		break;
	case 0x41:
		niv->deplacer(-1, 0);
		break;
	case 0x53:
		niv->deplacer(0, -1);
		break;
	case 0x44:
		niv->deplacer(1, 0);
		break;
	case VK_RETURN:
		if (niv->GameOver() == true || niv2->GameOver() == true)
			reCommencer();
	default:
		return false;
	}
	return true;
}

void Jeu::MAJTemps()
{
	if (this->etrePause == true)
		return;
	if (niv->GameOver() == true || niv2->GameOver() == true) {
		this->etrePause = true;
		GameOver();
		return;
	}
	niv->MAJTemps_p1();
	niv2->MAJTemps_p2();
	niv->dessinerTableau_p1();
	niv2->dessinerTableau_p2();
}

void Jeu::rePeindre() const
{
	dess.dessinerInterface();
	niv->dessinerPoint_p1();
	niv->dessinerVit_p1();
	niv->dessinerPiece_p1();
	niv->dessinerTableau_p1();
	niv2->dessinerTableau_p2();
	niv2->dessinerPoint_p2();
	niv2->dessinerVit_p2();
	niv2->dessinerPiece_p2();
	
	if (niv->GameOver() == true)
		GameOver();
	else if (etrePause == true)
		Pause();
}

bool Jeu::Perdre() const
{
	return niv->GameOver();
}

void Jeu::pause(bool paused)
{
		if (Perdre() == true)
			return;
		this->etrePause = paused;
		if (paused == true)
			Pause();
}

void Jeu::reCommencer()
{
	delete niv;
	delete niv2;
	niv = new Niveau(dess, 10, 20);
	niv2 = new Niveau(dess, 10, 20);
	etrePause = false;
	rePeindre();
}
