#include "GameWin.h"
#include "Core/Data.h"


bool GameWin::init()
{
	animated_background.SetupAnimatedSprite("Data/Menu/helicopterwin.png", sf::Vector2i(200, 122), 2);
	fix_cursor.loadFromSystem(sf::Cursor::Type::Arrow);
	return true;
}

void GameWin::start()
{
	Data::GetInstance()->window->setMouseCursor(fix_cursor);
}

void GameWin::update(float dt)
{
	animated_background.Animate(dt);
	Data::GetInstance()->window->setMouseCursor(fix_cursor);
}


void GameWin::render()
{
	Data::RenderBackground(animated_background.sprite);
}



void GameWin::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Enter)
	{
		Data::GetInstance()->gamestate = Data::Menu;
		Data::GetInstance()->OnGameStateSwitch();
	}
}

void GameWin::keyReleased(sf::Event event)
{

}