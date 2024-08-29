#include "Movement.h"
//#include "CollisionDetector.h"

sf::Vector2f Movement::calculateIntersects(std::vector<std::shared_ptr<sf::RectangleShape>>& t_walls, sf::Vector2f t_pos, float t_radius, sf::Vector2f t_castMove)
{
	sf::Vector2f futurePos = { 0.0f, 0.0f };
	sf::Vector2f position = t_pos;
	float Radius = t_radius;

	sf::Vector2f movement = t_castMove;

	bool left  = (movement.x < 0.f);
	bool right = (movement.x > 0.f);

	bool up    = (movement.y < 0.f);
	bool down  = (movement.y > 0.f);

	// Hard to explain
	// circle structure of the future position, this is the maths calculation to predict the future location
	// this will add the ray cast forward of the future position on each side and the middle
	// NOTE : Miniumum object width : 12.5

	const sf::Vector2f POSITIONS[] = { {(position.x - movement.x) - Radius, position.y + Radius} ,
									   {(position.x - movement.x) - Radius, position.y}          ,
									   {(position.x - movement.x) - Radius, position.y - Radius} ,

									   {(position.x + movement.x) + Radius, position.y + Radius} ,
									   {(position.x + movement.x) + Radius, position.y }         ,
									   {(position.x + movement.x) + Radius, position.y - Radius} ,

									   {position.x - Radius, (position.y - movement.y) - Radius} ,
									   {position.x, (position.y - movement.y) - Radius}          ,
									   {position.x + Radius, (position.y - movement.y) - Radius} ,

									   {position.x + Radius, (position.y + movement.y) + Radius} ,
									   {position.x, (position.y + movement.y) + Radius}          ,
									   {position.x - Radius, (position.y + movement.y) + Radius}  };

    for (int i = 0; i < t_walls.size(); i++)
    {
        if (movement.x != 0.f || movement.y != 0.f)
        {
			if(left)
			{
				futurePos = POSITIONS[0];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.x = 0;
				}
				futurePos = POSITIONS[1];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.x = 0;
				}
				futurePos = POSITIONS[2];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.x = 0;
				}
			}
			if(right)
			{
				futurePos = POSITIONS[3];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.x = 0;
				}
				futurePos = POSITIONS[4];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.x = 0;
				}
				futurePos = POSITIONS[5];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.x = 0;
				}
			}
			if(up)
			{
				futurePos = POSITIONS[6];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.y = 0;
				}
				futurePos = POSITIONS[7];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.y = 0;
				}
				futurePos = POSITIONS[8];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.y = 0;
				}
			}
			if(down)
			{
				futurePos = POSITIONS[9];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.y = 0;
				}
				futurePos = POSITIONS[10];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.y = 0;
				}
				futurePos = POSITIONS[11];
				if (t_walls.at(i)->getGlobalBounds().contains(futurePos))
				{
					movement.y = 0;
				}
			}
			
        }
        else
        {
            break;
        }
    }
	return movement;
}
