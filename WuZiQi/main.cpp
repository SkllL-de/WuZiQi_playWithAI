#include "chess_game.h"
#include "ai_chess.h"
#include "menu.h"
#include "global_def.h"
#include "easyx.h"
#pragma comment(lib, "winmm.lib")//多媒体音频接口

void playGame() {
	int ChessX = 0, ChessY = 0;
	int MapX = 0, MapY = 0;
	MOUSEMSG Msg;
	HWND hwnd = GetHWnd();

	int btnX1 = mutiple(520), btnY1 = mutiple(180);
	int btnX2 = mutiple(600), btnY2 = mutiple(220);

	settextstyle(mutiple(20), 0, L"微软雅黑");
	while (true) {
		//展示行棋方
		if ((flag & 1) == 0) {
			 //当前行棋：黑方
			setfillcolor(BLACK);
			solidcircle(mutiple(608), mutiple(108), mutiple(10));
		}
		else {
			//当前行棋：白方
			setfillcolor(WHITE);
			solidcircle(mutiple(608), mutiple(108), mutiple(10));
			if (isAI) {
				aiMove(aiDif, MapX, MapY);
				ChessX = MapX * mutiple(25);
				ChessY = MapY * mutiple(25);
				mciSendString(L"play luoZi.mp3", NULL, 0, NULL);
				setfillcolor(WHITE);
				solidcircle(ChessX, ChessY, mutiple(10));
				ChessMap[MapX][MapY] = 2;
				flag++;

				if (judge(MapX, MapY)) {
					Sleep(1500);
					int choice = showGameOverWindow(L"白棋胜利");
					if (choice == 1) resetGame();
					else return;
				}
				continue;
			}
		}

		Msg = GetMouseMsg();
		for (int y = 1; y < 20; y++) {
			for (int x = 1; x < 20; x++) {
				if (abs(Msg.x - x * mutiple(25)) < mutiple(12) &&
					abs(Msg.y - y * mutiple(25)) < mutiple(12)) {
					ChessX = x * mutiple(25);
					ChessY = y * mutiple(25);
					MapX = x;
					MapY = y;
				}
			}
		}
		if (Msg.uMsg == WM_LBUTTONDOWN) {
			// 检查是否点击了返回菜单按钮
			if (Msg.x >= btnX1 && Msg.x <= btnX2 && Msg.y >= btnY1 && Msg.y <= btnY2) {
				return;
			}
			if (ChessMap[MapX][MapY] != 0) {
				MessageBox(hwnd, L"这里有棋子了！", L"请重新放置棋子", MB_OK);
				continue;
			}
			if ((flag & 1) == 0) {
				mciSendString(L"play luoZi.mp3", NULL, 0, NULL);
				setfillcolor(BLACK);
				solidcircle(ChessX, ChessY, mutiple(10));
				ChessMap[MapX][MapY] = 1;//黑子记为1
			}
			else {
				mciSendString(L"play luoZi.mp3", NULL, 0, NULL);
				setfillcolor(WHITE);
				solidcircle(ChessX, ChessY, mutiple(10));
				ChessMap[MapX][MapY] = 2;//白子记为2
			}
			flag++;
		}
		if (judge(MapX, MapY)) {
			/*if (1 == (flag & 1)) {
				MessageBox(hwnd, "玩家1：黑棋胜利", "Game Over", MB_OK);
				return;
			}
			else {
				MessageBox(hwnd, "玩家2：白棋胜利", "Game Over", MB_OK);
				return;
			}*/
			const wchar_t* winner = (1 == (flag & 1) ? L"玩家1:黑棋胜利" : L"玩家2:白棋胜利");
			int choice = showGameOverWindow(winner);
			if (choice == 1) {
				resetGame();
			}
			else {
				return;
			}
		}
	}
}

//int main()
//#define WINAPI __stdcall
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	mciSendString(L"play music.mp3 repeat", NULL, 0, NULL);
	setMutiple(2);
	useAI(); setAiDif(1);
	/*initGame();
	playGame();
	closegraph();*/
	while (showMainMenu() == 1);
	return 0;
}