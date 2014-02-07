#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include <cmath>
class VisualCountdown : public sf::Drawable
{
public:
	VisualCountdown(void);
	~VisualCountdown(void);

	void increment();

	void init(sf::Vector2f);
	void update();

	void reset();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	sf::Vector2f m_position;
	int m_guesses;
	std::vector<sf::Shape*> m_shapes;
};

