#pragma once
#include "global_def.h"
#include <math.h>

const int SCORE_WIN = 1000000;    // 成五（必胜）
const int SCORE_LIVE_FOUR = 100000; // 活四（必赢，两端空）
const int SCORE_BLOCK_FOUR = 50000;  // 冲四/断四（一端空，需防）
const int SCORE_LIVE_THREE = 10000;  // 活三（两端空，高威胁）
const int SCORE_BLOCK_THREE = 5000;   // 眠三（一端空，需防）
const int SCORE_LIVE_TWO = 1000;     // 活二
const int SCORE_BLOCK_TWO = 500;      // 眠二
const int SCORE_CENTER = 100;        // 中心位置加分
const int SCORE_NEAR = 50;           // 有棋子相邻加分

enum ChessShape {
    NONE,
    LIVE_TWO, BLOCK_TWO,
    LIVE_THREE, BLOCK_THREE,
    LIVE_FOUR, BLOCK_FOUR,
    WIN
};

void useAI();
bool isPosValid(int x, int y);
ChessShape countShapeInLine(int x, int y, int dx, int dy, ChessColor color);
int checkShape(int x, int y, ChessColor	color);
int calBaseScore(int x, int y);
int calPosScore(int x, int y);
void dif1(int& MapX, int& MapY);
void dif2(int& MapX, int& MapY);
void dif3(int& MapX, int& MapY);
void setAiDif(int t);
void aiMove(int difficulty, int& MapX, int& MapY);