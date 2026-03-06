#include "chess_game.h"
#include "menu.h"
#include "graphics.h"
#include "easyx.h"
#include "global_def.h"
#include <windows.h>

int showDifficultyMenu() {
	initgraph(mutiple(650), mutiple(500));
	setbkcolor(WHITE);
	cleardevice();

	settextcolor(BLACK);
	settextstyle(mutiple(35), 0, L"微软雅黑");
	outtextxy(mutiple(200), mutiple(50), L"人机难度选择");

	MenuItem menuItems[] = {
		{ mutiple(100), mutiple(120), mutiple(500), mutiple(180), L"漫不经心：人机有时会出错!" },
		{ mutiple(100), mutiple(210), mutiple(500), mutiple(270), L"认真模式：人机严防死守，从不出错!!" },
		{ mutiple(100), mutiple(300), mutiple(500), mutiple(360), L"机魂觉醒：AI能预测到多步之后的局面!!!" },
		{ mutiple(100), mutiple(390), mutiple(500), mutiple(450), L"返回主菜单"}
	};

	int itemCount = 4;
	MOUSEMSG msg;

	const int buttonColors[] = {GREEN, BLUE, RED, BLACK};

	setlinecolor(BLACK);
	settextstyle(mutiple(25), 0, L"微软雅黑");

	for (int i = 0; i < itemCount; i++) {
		setfillcolor(RGB(100, 150, 255));
		solidrectangle(menuItems[i].x1, menuItems[i].y1, menuItems[i].x2, menuItems[i].y2);
		rectangle(menuItems[i].x1, menuItems[i].y1, menuItems[i].x2, menuItems[i].y2);

		settextcolor(buttonColors[i]);
		int textWidth = wcslen(menuItems[i].text) * mutiple(16);
		int textX = menuItems[i].x1 + (menuItems[i].x2 - menuItems[i].x1 - textWidth) / 2;
		int textY = menuItems[i].y1 + (menuItems[i].y2 - menuItems[i].y1 - mutiple(25)) / 2;
		outtextxy(textX, textY, menuItems[i].text);
	}

	while (true) {
		msg = GetMouseMsg();

		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x >= menuItems[0].x1 && msg.x <= menuItems[0].x2 &&
				msg.y >= menuItems[0].y1 && msg.y <= menuItems[0].y2) {
				closegraph();
				return 1;
			}
			else if (msg.x >= menuItems[1].x1 && msg.x <= menuItems[1].x2 &&
				msg.y >= menuItems[1].y1 && msg.y <= menuItems[1].y2) {
				closegraph();
				return 2;
			}
			else if (msg.x >= menuItems[2].x1 && msg.x <= menuItems[2].x2 &&
				msg.y >= menuItems[2].y1 && msg.y <= menuItems[2].y2) {
				closegraph();
				return 3;
			}
			else if (msg.x >= menuItems[3].x1 && msg.x <= menuItems[3].x2 &&
				msg.y >= menuItems[3].y1 && msg.y <= menuItems[3].y2) {
				closegraph();
				return -1;
			}
		}
	}
}

int showSettingsMenu() {
	initgraph(mutiple(650), mutiple(500));
	setbkcolor(WHITE);
	cleardevice();

	settextcolor(BLACK);
	settextstyle(mutiple(35), 0, L"微软雅黑");
	outtextxy(mutiple(200), mutiple(50), L"界面大小");

	MenuItem menuItems[] = {
		{ mutiple(150), mutiple(120), mutiple(450), mutiple(180), L"1.0 倍" },
		{ mutiple(150), mutiple(210), mutiple(450), mutiple(270), L"1.5 倍" },
		{ mutiple(150), mutiple(300), mutiple(450), mutiple(360), L"1.8 倍" },
		{ mutiple(150), mutiple(390), mutiple(450), mutiple(450), L"2.0 倍"}
	};

	int itemCount = 4;
	MOUSEMSG msg;

	setlinecolor(BLACK);
	setfillcolor(RGB(100, 150, 255));
	settextcolor(BLACK);
	settextstyle(mutiple(28), 0, L"微软雅黑");

	for (int i = 0; i < itemCount; i++) {
		solidrectangle(menuItems[i].x1, menuItems[i].y1, menuItems[i].x2, menuItems[i].y2);
		rectangle(menuItems[i].x1, menuItems[i].y1, menuItems[i].x2, menuItems[i].y2);

		int rectWidth = menuItems[i].x2 - menuItems[i].x1;
		int rectHeight = menuItems[i].y2 - menuItems[i].y1;
		int textW = textwidth(menuItems[i].text);
		int textH = textheight(menuItems[i].text);

		int textX = menuItems[i].x1 + (rectWidth - textW) / 2;
		int textY = menuItems[i].y1 + (rectHeight - textH) / 2;
		outtextxy(textX, textY, menuItems[i].text);
	}

	while (true) {
		msg = GetMouseMsg();

		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x >= menuItems[0].x1 && msg.x <= menuItems[0].x2 &&
				msg.y >= menuItems[0].y1 && msg.y <= menuItems[0].y2) {
				closegraph();
				setMutiple(1);
				return showMainMenu();
			}
			else if (msg.x >= menuItems[1].x1 && msg.x <= menuItems[1].x2 &&
				msg.y >= menuItems[1].y1 && msg.y <= menuItems[1].y2) {
				closegraph();
				setMutiple(1.5);
				return showMainMenu();
			}
			else if (msg.x >= menuItems[2].x1 && msg.x <= menuItems[2].x2 &&
				msg.y >= menuItems[2].y1 && msg.y <= menuItems[2].y2) {
				closegraph();
				setMutiple(1.8);
				return showMainMenu();
			}
			else if (msg.x >= menuItems[3].x1 && msg.x <= menuItems[3].x2 &&
				msg.y >= menuItems[3].y1 && msg.y <= menuItems[3].y2) {
				closegraph();
				setMutiple(2);
				return showMainMenu();
			}
		}
	}
}

int showMainMenu() {
	initgraph(mutiple(650), mutiple(500));
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);

	settextcolor(BLACK);
	settextstyle(mutiple(40), 0, L"微软雅黑");
	outtextxy(mutiple(250), mutiple(50), L"五子棋");

	MenuItem menuItems[] = {
		{ mutiple(150), mutiple(120), mutiple(450), mutiple(170), L"真人对战" },
		{ mutiple(150), mutiple(200), mutiple(450), mutiple(250), L"人机对战" },
		{ mutiple(150), mutiple(280), mutiple(450), mutiple(330), L"界面大小" },
		{ mutiple(150), mutiple(360), mutiple(450), mutiple(410), L"退出" }
	};

	int itemCount = 4;
	MOUSEMSG msg;

	setfillcolor(RGB(100, 150, 255));
	setlinecolor(BLACK);
	settextcolor(BLACK);
	settextstyle(mutiple(30), 0, L"微软雅黑");

	for (int i = 0; i < itemCount; i++) {
		solidrectangle(menuItems[i].x1, menuItems[i].y1, menuItems[i].x2, menuItems[i].y2);
		rectangle(menuItems[i].x1, menuItems[i].y1, menuItems[i].x2, menuItems[i].y2);

		int rectWidth = menuItems[i].x2 - menuItems[i].x1;
		int rectHeight = menuItems[i].y2 - menuItems[i].y1;
		int textW = textwidth(menuItems[i].text);
		int textH = textheight(menuItems[i].text);

		int textX = menuItems[i].x1 + (rectWidth - textW) / 2;
		int textY = menuItems[i].y1 + (rectHeight - textH) / 2;
		outtextxy(textX, textY, menuItems[i].text);
	}

	while (true) {
		msg = GetMouseMsg();

		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x >= menuItems[0].x1 && msg.x <= menuItems[0].x2 &&
				msg.y >= menuItems[0].y1 && msg.y <= menuItems[0].y2) {
				closegraph();
				isAI = FALSE;
				initGame();
				resetGame();
				playGame();
				closegraph();
				return 1;
			}
			else if (msg.x >= menuItems[1].x1 && msg.x <= menuItems[1].x2 &&
				msg.y >= menuItems[1].y1 && msg.y <= menuItems[1].y2) {
				closegraph();
				int difficulty = showDifficultyMenu();
				if (difficulty != -1) {
					isAI = TRUE;
					aiDif = difficulty;
					initGame();
					resetGame();
					playGame();
					closegraph();
					return 1;
				}
				else {
					// 返回主菜单，需要重新显示
					return showMainMenu();
				}
			}
			else if (msg.x >= menuItems[2].x1 && msg.x <= menuItems[2].x2 &&
				msg.y >= menuItems[2].y1 && msg.y <= menuItems[2].y2) {
				closegraph();
				return showSettingsMenu();
			}
			else if (msg.x >= menuItems[3].x1 && msg.x <= menuItems[3].x2 &&
				msg.y >= menuItems[3].y1 && msg.y <= menuItems[3].y2) {
				closegraph();
				return 0;
			}
		}
	}
}
