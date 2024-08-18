#ifndef PLAYER_BUFF_INTERPRETTER_HPP
#define PLAYER_BUFF_INTERPRETTER_HPP

#include "Player.h"
#include "BuffHolder.h"

class PlayerBuffInterpretter
{
public:
	static void InterpretPlayerBuffs(Player& t_player, std::shared_ptr<Buff> t_buff)
	{
		if (t_buff->name == BuffName::PlayerSpeed)
		{
			t_player.m_speed += t_buff->increase;
		}
		else if (t_buff->name == BuffName::PlayerSpeedPercentage)
		{
			t_player.m_speed *=  t_buff->increase;
		}
		else if (t_buff->name == BuffName::PlayerHealth)
		{
			t_player.m_healthMax += t_buff->increase;
		}
		else if (t_buff->name == BuffName::PlayerHealthPercentage)
		{
			t_player.m_healthMax *= t_buff->increase;
		}

		t_buff->active = false; // always nullify the buff after use!
	}
};

#endif // !PLAYER_BUFF_INTERPRETTER_HPP
