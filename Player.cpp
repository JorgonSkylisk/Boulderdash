// Project Includes
#include "Player.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Dirt.h"
#include "Rock.h"
#include "Exit.h"
#include "Diamond.h"

Player::Player()
	: GridObject()
	, m_pendingMove(0, 0)
	, m_moveSound()
	, m_bumpSound()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));
	m_moveSound.setBuffer(AssetManager::GetSoundBuffer("audio/footstep1.ogg"));
	m_bumpSound.setBuffer(AssetManager::GetSoundBuffer("audio/bump.wav"));
	m_blocksMovement = true;
}

void Player::Input(sf::Event _gameEvent)
{
	// Read the input from the keyboard and convert it
	// to a direction to move in (and then move)

	// Was the event a key press?
	if (_gameEvent.type == sf::Event::KeyPressed)
	{
		// Yes it was a key press!

		// What key was pressed?
		if (_gameEvent.key.code == sf::Keyboard::W)
		{
			// It was W!
			// Move up
			m_pendingMove = sf::Vector2i(0, -1);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandUp.png"));
		}
		else if (_gameEvent.key.code == sf::Keyboard::A)
		{
			// It was A!
			// Move left
			m_pendingMove = sf::Vector2i(-1, 0);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandLeft.png"));
		}
		else if (_gameEvent.key.code == sf::Keyboard::S)
		{
			// It was S!
			// Move down
			m_pendingMove = sf::Vector2i(0, 1);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));
		}
		else if (_gameEvent.key.code == sf::Keyboard::D)
		{
			// It was D!
			// Move right
			m_pendingMove = sf::Vector2i(1, 0);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandRight.png"));
		}
	}
}

void Player::Update(sf::Time _frameTime)
{
	// If we have movement waiting to be processed,
	if (m_pendingMove.x != 0 || m_pendingMove.y != 0)
	{
		// move in that direction
		bool moveSuccessful = AttemptMove(m_pendingMove);

		// Play movememnt sound
		if (moveSuccessful == true)
		{
			m_moveSound.play();
		}
		else
		{
			m_bumpSound.play();
		}

		// and clear the pending movement
		m_pendingMove = sf::Vector2i(0, 0);
	}
}


bool Player::AttemptMove(sf::Vector2i _direction)
{
	// Attempt to move in the given direction

	// Get current position
	// Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	// TODO: Check if the space is empty

	// Get list of objects in our target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	// Check if any of those objects block movement
	bool blocked = false;
	GridObject* Blocker = nullptr;
	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;
			Blocker = targetCellContents[i];

		}
	}

	// If empty, move there
	if (blocked == false)
		return m_level->MoveObjectTo(this, targetPos);
	else
	{
		//Blocked
		//Can blockage be pushed 
		Rock* PushableRock = dynamic_cast<Rock*>(Blocker);
		Dirt* dirt = dynamic_cast<Dirt*>(Blocker);
		Diamond* diamond = dynamic_cast<Diamond*>(Blocker);
		Exit* exit = dynamic_cast<Exit*>(Blocker);

		if (dirt != nullptr)
		{
			m_level->RemoveObject(Blocker);
			return m_level->MoveObjectTo(this, targetPos);
		}

		if (diamond != nullptr)
		{
			m_level->RemoveObject(Blocker);
			return m_level->MoveObjectTo(this, targetPos);
		}

		if (exit != nullptr)
		{

			//check if level complete
			m_level->CheckComplete();
			return m_level->MoveObjectTo(this, targetPos);
		}

		//if so attempt to push 
		if (PushableRock != nullptr)
		{
			bool pushSucceeded = PushableRock->AttemptDrop(_direction);
			//if push succeeded 
			if (pushSucceeded == true)
			{
				return m_level->MoveObjectTo(this, targetPos);
			}
			//move to new spot(where blockage was)
		}

	}

	// If movement is blocked, do nothing, return false
	// Default
	return false;
}

bool Player::Delete(sf::Vector2i _direction)
{
	// Attempt to move in the given direction

	// Get current position
	// Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	// TODO: Check if the space is empty

	// Get list of objects in our target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	// Check if any of those objects block movement
	bool blocked = false;
	GridObject* Blocker = nullptr;
	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;
			Blocker = targetCellContents[i];

		}
	}

	// If empty, move there
	if (blocked == false)
		return m_level->MoveObjectTo(this, targetPos);
	else
	{
		//Blocked
		//Can blockage be pushed 
		Dirt* dirt = dynamic_cast<Dirt*>(Blocker);

		//if so attempt to push 
		if (dirt != nullptr)
		{

				return m_level->RemoveObject(this);
			
		}

	}

	// If movement is blocked, do nothing, return false
	// Default
	//return false;
}