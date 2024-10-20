#pragma once

class Player
{
	enum class PlayerNumber
	{
		PLAYER1,
		PLAYER2
	};
public:
	Player(PlayerNumber num);
private:
	char m_playerIcon;
	size_t m_score = 0;
};