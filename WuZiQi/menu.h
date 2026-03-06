#include "global_def.h"

struct MenuItem {
	int x1, y1, x2, y2;
	const wchar_t* text;
};

int showMainMenu();
int showDifficultyMenu();
int showSettingsMenu();