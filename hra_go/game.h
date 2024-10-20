#pragma once
#include <vector>
#include <set>
#include "matrix.h"

class Game
{
public:
enum class PlayerCharakter : char
{
	PLAYER1 = 'O',
	PLAYER2 = 'X',
	FREEDOM = '.'
};

public:
	Game(size_t rows, size_t cols);
	Game(Matrix&& board);
	void run();
	void turn();
	void freedomChecker();
	std::set<std::pair<int, int>> checkArea(std::set<std::pair<int, int>> area, bool createArea = true);
	void print() { std::cout << m_board; }
	const char getCharValue(PlayerCharakter input) const;

private:
	std::vector<unsigned int> m_playerScores;
	Matrix m_board;
	Matrix m_pastBoard;
	unsigned int m_round = 0;
	std::vector<std::vector<std::pair<int, int>>> m_areas;
	std::vector<Matrix> m_pastConfigs;

};