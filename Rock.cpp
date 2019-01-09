// Project Includes
#include "Level.h"
#include "Rock.h"
#include "Framework/AssetManager.h"
#include "Exit.h"
#include "Player.h"
#include "Diamond.h"

Rock::Rock()
	: GridObject()
	, m_stored(false)

	, m_timer(0)
	, m_falltimer(0.5)
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
	m_blocksMovement = true;

}

bool Rock::Remove(sf::Vector2i _direction)
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

void Rock::Update(sf::Time _frameTime)
{

	m_timer += _frameTime.asSeconds();

	if (m_timer > m_falltimer)
	{

		AttemptDrop(sf::Vector2i(0, 1));
		m_timer = 0;

	}

}

bool Rock::AttemptDrop(sf::Vector2i _direction)
{
	// Attempt to move the box in the given direction

	// Get current position

	// Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	// TODO: Check if the space is empty
	// Get list of objects in target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	// Check if any of those objects block movement 
	bool blocked = false;
	GridObject* blocker = nullptr;

	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;
			blocker = targetCellContents[i];
		}

	}

	// If empty, move there
	if (blocked == false)
	{

		return m_level->MoveObjectTo(this, targetPos);
	}
	else
	{
		Player* player = dynamic_cast<Player*>(blocker);

		// If drops on player, not nullptr
		if (player != nullptr)
		{
			//Delete player
			m_level->RemoveObject(blocker);
			//Move to the new spot
			return m_level->MoveObjectTo(this, targetPos);
		}

		if (_direction.x == 0)
		{

			Diamond* diamond = dynamic_cast<Diamond*>(blocker);
			Rock* rock = dynamic_cast<Rock*>(blocker);
			if (diamond != nullptr || rock != nullptr)
			{
				AttemptDrop(sf::Vector2i(1, 1));

				bool slideRightSucceed = AttemptDrop(sf::Vector2i(1, 1));

				if (!slideRightSucceed)
				{
						return AttemptDrop(sf::Vector2i(-1, 1));

				}
				else
				{
					return true;

				}
			}
		}

	}

	// if movement is block do nothing, return false
	return false;
}
