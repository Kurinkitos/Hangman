#include "Game.h"


Game::Game(void)
{
	m_gamestate = Game::UNINITIALIZED;
}


Game::~Game(void)
{
}

void Game::start()
{
	init();
	if(m_gamestate == Gamestate::UNINITIALIZED)
	{
		std::cout << "Something went wrong loading assets" << std::endl;
		exit(1);
	}
	while (m_gamestate != Gamestate::EXITING)
	{
		update();
		draw();
	}


}

void Game::init()
{
	m_window.create(sf::VideoMode(800, 600), "Hangman!");
	m_window.setFramerateLimit(60);

	if(!m_font.loadFromFile("opensans.ttf"))
		return;

	m_menuText.setFont(m_font);
	m_guessedLettersText.setFont(m_font);
	m_secretWordText.setFont(m_font);

	m_menuText.setString("PRESS ENTER TO CONTINUE THE MAGICAL ADVENTURE");

	m_gamestate = Gamestate::MENU;
}
void Game::update()
{
	sf::Event event;
    while (m_window.pollEvent(event))
    {
		if (event.type == sf::Event::Closed)
			m_gamestate = Gamestate::EXITING;
		switch (m_gamestate)
		{
		case Gamestate::MENU:
			if(event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					m_gamestate = Gamestate::PLAYING;
					break;
				}
			}
			break;
		case Gamestate::PLAYING:
			break;
		}
	}
}
void Game::draw()
{
	m_window.clear();

	switch (m_gamestate)
	{
	case Game::MENU:
		m_window.draw(m_menuText);
		break;
	case Game::PLAYING:
		break;
	}

	m_window.display();
}