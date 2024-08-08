#include "cameraTracker.h"
#include "simpleMaths.h"
#include "RenderObject.h"
#include "Game.h"

CameraTracker::CameraTracker()
{
	m_currentPosition = RenderObject::getInstance().getCameraView().getCenter();
}

void CameraTracker::setCameraType(CameraType const& t_type)
{
	m_followType = t_type;
}

void CameraTracker::update(sf::Vector2f const& t_trackPos)
{
	switch (m_followType)
	{
	case CameraTracker::CameraType::Locked:
		// no movement for locked type
		break;
	case CameraTracker::CameraType::Delayed_Follow:
	{
		// camera movement logic for delayed follow
		float travelSpeed = static_cast<float>(math::distance(m_currentPosition, t_trackPos) / 3.0f);
		if (travelSpeed < 1.0f)
		{
			travelSpeed = 1.0f;
		}
		sf::Vector2f displacement = t_trackPos - m_currentPosition;
		displacement /= std::sqrtf(displacement.x * displacement.x + displacement.y * displacement.y);
		displacement = displacement * (travelSpeed / Game::deltaTime / 1000.f);
		m_currentPosition += displacement;
	}
	break;
	default:
		break;
	}
	RenderObject::getInstance().setCamera(m_currentPosition);
}