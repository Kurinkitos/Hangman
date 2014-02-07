#include "VisualCountdown.h"


VisualCountdown::VisualCountdown(void)
{
	for(size_t i=0; i < m_shapes.size(); i++)
	{
		m_shapes[i] = 0x0;
	}
}


VisualCountdown::~VisualCountdown(void)
{
	for(size_t i=0; i < m_shapes.size(); i++)
	{
		delete m_shapes[i]; //Since we used new we must cleanup!
	}
}

void VisualCountdown::init(sf::Vector2f position)
{
	m_guesses = 0;

	m_position = position;
	m_shapes.resize(10);

	const float PI = 3.141592f;

	//The base, a half circle
	sf::ConvexShape *base = new sf::ConvexShape(40);
	base->setFillColor(sf::Color::White);
	float angle = 200.0f/40;
	for(int i=0; i < 40; i++)
	{
		float xPos = 150 * -cos((angle*i*PI)/180);
		float yPos = 150 * -sin((angle*i*PI)/180);
		base->setPoint(i, sf::Vector2f(xPos, yPos));
		
	}
	base->setPosition(position + sf::Vector2f(-50, 450));
	m_shapes[0] = base;

	//The Main Pole, a Rectangle
	sf::RectangleShape *pole = new sf::RectangleShape();
	pole->setSize(sf::Vector2f(20, 300));
	pole->setFillColor(sf::Color::White);
	pole->setPosition(sf::Vector2f(position + sf::Vector2f(-60, 0)));
	m_shapes[1] = pole;

	//The side beam, a Rectangle
	sf::RectangleShape *beam = new sf::RectangleShape();
	beam->setSize(sf::Vector2f(150, 20));
	beam->setFillColor(sf::Color::White);
	beam->setPosition(sf::Vector2f(position + sf::Vector2f(-50, 0)));
	m_shapes[2] = beam;
	
	//The support beam, a Rectangle
	sf::RectangleShape *support = new sf::RectangleShape();
	support->setSize(sf::Vector2f(85, 20));
	support->setFillColor(sf::Color::White);
	support->setRotation(-45.0f);
	support->setPosition(position + sf::Vector2f(-55, 65));
	m_shapes[3] = support;

	//The rope, a Rectangle
	sf::RectangleShape *rope = new sf::RectangleShape();
	rope->setSize(sf::Vector2f(5, 60));
	rope->setFillColor(sf::Color::White);
	rope->setPosition(position + sf::Vector2f(80, 0));
	m_shapes[4] = rope;
}
void VisualCountdown::update()
{

}
void VisualCountdown::increment()
{
	m_guesses++;
}

void VisualCountdown::reset()
{
	m_guesses = 0;
}


void VisualCountdown::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(int i=0; i < m_guesses; i++)
	{
		if(m_shapes[i] != 0x0)
			target.draw(*m_shapes[i]);
	}
}