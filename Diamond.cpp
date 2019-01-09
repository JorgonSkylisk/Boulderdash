// Project Includes
#include "Diamond.h"
#include "Framework/AssetManager.h"
#include "Level.h"

Diamond::Diamond()
	: GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/storage.png"));
	m_blocksMovement = true;
}

bool Diamond::Remove(sf::Vector2i _direction)
{
	// Get current position
	// Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	// TODO: Check if the space is empty

	// Get list of objects in our target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	// Check if any of those objects block movement
	bool blocked = false;
	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;
		}
	}

	// If empty, move there
	if (blocked == false)
		return m_level->MoveObjectTo(this, targetPos);

	// If movement is blocked, do nothing, return false
// Default
	return true;
}

bool Diamond::GetStored()
{
	return m_stored;
}