#ifndef BUFF_HOLDER_H
#define BUFF_HOLDER_H

#include "Library.h"

enum class ApplicationType
{
	None, Once, Spawn
};

enum class AlertClassName
{
	Player, Enemy
};

enum class BuffName
{
	PlayerSpeed, PlayerSpeedPercentage, PlayerHealth, PlayerHealthPercentage
};

struct Buff
{
	BuffName name;
	ApplicationType applier;
	AlertClassName applyLocation;
	float increase;
	bool active;
};

class BuffHolder
{
public:
	static BuffHolder& getInstance()
	{
		static BuffHolder instance;
		return instance;
	}

	// DELETE FUNCTIONS TO AVOID MORE INSTANCES
	BuffHolder(BuffHolder const&) = delete;
	void operator=(BuffHolder const&) = delete;

	void initNew(Buff& t_newBuff);
	void initNew(std::shared_ptr<Buff> t_newBuff);

	Buff& getBuff(BuffName t_typeToGet);

	std::vector<std::shared_ptr<Buff>> getOneTimeApplicators(); // NOTE: POTENTIAL SPEED DECREASE BECAUSE OF COPYING (MAYBE?)

	bool getAlert();
private:
	BuffHolder() {}

	std::vector<std::shared_ptr<Buff>> m_buffs;
};

#endif // !BUFF_HOLDER_H
