#pragma once

// Project Includes
#include "GridObject.h"

class Rock : public GridObject
{

public:

	Rock();

	bool AttemptPush(sf::Vector2i _direction);
};