#ifndef EXTRACT_MANAGER_H
#define EXTRACT_MANAGER_H

#include "Player.h"
#include "Extractor.h"

class ExtractManager
{
public:
	void checkExtract(Player& t_player, EnemyManager& t_enemyManager);

private:
	std::vector<ExtractorCharacter> m_extractors;
	std::shared_ptr<sf::RectangleShape> m_fadeSquare;
	float m_fadeTime{ 0.f };
	float m_wait{ 0.f };
	bool m_leave{ false };
	bool m_fadeLast{ false };

	bool m_dying{ false }; // the check if the player is dying (for extraction)
};

#endif // !EXTRACT_MANAGER_H
