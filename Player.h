#pragma once

// Project Includes
#include "GridObject.h"

class Player : public GridObject
{

public:

	Player();

	// overriding methods
	virtual void Input(sf::Event _gameEvent);

protected:

	bool AttemptMove(sf::Vector2i _direction);
};