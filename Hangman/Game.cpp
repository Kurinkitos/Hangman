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
	m_wordGenerator.init("words.txt");

	m_menuText.setFont(m_font);
	m_guessedLettersText.setFont(m_font);
	m_secretWordText.setFont(m_font);
	m_winText.setFont(m_font);
	m_lossText.setFont(m_font);

	m_guessedLettersText.setPosition(400, 100);
	m_secretWordText.setPosition(400, 300);
	

	m_menuText.setString("Press a letter on your keyboard to guess it\nGuess the correct word before the man gets hanged!\nPress enter the continue");
	m_menuText.setPosition(400 - (m_menuText.getGlobalBounds().width/2), 300 - (m_menuText.getGlobalBounds().height/2));

	m_secretWord = m_wordGenerator.getWord();
	m_secretWordDisplay.resize(m_secretWord.size());
	for(size_t i=0; i < m_secretWordDisplay.size(); i++)
	{
		m_secretWordDisplay[i] = '_';
	}
	m_secretWordText.setString(m_secretWordDisplay);

	m_timesGuessed = 0;

	m_visualCountdown.init(sf::Vector2f(200, 150));
	

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
			if(event.type == sf::Event::KeyReleased)
			{
				if(event.key.code < 26)
				{
					processLetter(KeyboardUtil::convertKeyCodeToChar(event.key.code));
				}
			}
			break;
		case Gamestate::WON:
			if(event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					resetGame();
					break;
				case sf::Keyboard::Escape:
					m_gamestate = Gamestate::EXITING;
				}
			}
			break;
		case Gamestate::LOST:
			if(event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					resetGame();
					break;
				case sf::Keyboard::Escape:
					m_gamestate = Gamestate::EXITING;
				}
			}
			break;
		}
	}
	switch (m_gamestate)
	{
	case Game::UNINITIALIZED:
		break;
	case Game::MENU:
		break;
	case Game::PLAYING:
			m_guessedLettersText.setString(m_guessedLetters);
			m_secretWordText.setString(m_secretWordDisplay);
			if(hasWon())
				m_gamestate = Gamestate::WON;
			if(hasLost())
				m_gamestate = Gamestate::LOST;
		break;
	case Game::WON:
			m_winText.setString("You won!\nYou had to guess: " + std::to_string(m_timesGuessed) + "\nPress Enter to play again, or press escape to exit");
			m_winText.setPosition(400 - (m_winText.getGlobalBounds().width/2), 300 - (m_winText.getGlobalBounds().height/2));
		break;
	case Game::LOST:
			m_lossText.setString("You lost!\nPress Enter to play again, or press escape to exit");
			m_lossText.setPosition(400 - (m_lossText.getGlobalBounds().width/2), 300 - (m_lossText.getGlobalBounds().height/2));
		break;
	case Game::EXITING:
		break;
	default:
		break;
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
		m_window.draw(m_secretWordText);
		m_window.draw(m_guessedLettersText);
		m_window.draw(m_visualCountdown);
		break;
	case Gamestate::WON:
		m_window.draw(m_winText);
		break;
	case Gamestate::LOST:
		m_window.draw(m_lossText);
		break;
	}

	m_window.display();
}

void Game::processLetter(char letter)
{
	//Check if letter has been entered before
	if((m_guessedLetters.find(letter) != std::string::npos) || (m_secretWordDisplay.find(letter) != std::string::npos))
		return;
	//check if it is part of the secret word, and add it to secretWordDisplay if it is
	for(size_t i=0; i < m_secretWord.size(); i++)
	{
		if(m_secretWord[i] == letter)
			m_secretWordDisplay[i] = letter; //Index * 2 since the spaces in the display strings are added at positions 1, 3, 5 and so on
	}
	//If the letter is incorrect, add it to guessedLetters and increment number of guesses
	if(m_secretWord.find(letter) == std::string::npos)
	{
		m_guessedLetters += letter;
		m_timesGuessed++;
		m_visualCountdown.increment();
	}
}

bool Game::hasWon()
{
	if(m_secretWord == m_secretWordDisplay)
	{
		return true;
	}
	return false;
}
bool Game::hasLost()
{
	if(m_timesGuessed >= 10)
	{
		return true;
	}
	return false;
}

void Game::resetGame()
{
	m_guessedLetters = "";
	m_secretWord = m_wordGenerator.getWord();
	m_secretWordDisplay.resize(m_secretWord.size());
	for(size_t i=0; i < m_secretWordDisplay.size(); i++)
	{
		m_secretWordDisplay[i] = '_';
	}
	m_secretWordText.setString(m_secretWordDisplay);

	m_visualCountdown.reset();

	m_gamestate = Gamestate::MENU;
}