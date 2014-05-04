#pragma once
#include "template.h"
using namespace std;

class View
{
public:
	static View* Instance();

	void buildTitleScreen();
	void showTitleScreen();
	void destroyTitleScreen();

	void buildTrackScreen();
	void showTrackScreen();
	void destroyTrackScreen();

	void buildCarColorScreen();
	void showCarColorScreen();
	void destroyCarColorScreen();

	void buildCarTypeScreen();
	void showCarTypeScreen();
	void destroyCarTypeScreen();

	void buildHUDScreen();
	void showHUDScreen();
	void destroyHUDScreen();

	void buildGameoverScreen();
	void showGameoverScreen();

	void buildWinScreen();
	void showWinScreen();

private:
	View();  // Private so that it can  not be called
	View(View const&){};             // copy constructor is private
	View& operator=(View const&){};  // assignment operator is private
	static View* m_pInstance;
};
