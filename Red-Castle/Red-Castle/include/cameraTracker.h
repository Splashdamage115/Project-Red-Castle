#pragma once

#include "Library.h"


class CameraTracker
{
public:
/// <Enum Declerations>

	// what type of following the camera performs
	enum class CameraType { Locked, Delayed_Follow /*,Object_Follow?*/ };

/// </Enum Declerations>



	// standard constructor, sets up the tracker with default values
	CameraTracker();
	// change the type of the camera tracker
	void setCameraType(CameraType const& t_type);
	// updates the camera tracker based on the type of tracker selected
	void update(sf::Vector2f const& t_trackPos);



/// <Getters / Setters>
	// returns the view so that it can be set by the window
	inline sf::View& getView() { return m_view; }
/// </Getters / Setters>

private:

	// the camera type, changes what happens in update
	CameraType m_followType{ CameraType::Locked };

	// the view (stores positional values and scales)
	sf::View m_view;

	// current position of the camera (used for maths)
	sf::Vector2f m_currentPosition{ 0.f,0.f };
};
