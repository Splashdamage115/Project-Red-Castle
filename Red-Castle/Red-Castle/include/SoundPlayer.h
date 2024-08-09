#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <SFML/Audio.hpp>
#include "DEBUG.h"

//sf::Sound sound;
//sound.setBuffer(buffer);
//sound.play();

class SoundPlayer
{
public:
    static SoundPlayer& getInstance()
    {
        static SoundPlayer instance;
        return instance;
    }

    // DELETE FUNCTIONS TO AVOID MORE INSTANCES
    SoundPlayer(SoundPlayer const&) = delete;
    void operator=(SoundPlayer const&) = delete;

    void playNewSound(std::string t_soundLocation)
    {
        for (unsigned int i = 0; i < m_locations.size(); i++)
        {
            if (t_soundLocation == m_locations.at(i))
            {
                m_sounds.at(i).play();
                return;
            }
        }
        if (m_buffer.size() < 255)
        {
            m_locations.push_back(t_soundLocation);
            m_buffer.emplace_back();
            if (!m_buffer.back().loadFromFile(t_soundLocation))
            {
                DEBUG_MSG("Couldnt find sound: ");
                DEBUG_MSG(t_soundLocation);
                return;
            }
            m_sounds.emplace_back();
            m_sounds.back().setBuffer(m_buffer.back());
            m_sounds.back().play();
            return;

        }
        else
        {
            // TO DO: get a backup sound player playing
        }
    }

private:
	SoundPlayer() {}
    std::vector<sf::Sound> m_sounds;
    std::vector<sf::SoundBuffer> m_buffer;
    std::vector<std::string> m_locations;
};


#endif // !SOUND_PLAYER_H
