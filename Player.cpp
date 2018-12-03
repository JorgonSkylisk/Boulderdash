// Project Includes
#include "Player.h"
#include "Level.h"
#include "Framework/AssetManager.h"

Player::Player()
	: GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerWalkDown1.png"));
}

void Player::Input(sf::Event _gameEvent)
{
	// Read input from player and convert it into a direction then move in that direction

	// was event a key Press?
	if (_gameEvent.type == sf::Event::KeyPressed)
	{
		//It was a keypress

		//Which key?
		if (_gameEvent.key.code == sf::Keyboard::W)
		{
			// it was W so move Up
			AttemptMove(sf::Vector2i(0, -1));
		}
		else if (_gameEvent.key.code == sf::Keyboard::A)
		{
			// it was A so move Left
			AttemptMove(sf::Vector2i(-1, 0));
		}
		else if (_gameEvent.key.code == sf::Keyboard::S)
		{
			// it was S so move Down
			AttemptMove(sf::Vector2i(0, 1));
		}
		else if (_gameEvent.key.code == sf::Keyboard::D)
		{
			// it was D so move Right
			AttemptMove(sf::Vector2i(1, 0));
		}
	}

}

bool Player::AttemptMove(sf::Vector2i _direction)
{
	// Attempt to move in given direction

	// Get current position
	// Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	// Check if space ahead is empty

	// If Empty move to target
	return m_level->moveObjectTo(this, targetPos);
}