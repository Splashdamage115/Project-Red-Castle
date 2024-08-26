#ifndef LEVEL_UP_HANDLER_HPP
#define LEVEL_UP_HANDLER_HPP

#include "Library.h"
#include "Player.h"

class LevelUpHandler
{
public:
	bool checkXp(Player& t_player)
	{
		if (t_player.m_xpLvl > m_nextXp)
		{
			t_player.m_xpLvl = 0;
			m_nextXp += 75;
			return true;
		}
		return false;
	}
private:
	int m_nextXp{ 125 };
};


#endif // !LEVEL_UP_HANDLER_HPP
