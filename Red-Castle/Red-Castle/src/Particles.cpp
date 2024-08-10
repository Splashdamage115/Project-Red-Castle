#include "Particles.h"
#include "Game.h"
#include "RenderObject.h"
#include "GlobalFontStorage.h"
#include "math.h"

// update the shape particle
void Particle::update()
{
	m_body->move(m_displacement * Game::deltaTime);

	m_lifeTime -= Game::deltaTime;
	if (m_lifeTime <= 0.f)
	{
		m_active = false;
	}
	sf::Color color = m_body->getFillColor();
	color.a = static_cast<int>(m_alpha * (m_lifeTime / m_maxTime));
	m_body->setFillColor(color);
}

// initialiser of the shape particle
Particle::Particle(std::shared_ptr<sf::Shape> t_body, sf::Vector2f t_direction, float t_speed, float t_lifeTime)
{
	m_body = t_body;
	m_displacement = t_direction * t_speed;
	m_lifeTime = t_lifeTime;
	m_active = true;
	m_maxTime = t_lifeTime;
	m_alpha = t_body->getFillColor().a;

	RenderObject::getInstance().addParticles(m_body);
}

// update the text particle
void TextParticle::update()
{
	m_body->move(m_displacement * Game::deltaTime);

	m_lifeTime -= Game::deltaTime;
	if (m_lifeTime <= 0.f)
	{
		m_active = false;
	}
	sf::Color color = m_body->getFillColor();
	color.a = static_cast<int>(m_alpha * (m_lifeTime / m_maxTime));
	m_body->setFillColor(color);
}

// initialiser of the text particle
TextParticle::TextParticle(std::shared_ptr<sf::Text> t_body, sf::Vector2f t_direction, float t_speed, float t_lifeTime)
{
	m_body = t_body;
	m_displacement = t_direction * t_speed;
	m_lifeTime = t_lifeTime;
	m_alpha = t_body->getFillColor().a;
	m_maxTime = t_lifeTime;
	m_active = true;

	RenderObject::getInstance().addParticles(m_body);
}





/// <summary>
/// Spawn a text based particle with the assigned display text
/// 
/// </summary>
/// <param name="t_displayed">visible text</param>
/// <param name="t_spawnPos">where the particle spawns</param>
/// <param name="textSize">size of the text</param>
/// <param name="t_direction">which direction the text will move</param>
/// <param name="t_speed">what speed the text will move</param>
/// <param name="t_lifeTime">how long the text will live</param>
void ParticleSystem::spawnNewParticle(std::string t_displayed, sf::Vector2f t_spawnPos, unsigned int textSize, sf::Vector2f t_direction, float t_speed, float t_lifeTime, float t_spread, sf::Color t_color)
{
	// Particle :
	// std::shared_ptr<sf::Shape> t_body, sf::Vector2f t_spawnPos, sf::Vector2f t_direction, float t_speed, float t_lifeTime

	std::shared_ptr<sf::Text> shown;
	shown = std::make_shared<sf::Text>();
	shown->setPosition(t_spawnPos);
	shown->setString(t_displayed);
	shown->setCharacterSize(textSize);
	shown->setFont(*GlobalFontStorage::getInstance().getFont());
	shown->setOrigin(sf::Vector2f(shown->getGlobalBounds().width / 2.f, shown->getGlobalBounds().height / 2.f));
	shown->setFillColor(t_color);

	sf::Vector2f moveDirection = t_direction;

	if (t_spread > 0.f)
	{
		float moveAngle = math::displacementToDegrees(moveDirection);
		moveAngle += (rand() % static_cast<int>(t_spread)) - (t_spread / 2.f);

		moveDirection = math::degreesToDisplacement(moveAngle);
	}
	
	std::shared_ptr<TextParticle> newParticle;
	newParticle = std::make_shared<TextParticle>(shown, moveDirection, t_speed, t_lifeTime);

	for (unsigned int i = 0; i < m_textParticles.size(); i++)
		if (m_textParticles.at(i) == nullptr)
		{
			m_textParticles.at(i) = newParticle;
			return;
		}
	m_textParticles.push_back(newParticle);
}


/// <summary>
/// used to spawn a new circle
/// </summary>
/// <param name="t_radius">radius of the circle</param>
/// <param name="t_spawnPos">position it spawns</param>
/// <param name="t_direction">what direction it goes</param>
/// <param name="t_speed">speed of the circle</param>
/// <param name="t_lifeTime">how long the circle lives</param>
/// <param name="t_color">what colour the circle will be</param>
void ParticleSystem::spawnNewParticle(float t_radius, sf::Vector2f t_spawnPos, sf::Vector2f t_direction, float t_speed, float t_lifeTime, sf::Color t_color)
{
	// Particle :
	// std::shared_ptr<sf::Shape> t_body, sf::Vector2f t_spawnPos, sf::Vector2f t_direction, float t_speed, float t_lifeTime

	std::shared_ptr<sf::CircleShape> shown;
	shown = std::make_shared<sf::CircleShape>();
	shown->setPosition(t_spawnPos);
	shown->setRadius(t_radius);
	shown->setFillColor(t_color);
	shown->setOrigin(sf::Vector2f(shown->getGlobalBounds().width / 2.f, shown->getGlobalBounds().height / 2.f));

	std::shared_ptr<Particle> newParticle;
	newParticle = std::make_shared<Particle>(shown, t_direction, t_speed, t_lifeTime);

	bool created = false;
	for (unsigned int i = 0; i < m_particles.size(); i++)
		if (m_particles.at(i) == nullptr)
		{
			m_particles.at(i) = newParticle;
			created = true;
			break;
		}
	if (!created)
		m_particles.push_back(newParticle);
}

/// <summary>
/// spawn new rectangle shape
/// </summary>
/// <param name="t_size">size of the rectangle</param>
/// <param name="t_spawnPos">where the rectangle spawns</param>
/// <param name="t_direction">direction the rectangle will move</param>
/// <param name="t_speed">speed of the rectangle</param>
/// <param name="t_lifeTime">how long the rectangle will live</param>
/// <param name="t_color">what colour will the rectangle be</param>
void ParticleSystem::spawnNewParticle(sf::Vector2f t_size, sf::Vector2f t_spawnPos, sf::Vector2f t_direction, float t_speed, float t_lifeTime, sf::Color t_color)
{
	// Particle :
	// std::shared_ptr<sf::Shape> t_body, sf::Vector2f t_spawnPos, sf::Vector2f t_direction, float t_speed, float t_lifeTime

	std::shared_ptr<sf::RectangleShape> shown;
	shown = std::make_shared<sf::RectangleShape>();
	shown->setPosition(t_spawnPos);
	shown->setSize(t_size);
	shown->setFillColor(t_color);
	shown->setOrigin(sf::Vector2f(shown->getGlobalBounds().width / 2.f, shown->getGlobalBounds().height / 2.f));

	std::shared_ptr<Particle> newParticle;
	newParticle = std::make_shared<Particle>(shown, t_direction, t_speed, t_lifeTime);

	bool created = false;
	for (unsigned int i = 0; i < m_particles.size(); i++)
		if (m_particles.at(i) == nullptr)
		{
			m_particles.at(i) = newParticle;
			created = true;
			break;
		}
	if (!created)
		m_particles.push_back(newParticle);
}

/// <summary>
/// update all particles, used for settiing positions
/// </summary>
void ParticleSystem::update()
{
	for (unsigned int i = 0; i < m_particles.size(); i++)
	{
		if (m_particles.at(i) != nullptr)
		{
			m_particles.at(i)->update();
			if (!m_particles.at(i)->getActive())
				m_particles.at(i) = nullptr;
		}
	}
	for (unsigned int i = 0; i < m_textParticles.size(); i++)
	{
		if (m_textParticles.at(i) != nullptr)
		{
			m_textParticles.at(i)->update();
			if (!m_textParticles.at(i)->getActive())
				m_textParticles.at(i) = nullptr;
		}
	}
}
