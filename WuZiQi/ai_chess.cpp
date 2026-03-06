#include "global_def.h"
#include "ai_chess.h"
#include <windows.h> 
#include <cmath>
void useAI() {
	isAI = true;
}

bool isPosValid(int x, int y) {
	return x >= 1 && x < 20 && y >= 1 && y < 20;
}

bool isNearChess(int x, int y) {
	// 检查位置周围（包括2格距离内）是否有棋子
	for (int dy = -2; dy <= 2; dy++) {
		for (int dx = -2; dx <= 2; dx++) {
			if (dx == 0 && dy == 0) continue;
			int tx = x + dx;
			int ty = y + dy;
			if (isPosValid(tx, ty) && ChessMap[ty][tx] != EMPTY) {
				return true;
			}
		}
	}
	return false;
}
ChessShape countShapeInLine(int x, int y, int dx, int dy, ChessColor color) {
	int same = 0;       // 同色棋子数
	bool empty_left = 0; // 左空位数
	bool empty_right = 0;// 右空位数
	bool block_left = 0; // 左阻挡（对方棋子/边界）
	bool block_right = 0;// 右阻挡

	// 向右统计同色棋子
	int tx = x + dx, ty = y + dy;
	while (isPosValid(tx, ty) && ChessMap[ty][tx] == color) {
		same++;
		tx += dx;
		ty += dy;
	}
	// 统计右侧空位/阻挡
	if (isPosValid(tx, ty) && ChessMap[ty][tx] == EMPTY) {
		empty_right = 1; // 仅需1个空位即可判断活型
	}
	else {
		block_right = 1;
	}

	// 向左统计同色棋子
	tx = x - dx, ty = y - dy;
	while (isPosValid(tx, ty) && ChessMap[ty][tx] == color) {
		same++;
		tx -= dx;
		ty -= dy;
	}
	// 统计左侧空位/阻挡
	if (isPosValid(tx, ty) && ChessMap[ty][tx] == EMPTY) {
		empty_left = 1;
	}
	else {
		block_left = 1;
	}

	// 棋型判定逻辑
	if (same >= 4) return WIN;                  // 成五（已赢）
	if (same == 3) {
		if (empty_left  && empty_right) return LIVE_FOUR;  // 活四（两端空）
		else if (empty_left  || empty_right) return BLOCK_FOUR; // 冲四（一端空）
	}
	if (same == 2) {
		if (empty_left && empty_right) return LIVE_THREE; // 活三
		else if (empty_left || empty_right) return BLOCK_THREE; // 眠三
	}
	if (same == 1) {
		if (empty_left && empty_right) return LIVE_TWO;   // 活二
		else if (empty_left || empty_right) return BLOCK_TWO; // 眠二
	}
	return NONE;
}
int checkShape(int x, int y, ChessColor color) {
	if (!isPosValid(x, y) || ChessMap[y][x] != EMPTY) return 0;

	// 模拟落子
	ChessMap[y][x] = color;
	int score = 0;
	// 遍历4个方向（横、竖、两个斜线）
	int dirs[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };
	for (auto& dir : dirs) {
		int dx = dir[0], dy = dir[1];
		ChessShape shape = countShapeInLine(x, y, dx, dy, color);
		// 根据棋型加分
		switch (shape) {
		case WIN: score += SCORE_WIN; break;
		case LIVE_FOUR: score += SCORE_LIVE_FOUR; break;
		case BLOCK_FOUR: score += SCORE_BLOCK_FOUR; break;
		case LIVE_THREE: score += SCORE_LIVE_THREE; break;
		case BLOCK_THREE: score += SCORE_BLOCK_THREE; break;
		case LIVE_TWO: score += SCORE_LIVE_TWO; break;
		case BLOCK_TWO: score += SCORE_BLOCK_TWO; break;
		default: break;
		}
	}
	// 还原棋盘
	ChessMap[y][x] = EMPTY;
	return score;
}
int calBaseScore(int x, int y) {
	int score = 0;
	int dist = abs(x - 10) + abs(y - 10);
	score += SCORE_CENTER - dist * 5; // 中心点位基础分，距离越近分数越高
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			if (dx == 0 && dy == 0) continue;
			int tx = x + dx;
			int ty = y + dy;
			if (isPosValid(tx, ty) && ChessMap[ty][tx] != EMPTY) {
				score += SCORE_NEAR; // 周围有棋子，增加基础分
			}
		}
	}
	return score;
}
int calPosScore(int x, int y) {
	if (!isPosValid(x, y) || ChessMap[y][x] != EMPTY) return 0;

	int attack_score = checkShape(x, y, WHITE_CHESS);
	int defense_score = checkShape(x, y, BLACK_CHESS);

	if (defense_score >= SCORE_WIN) defense_score = SCORE_WIN;          // 玩家即将成五，必须防
	else if (defense_score >= SCORE_LIVE_FOUR) defense_score = SCORE_WIN - 1000; // 玩家活四，优先级仅次于成五
	else if (defense_score >= SCORE_BLOCK_FOUR) defense_score = SCORE_WIN - 5000; // 玩家冲四，必须优先防
	return attack_score + defense_score + calBaseScore(x, y);

}
void setAiDif(int t) { aiDif = t; }
void dif1(int& MapY, int& MapX){
	int max_score = -100000;
	int best_y = 10, best_x = 10;

	for (int y = 1; y < 20; y++) {
		for (int x = 1; x < 20; x++) {
			if (ChessMap[y][x] == 0) {
				int score = calPosScore(x, y);
				if (score > max_score) {
					max_score = score;
					best_y = y;
					best_x = x;
				}
			}
		}
	}
	MapX = best_x;
	MapY = best_y;
}
void dif2(int& MapY, int& MapX){
	int max_score = -100000;
	int best_y = 10, best_x = 10;
	int defense_priority = 0;  // 防守优先级：0=无，1=眠三，2=活三，3=冲四，4=活四，5=成五

	for (int y = 1; y < 20; y++) {
		for (int x = 1; x < 20; x++) {
			if (ChessMap[y][x] == 0) {
				int defense_score = checkShape(x, y, BLACK_CHESS);
				int current_defense_priority = 0;

				// 评估防守优先级
				if (defense_score >= SCORE_WIN) current_defense_priority = 5;
				else if (defense_score >= SCORE_LIVE_FOUR) current_defense_priority = 4;
				else if (defense_score >= SCORE_BLOCK_FOUR) current_defense_priority = 3;
				else if (defense_score >= SCORE_LIVE_THREE) current_defense_priority = 2;
				else if (defense_score >= SCORE_BLOCK_THREE) current_defense_priority = 1;

				// 如果发现更高优先级的防守，直接选择
				if (current_defense_priority > defense_priority) {
					defense_priority = current_defense_priority;
					best_y = y;
					best_x = x;
					max_score = defense_score;
				}
				// 同优先级则只比较防守分（不混入进攻分）
				else if (current_defense_priority == defense_priority && current_defense_priority > 0) {
					if (defense_score > max_score) {
						max_score = defense_score;
						best_y = y;
						best_x = x;
					}
				}
				// 没有防守需求时，用总分判断
				else if (defense_priority == 0) {
					int score = calPosScore(x, y);
					if (score > max_score) {
						max_score = score;
						best_y = y;
						best_x = x;
					}
				}
			}
		}
	}
	MapX = best_x;
	MapY = best_y;
}
// Minimax + Alpha-Beta 剪枝算法的递归函数
// isMaximize: true 表示最大化节点（AI），false 表示最小化节点（玩家）
int minimax(int depth, int alpha, int beta, bool isMaximize) {
	// 达到搜索深度或游戏结束时的估值
	if (depth == 0) {
		int totalScore = 0;
		// 遍历所有空位，计算全局棋盘的综合评分（模拟叶子节点价值）
		for (int y = 1; y < 20; y++) {
			for (int x = 1; x < 20; x++) {
				if (ChessMap[y][x] == EMPTY && isNearChess(x, y)) {
					totalScore += calBaseScore(x, y); // 加入基础评分
					totalScore += checkShape(x, y, WHITE_CHESS); // AI 进攻分
					totalScore -= checkShape(x, y, BLACK_CHESS); // 玩家防守分
				}
			}
		}
		return totalScore;
	}

	if (isMaximize) {  // AI 的回合（最大化）
		int maxEval = -1000000;
		for (int y = 1; y < 20; y++) {
			bool isPruned = false;
			for (int x = 1; x < 20; x++) {
				if (ChessMap[y][x] == EMPTY && isNearChess(x, y)) {
					// 模拟 AI 落子
					ChessMap[y][x] = WHITE_CHESS;
					int attackScore = checkShape(x, y, WHITE_CHESS);

					// 如果 AI 赢了，直接返回最高分
					if (attackScore >= SCORE_WIN) {
						ChessMap[y][x] = EMPTY;
						//return SCORE_WIN;
						maxEval = SCORE_WIN;
						isPruned = true;
						break;
					}
					int eval = attackScore - checkShape(x, y, BLACK_CHESS) * 2 + minimax(depth - 1, alpha, beta, false);
					ChessMap[y][x] = EMPTY;
					maxEval = (eval > maxEval) ? eval : maxEval;
					alpha = (eval > alpha) ? eval : alpha;

					// Beta 剪枝
					if (beta <= alpha) {isPruned = true; break;}
				}
			}
			if(isPruned) break;   // 剪枝
		}
		return maxEval;
	}
	else {  // 玩家的回合（最小化）
		int minEval = 1000000;
		for (int y = 1; y < 20; y++) {
			bool isPruned = false;
			for (int x = 1; x < 20; x++) {
				if (ChessMap[y][x] == EMPTY && isNearChess(x, y)) {
					// 模拟玩家落子
					ChessMap[y][x] = BLACK_CHESS;
					int attackScore = checkShape(x, y, BLACK_CHESS);

					// 如果玩家赢了，返回最低分（最坏情况）
					if (attackScore >= SCORE_WIN) {
						ChessMap[y][x] = EMPTY;
						minEval = -SCORE_WIN;
						isPruned = true;
						break;
					}

					int eval = -attackScore * 2 + checkShape(x, y, WHITE_CHESS) + minimax(depth - 1, alpha, beta, true);
					ChessMap[y][x] = EMPTY;

					minEval = (eval < minEval) ? eval : minEval;
					beta = (eval < beta) ? eval : beta;

					// Alpha 剪枝
					if (beta <= alpha) { isPruned = true; break; }
				}
			}
			if (isPruned) break;  // 剪枝
		}
		return minEval;
	}
}

void dif3(int& MapY, int& MapX) {
	int max_score = -1000000;
	int best_y = 10, best_x = 10;
	int search_depth = 3;  // 搜索深度

	for (int y = 1; y < 20; y++) {
		for (int x = 1; x < 20; x++) {
			if (ChessMap[y][x] == EMPTY && isNearChess(x, y)) {
				// 模拟 AI 落子
				ChessMap[y][x] = WHITE_CHESS;
				int attackScore = checkShape(x, y, WHITE_CHESS);

				// 如果 AI 能赢，直接返回该位置
				if (attackScore >= SCORE_WIN) {
					ChessMap[y][x] = EMPTY;
					MapX = x;
					MapY = y;
					return;
				}

				// 防守：检查玩家是否即将赢
				int defenseScore = checkShape(x, y, BLACK_CHESS);
				if (defenseScore >= SCORE_WIN) {
					ChessMap[y][x] = EMPTY;
					MapX = x;
					MapY = y;
					return;
				}

				// 使用 Minimax 算法评估该位置
				int eval = attackScore - defenseScore  /*+ calBaseScore(x, y)*/+ minimax(search_depth - 1, -1000000, 1000000, false);
				ChessMap[y][x] = EMPTY;

				if (eval > max_score) {
					max_score = eval;
					best_y = y;
					best_x = x;
				}
			}
		}
	}
	MapX = best_x;
	MapY = best_y;
}
void aiMove(int difficulty, int& MapX, int& MapY) {
	switch (difficulty) {
		case 1: Sleep(800); dif1(MapX, MapY); break;
		case 2: Sleep(800); dif2(MapX, MapY); break;
		case 3: Sleep(400); dif3(MapX, MapY); break;
		default: dif1(MapX, MapY); break;
	}
}