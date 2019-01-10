#pragma once
#include "Jouer.h"
#include "PieceSet.h"

class Jeu
{
protected:
	Niveau *niv, *niv2;
	Dessiner &dess;
	bool etrePause;
public:
	Jeu(Dessiner &de) :dess(de), etrePause(false)
	{
		niv = new Niveau(de, 10, 20);
		niv2 = new Niveau(de, 10, 20);
	}

	void GameOver() const
	{
		dess.dessinerTexte(TEXT("GAME OVER"), 3, 10);
		dess.dessinerTexte(TEXT("Appuyez sur Entrée pour rejouer"), 1, 9);
		dess.dessinerTexte(TEXT("GAME OVER"), 19, 10);
		dess.dessinerTexte(TEXT("Appuyez sur Entrée pour rejouer"), 17, 9);
	}

	void Pause() const
	{
		dess.dessinerTexte(TEXT("PAUSE"), 4, 10);
		dess.dessinerTexte(TEXT("Appuyez sur Pause pour continuer"), 1, 9);
		dess.dessinerTexte(TEXT("PAUSE"), 20, 10);
		dess.dessinerTexte(TEXT("Appuyez sur Pause pour continuer"), 17, 9);
	}

	bool toucher(WPARAM vk);
	void MAJTemps();
	void rePeindre() const;
	bool Perdre() const;
	void pause(bool paused);
	void reCommencer();

	~Jeu()
	{
		delete niv;
		delete niv2;
	}
};
