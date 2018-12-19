#pragma once

// Project Includes
#include "GridObject.h"

class Dirt : public GridObject
{

public:

	Dirt();

	bool Remove(sf::Vector2i _direction);
};