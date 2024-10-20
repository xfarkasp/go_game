#pragma once
#include <vector>
#include <set>
#include "matrix.h"

enum class PlayerNumber : char
{
	PLAYER1 = 'o',
	PLAYER2 = 'x'
};

enum class Directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Game
{
public:
	Game(size_t rows, size_t cols);
	Game(Matrix&& board);
	void run();
	void turn();
	void freedomChecker();
	std::set<std::pair<int, int>> checkArea(std::set<std::pair<int, int>> area, bool createArea = true);
	void print() { std::cout << m_board; }

private:
	std::vector<unsigned int> m_playerScores;
	Matrix m_board;
	Matrix m_pastBoard;
	unsigned int m_round = 0;
	std::vector<std::vector<std::pair<int, int>>> m_areas;
	std::vector<Matrix> m_pastConfigs;

};