#pragma once

// Project Includes
#include "GridObject.h"

class Diamond : public GridObject
{

public:

	Diamond();

	bool Remove(sf::Vector2i _direction);
	void Update(sf::Time _frameTime);
	bool AttemptDrop(sf::Vector2i _direction);

private:

	float m_timer;
	float m_falltimer;
};
