#include "BuffHolder.h"

void BuffHolder::initNew(Buff& t_newBuff)
{
	for (auto& i : m_buffs)
	{
		if (!i->active)
		{
			i = std::make_shared<Buff>(t_newBuff);
			return;
		}
	}

	m_buffs.push_back(std::make_shared<Buff>(t_newBuff));
}

void BuffHolder::initNew(std::shared_ptr<Buff> t_newBuff)
{
	for (auto& i : m_buffs)
	{
		if (!i->active)
		{
			i = t_newBuff;
			return;
		}
	}

	m_buffs.push_back(t_newBuff);
}

Buff& BuffHolder::getBuff(BuffName t_typeToGet)
{
	for (auto& i : m_buffs)
	{
		if (i->name == t_typeToGet)
		{
			return *i;
		}
	}
	Buff t;
	t.active = false;
	return t;
}

std::vector<std::shared_ptr<Buff>> BuffHolder::getOneTimeApplicators()
{
	std::vector<std::shared_ptr<Buff>> newBuffs;

	for (auto& i : m_buffs)
	{
		if (i->active)
		{
			if (i->applier == ApplicationType::Once)
			{
				newBuffs.push_back(i);
			}
		}
	}
	return newBuffs;
}

bool BuffHolder::getAlert()
{
	for (auto& i : m_buffs)
	{
		if (i->active)
		{
			if (i->applier == ApplicationType::Once)
			{
				return true;
			}
		}
	}
	return false;
}
