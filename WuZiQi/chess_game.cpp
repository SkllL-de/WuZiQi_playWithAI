#include "global_def.h"
#include "chess_game.h"
#include "easyx.h"
#include <math.h>


int flag = 0;
double muti = 1;
int ChessMap[20][20] = { 0 };
bool isAI = FALSE;
int aiDif = 1;
void setMutiple(double t) {
	muti = t;
}

int mutiple(int x) {
	return (int)(muti * x);
}

void setbk() {
	cleardevice();
	setbkcolor(RGB(200, 200, 200));
	loadimage(NULL, L"bk2.png");
	setlinecolor(BLACK);
	for (int i = 0; i <= 20; i++) {
		line(0, i * mutiple(25), mutiple(500), i * mutiple(25));
		line(i * mutiple(25), 0, i * mutiple(25), mutiple(500));
	}
	settextcolor(BLACK);
	settextstyle(mutiple(20), 0, L"微软雅黑");
	outtextxy(mutiple(520), mutiple(30), L"玩家1：黑棋");
	outtextxy(mutiple(520), mutiple(60), L"玩家2：白棋");

	settextcolor(BLACK);
	outtextxy(mutiple(520), mutiple(100), L"当前行棋:");

	int btnX1 = mutiple(520), btnY1 = mutiple(180);
	int btnX2 = mutiple(600), btnY2 = mutiple(220);
	setfillcolor(RGB(200, 200, 200));
	solidrectangle(btnX1, btnY1, btnX2, btnY2);
	setlinecolor(BLACK);
	rectangle(btnX1, btnY1, btnX2, btnY2);
	settextstyle(mutiple(16), 0, L"微软雅黑");
	int btnTextW = textwidth(L"返回菜单");
	int btnTextH = textheight(L"返回菜单");
	int btnTextX = btnX1 + (btnX2 - btnX1 - btnTextW) / 2;
	int btnTextY = btnY1 + (btnY2 - btnY1 - btnTextH) / 2;
	outtextxy(btnTextX, btnTextY, L"返回菜单");
}

void initGame() {
	initgraph(mutiple(650), mutiple(500));
	IMAGE img;
	setbk();
}

bool judge(int MapX, int MapY) {
	int temp = 2 - (flag % 2);
	for (int i = MapX - 4, j = MapY; i <= MapX; i++) {
		if (i >= 1 && i < 16
			&& temp == ChessMap[i][j]
			&& temp == ChessMap[i + 1][j]
			&& temp == ChessMap[i + 2][j]
			&& temp == ChessMap[i + 3][j]
			&& temp == ChessMap[i + 4][j])
		{
			return true;
		}
	}
	for (int i = MapX, j = MapY - 4; j <= MapY; j++) {
		if (j >= 1 && j < 16
			&& temp == ChessMap[i][j]
			&& temp == ChessMap[i][j + 1]
			&& temp == ChessMap[i][j + 2]
			&& temp == ChessMap[i][j + 3]
			&& temp == ChessMap[i][j + 4])
		{
			return true;
		}
	}
	for (int i = MapX - 4, j = MapY - 4; i <= MapX && j <= MapY; i++, j++) {
		if (i >= 1 && i < 16
			&& j >= 1 && j < 16
			&& temp == ChessMap[i][j]
			&& temp == ChessMap[i + 1][j + 1]
			&& temp == ChessMap[i + 2][j + 2]
			&& temp == ChessMap[i + 3][j + 3]
			&& temp == ChessMap[i + 4][j + 4])
		{
			return true;
		}
	}
	for (int i = MapX + 4, j = MapY - 4; i >= MapX && j <= MapY; i--, j++) {
		if (i >= 5 && i < 20
			&& j >= 1 && j < 16
			&& temp == ChessMap[i][j]
			&& temp == ChessMap[i - 1][j + 1]
			&& temp == ChessMap[i - 2][j + 2]
			&& temp == ChessMap[i - 3][j + 3]
			&& temp == ChessMap[i - 4][j + 4])
		{
			return true;
		}
	}
	return false;
}

void resetGame() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			ChessMap[i][j] = 0;
		}
	}
	flag = 0;
	setbk();
}

int showGameOverWindow(const wchar_t* winnerText) {
	setfillcolor(RGB(200, 200, 200));
	solidrectangle(mutiple(100), mutiple(150), mutiple(400), mutiple(350));//窗口背景：内部设为灰色矩形
	setlinecolor(BLACK);
	rectangle(mutiple(100), mutiple(150), mutiple(400), mutiple(350));//窗口边框：边框线设为黑色矩形
	settextcolor(BLACK);
	settextstyle(mutiple(20), 0, L"微软雅黑");
	outtextxy(mutiple(200), mutiple(180), winnerText);

	setfillcolor(RGB(100, 200, 100));
	solidrectangle(mutiple(130), mutiple(230), mutiple(230), mutiple(280));
	setfillcolor(BLACK);
	rectangle(mutiple(130), mutiple(230), mutiple(230), mutiple(280));
	settextcolor(BLACK);
	outtextxy(mutiple(155), mutiple(245), L"再来一局");

	setfillcolor(RGB(200, 100, 100));
	solidrectangle(mutiple(265), mutiple(230), mutiple(365), mutiple(280));
	setlinecolor(BLACK);
	rectangle(mutiple(265), mutiple(230), mutiple(365), mutiple(280));
	settextcolor(BLACK);
	outtextxy(mutiple(285), mutiple(245), L"返回菜单");
	MOUSEMSG msg;
	while (true) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x >= mutiple(130) && msg.x <= mutiple(230)
				&& msg.y >= mutiple(230) && msg.y <= mutiple(280)) {
				return 1;
			}
			else if (msg.x >= mutiple(265) && msg.x <= mutiple(365)) {
				return 0;
			}
		}
	}
}