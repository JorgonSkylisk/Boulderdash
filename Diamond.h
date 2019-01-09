#pragma once

// Project Includes
#include "GridObject.h"

class Diamond : public GridObject
{

public:

	Diamond();

	bool Remove(sf::Vector2i _direction);
	bool GetStored();

private:
	bool m_stored;
};