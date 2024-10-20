#include "game.h"
#include <sstream>
#include <stdexcept>

Game::Game(size_t rows, size_t cols)
	:m_board(Matrix{rows, cols})
{
	m_playerScores = { 0, 0 };
	run();
};

Game::Game(Matrix&& board)
	:m_board(std::move(board))
{
	m_playerScores = { 0, 0 };
	/*m_board[2][2] = 'o';
	m_board[2][3] = 'o';
	m_board[3][2] = 'o';
	m_board[3][3] = 'o';

	m_board[1][2] = 'x';
	m_board[1][3] = 'x';
	m_board[2][1] = 'x';
	m_board[3][1] = 'x';
	m_board[2][4] = 'x';
	m_board[3][4] = 'x';
	m_board[4][2] = 'x';*/
	
	print();

	run();
};

void Game::run()
{
	turn();
	

}

void Game::freedomChecker()
{
	std::vector<char*> delPoints;
	for (size_t i = 0; i < m_board.m_rows.size(); i++)
	{
		for (size_t j = 0; j < m_board.m_rows[0].size(); j++)
		{
			auto& currentChar = m_board[i][j];
			if (currentChar == '.')
			{
				continue;
			}
			unsigned short freedoms = 4;
			const auto& opponentChar = currentChar == 'o' ? 'x' : 'o';

			//check freedoms
			if (   i == 0
				|| m_board[i - 1][j] != '.')
			{
				if (i == 0)
				{
					freedoms--;
				}
				else
				{
					int delta = i - 1;
					while (delta != 0 && m_board[delta][j] == currentChar)
					{
						delta--;
					}
					
					if (delta == 0 || m_board[delta][j] == opponentChar)
					{
						freedoms--;
					}
				}
			}
			
			if (i == m_board.m_rows.size() - 1
				|| m_board[i + 1][j] != '.')
			{
				if (i == m_board.m_rows.size() - 1)
				{
					freedoms--;
				}
				else
				{
					int delta = i + 1;
					while (delta != m_board.m_rows.size() - 1 && m_board[delta][j] == currentChar)
					{
						delta++;
					}

					if (delta == m_board.m_rows.size() - 1 || m_board[delta][j] == opponentChar)
					{
						freedoms--;
					}
				}
			}
			
			if (j == 0
				|| m_board[i][j - 1] != '.')
			{
				if (j == 0)
				{
					freedoms--;
				}
				else
				{
					size_t delta = j - 1;
					while (delta != 0 && m_board[i][delta] == currentChar)
					{
						delta--;
					}

					if (delta == 0 || m_board[i][delta] == opponentChar)
					{
						freedoms--;
					}
				}
			}
			
			if (j == m_board.m_rows[0].size() - 1
				|| m_board[i][j + 1] != '.')
			{
				if (j == m_board.m_rows[0].size() - 1)
				{
					freedoms--;
				}
				else
				{
					int delta = j + 1;
					while (delta != m_board.m_rows[0].size() - 1 && m_board[i][delta] == currentChar)
					{
						delta++;
					}

					if (delta == m_board.m_rows.size() - 1 || m_board[i][delta] == opponentChar)
					{
						freedoms--;
					}
				}
			}

			if (freedoms == 0)
			{
				//currentChar = '.';
				delPoints.push_back(&currentChar);
			}
		}
	}

	for (auto element : delPoints)
	{
		*element = '.';
	}
}

void Game::turn()
{
	std::string input;
	size_t passCounter = 0;
	while (passCounter != 2)
	{
		try
		{
			std::getline(std::cin, input);
			std::stringstream ss{ input };
			std::string temp;
			ss >> temp;
			if (temp == "pass")
			{
				passCounter++;
				m_round++;
				continue;
			}
			passCounter = 0;
			std::pair<unsigned int, unsigned int> positions;
			positions.first = std::stoi(temp);
			ss >> temp;
			positions.second = std::stoi(temp);
			if (m_board[positions.first][positions.second] == '.')
			{
				m_board[positions.first][positions.second] = m_round % 2 == 0 ? 'o' : 'x';
				freedomChecker();
				print();

				m_round++;
			}
		}
		catch (...)
		{
			throw std::runtime_error("Invalid input");
		}
	}
}


