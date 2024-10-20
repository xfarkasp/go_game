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
	print();
	run();
};

void Game::run()
{
	turn();
}

std::set<std::pair<int, int>> Game::checkArea(std::set<std::pair<int, int>> area, bool createArea)
{
	int freedoms = 0;
	for (const auto& point : area)
	{
		int i = point.first;
		int j = point.second;
		const auto& currentChar = m_board[i][j];

		if (i != 0
			&& m_board[i - 1][j] != '.')
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
					if (m_board[delta][j] == '.')
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
			&& m_board[i + 1][j] != '.')
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
					if (m_board[delta][j] == '.')
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
			&& m_board[i][j - 1] != '.')
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
					if (m_board[i][delta] == '.')
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
			&& m_board[i][j + 1] != '.')
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
					if (m_board[i][delta] == '.')
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
			m_board[point.first][point.second] = '.';
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
			if (currentChar == '.')
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
				if (std::find(m_pastConfigs.begin(), m_pastConfigs.end(), m_board) == m_pastConfigs.end())
				{
					freedomChecker();
					print();
					m_round++;
					m_pastConfigs.emplace_back(m_board);
				}
				else
				{
					m_board = m_pastConfigs.back();
				}
			}
		}
		catch (...)
		{
			throw std::runtime_error("Invalid input");
		}
	}
}