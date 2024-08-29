#ifndef MOVEMENT_H
#define MOVEMENT_H
#include<SFML/Graphics.hpp>
#include<vector>

class Movement
{
public:
	void setSpeed(float t_moveSpeed) { m_moveSpeed = t_moveSpeed; }
	sf::Vector2f calculateIntersects(std::vector<std::shared_ptr<sf::RectangleShape>>& t_walls, sf::Vector2f t_pos, float t_radius, sf::Vector2f t_castMove);
private:
	float m_moveSpeed{ 1.f };
	sf::Vector2f m_movement{ 0.f,0.f };
};

#endif // !MOVEMENT_H
