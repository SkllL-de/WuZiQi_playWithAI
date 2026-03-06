#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include "global_def.h"
#include "graphics.h"
#include <windows.h>
#include <mmsystem.h>

void setMutiple(double t);
int mutiple(int x);
void setbk();
void initGame();
bool judge(int MapX, int MapY);
void resetGame();
int showGameOverWindow(const wchar_t* winnerText);
void playGame();
#endif //CHESS_GAME_H