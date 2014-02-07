#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"
#include "WordGenerator.h"
#include "KeyboardUtil.h"
#include "VisualCountdown.h"
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
		WON,
		LOST,
		EXITING
	};
	void init();
	void update();
	void draw();

	void processLetter(char);

	bool hasWon();
	bool hasLost();

	void resetGame();

	WordGenerator m_wordGenerator;
	VisualCountdown m_visualCountdown;

	int m_timesGuessed;

	std::string m_guessedLetters;
	std::string m_secretWord;
	std::string m_secretWordDisplay;

	Gamestate m_gamestate;
	sf::RenderWindow m_window;

	sf::Font m_font;

	sf::Text m_menuText;
	sf::Text m_guessedLettersText;
	sf::Text m_secretWordText;
	sf::Text m_winText;
	sf::Text m_lossText;


};

