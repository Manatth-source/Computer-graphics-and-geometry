#pragma once 

#include <SFML/Graphics.hpp>


class Canvas
{
private:
	const sf::RenderWindow* window_;

public:
	Canvas(const sf::RenderWindow& window);

	void setWindow(const sf::RenderWindow& window);
};

