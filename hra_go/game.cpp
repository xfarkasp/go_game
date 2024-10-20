#include "game.h"
#include <sstream>
#include <stdexcept>

Game::Game(size_t rows, size_t cols)
	:m_board(Matrix{rows, cols}), m_pastBoard(Matrix{rows, cols})
{
	m_playerScores = { 0, 0 };
	run();
};

Game::Game(Matrix&& board)
	:m_board(std::move(board)),
	m_pastBoard(m_board.m_rows.size(), m_board.m_rows[0].size())
{
	m_playerScores = { 0, 0 };
	print();
	run();
};

const char Game::getCharValue(Game::PlayerCharakter input) const
{
	switch (input)
	{
	case Game::PlayerCharakter::PLAYER1:
		return 'O';
	case Game::PlayerCharakter::PLAYER2:
		return 'X';
	}
}

void Game::run()
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
			if (m_board[positions.first][positions.second] == getCharValue(PlayerCharakter::FREEDOM))
			{
				m_board[positions.first][positions.second] = m_round % 2 == 0 ? getCharValue(PlayerCharakter::PLAYER1) : getCharValue(PlayerCharakter::PLAYER2);
				// check KO rule
				if (m_board == m_pastBoard)
				{
					m_board[positions.first][positions.second] = getCharValue(PlayerCharakter::FREEDOM);
				}
				else
				{
					m_pastBoard = m_board;
					freedomChecker();
					print();
					m_round++;
				}
			}
		}
		catch (...)
		{
			throw std::runtime_error("Invalid input");
		}
	}
}

std::set<std::pair<int, int>> Game::checkArea(std::set<std::pair<int, int>> area, bool createArea)
{
	int freedoms = 0;
	for (const auto& point : area)
	{
		int i = point.first;
		int j = point.second;
		const auto& currentChar = m_board[i][j];
		const auto& currentPlayer = m_round % 2 == 0 ? getCharValue(PlayerCharakter::PLAYER1) : getCharValue(PlayerCharakter::PLAYER2);
		if (!createArea && currentPlayer == currentChar)
		{
			freedoms++;
			continue;
		}
		if (   i != 0
			&& m_board[i - 1][j] != getCharValue(PlayerCharakter::FREEDOM))
		{
			int delta = i - 1;
			while (delta != 0 && m_board[delta][j] == currentChar)
			{
				if (createArea)
				{
					area.insert(std::make_pair(delta, j));
				}
				else
				{
					if (m_board[delta][j] == getCharValue(PlayerCharakter::FREEDOM))
					{
						freedoms++;
					}
				}
				delta--;
			}
		}
		else if(!createArea && i != 0)
		{
			freedoms++;
			break;
		}

		if (   i != m_board.m_rows.size() - 1
			&& m_board[i + 1][j] != getCharValue(PlayerCharakter::FREEDOM))
		{
			int delta = i + 1;
			while (delta != m_board.m_rows.size() - 1 && m_board[delta][j] == currentChar)
			{
				if (createArea)
				{
					area.insert(std::make_pair(delta, j));
				}
				else
				{
					if (m_board[delta][j] == getCharValue(PlayerCharakter::FREEDOM))
					{
						freedoms++;
					}
				}
				
				delta++;
			}
		}
		else if (!createArea && i != m_board.m_rows.size() - 1)
		{
			freedoms++;
			break;
		}

		if (j != 0
			&& m_board[i][j - 1] != getCharValue(PlayerCharakter::FREEDOM))
		{
			int delta = j - 1;
			while (	   delta != 0 
					&& m_board[i][delta] == currentChar)
			{
				if (createArea)
				{
					area.insert(std::make_pair(i, delta));
				}
				else
				{
					if (m_board[i][delta] == getCharValue(PlayerCharakter::FREEDOM))
					{
						freedoms++;
					}
				}
				delta--;
			}
		}
		else if (!createArea && j != 0)
		{
			freedoms++;
			break;
		}

		if (   j != m_board.m_rows[0].size() - 1
			&& m_board[i][j + 1] != getCharValue(PlayerCharakter::FREEDOM))
		{
			int delta = j + 1;
			while (delta != 0 && m_board[i][delta] == currentChar)
			{
				if (createArea)
				{
					area.insert(std::make_pair(i, delta));
				}
				else
				{
					if (m_board[i][delta] == getCharValue(PlayerCharakter::FREEDOM))
					{
						freedoms++;
					}
				}
				delta++;
			}
		}
		else if (!createArea && j != m_board.m_rows[0].size() - 1)
		{
			freedoms++;
			break;
		}
	}
	if (!createArea
		&& freedoms == 0)
	{
		for (auto& point : area)
		{
			m_board[point.first][point.second] = getCharValue(PlayerCharakter::FREEDOM);
		}
		print();
	}
	return area;
}

void Game::freedomChecker()
{
	std::vector<char*> delPoints;
	std::set<std::pair<int, int>> area;
	std::vector<std::set<std::pair<int, int>>> areas;
	for (size_t i = 0; i < m_board.m_rows.size(); i++)
	{
		for (size_t j = 0; j < m_board.m_rows[0].size(); j++)
		{
			auto& currentChar = m_board[i][j];
			if (currentChar == getCharValue(PlayerCharakter::FREEDOM))
			{
				continue;
			}
			bool found = false;
			for (const auto& element : areas)
			{
				if (element.find(std::make_pair(i, j)) != element.end())
				{
					found = true;
					break;
				}
			}
			if (found)
			{
				continue;
			}

			area.insert(std::make_pair(i, j));
			area = checkArea(area);
			if (areas.empty())
			{
				areas.emplace_back(area);
			}
			size_t it = 0;
			for (const auto& element : area)
			{
				for (it; it < areas.size(); it++)
				{
					if (areas[it].find(element) != areas[it].end())
					{
						found = true;
						areas[it] = area;
						break;
					}
				}
			}
			if (!found)
			{
				areas.emplace_back(area);
			}
			area.clear();
		}
	}

	for (auto area : areas)
	{
		checkArea(area, false);
	}
}