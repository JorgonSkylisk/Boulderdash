#pragma once

// Project Includes
#include "GridObject.h"

class Rock : public GridObject
{

public:

	Rock();

	bool Remove(sf::Vector2i _direction);
	void Update(sf::Time _frameTime);
	bool AttemptDrop(sf::Vector2i _direction);


private:

	bool m_stored;



	float m_timer;
	float m_falltimer;

};
