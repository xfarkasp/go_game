#pragma once
#include <vector>
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
	void print() { std::cout << m_board; }

private:
	std::vector<unsigned int> m_playerScores;
	Matrix m_board;
	unsigned int m_round = 0;
};