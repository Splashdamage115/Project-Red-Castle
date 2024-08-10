#ifndef PARTICLES_H
#define PARTICLES_H

#include "Library.h"

class ParticleSystem;

// simple particle that will be a shape that is asigned
class Particle
{
public:
	void update();
	bool getActive() { return m_active; }

	Particle(std::shared_ptr<sf::Shape> t_body, sf::Vector2f t_direction, float t_speed, float t_lifeTime);
private:
	std::shared_ptr<sf::Shape> m_body;
	sf::Vector2f m_displacement;
	float m_maxTime{ 1.0f };
	float m_lifeTime{ 1.0f };
	bool m_active{ false };
	unsigned int m_alpha{ 255 };
};

// simple particle for text objects
class TextParticle
{
public:
	void update();
	bool getActive() { return m_active; }

	TextParticle(std::shared_ptr<sf::Text> t_body, sf::Vector2f t_direction, float t_speed, float t_lifeTime);
private:
	std::shared_ptr<sf::Text> m_body;
	sf::Vector2f m_displacement;
	float m_lifeTime{ 1.0f };
	float m_maxTime{ 1.0f };
	bool m_active{ false };
	unsigned int m_alpha{ 255 };
};

// handler for the spawning of the particles
class ParticleSystem
{
public:
	// change particle system to singleton so it can store the particles array
	static ParticleSystem& getInstance()
	{
		static ParticleSystem instance;
		return instance;
	}
	// DELETE FUNCTIONS TO AVOID MORE INSTANCES
	ParticleSystem(ParticleSystem const&) = delete;
	void operator=(ParticleSystem const&) = delete;

	void spawnNewParticle(std::string t_displayed, sf::Vector2f t_spawnPos , unsigned int textSize, sf::Vector2f t_direction, float t_speed = 50.f, float t_lifeTime = 1.f, float t_spread = 0.f, sf::Color t_color = sf::Color::White);
	//void spawnNewParticle(sf::Texture t_displayed, sf::Vector2f t_direction, float t_speed = 50.f, float t_lifeTime = 1.f);
	void spawnNewParticle(float t_radius, sf::Vector2f t_spawnPos, sf::Vector2f t_direction, float t_speed = 50.f, float t_lifeTime = 1.f, sf::Color t_color = sf::Color::White);
	void spawnNewParticle(sf::Vector2f t_size, sf::Vector2f t_spawnPos, sf::Vector2f t_direction, float t_speed = 50.f, float t_lifeTime = 1.f, sf::Color t_color = sf::Color::White);

	void update();
private:
	ParticleSystem(){};
	std::vector<std::shared_ptr<Particle>> m_particles;
	std::vector< std::shared_ptr<TextParticle>> m_textParticles;
};

#endif // !PARTICLES_H
