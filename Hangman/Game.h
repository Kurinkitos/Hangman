#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"
#include "WordGenerator.h"
class Game
{
public:
	Game(void);
	~Game(void);

	void start();
private:
	enum Gamestate
	{
		UNINITIALIZED,
		MENU,
		PLAYING,
		EXITING
	};
	void init();
	void update();
	void draw();

	WordGenerator m_wordGenerator;

	std::string m_guessedLetters;
	std::string m_secretWord;

	Gamestate m_gamestate;
	sf::RenderWindow m_window;

	sf::Font m_font;

	sf::Text m_menuText;
	sf::Text m_guessedLettersText;
	sf::Text m_secretWordText;


};

