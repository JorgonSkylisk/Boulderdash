// Project Includes
#include "Exit.h"
#include "Framework/AssetManager.h"

Exit::Exit()
	: GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/exit_closed.png"));
	m_blocksMovement = true;
}
