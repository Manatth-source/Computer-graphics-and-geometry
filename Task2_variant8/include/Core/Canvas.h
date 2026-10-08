#pragma once 

#include <SFML/Graphics.hpp>

namespace core {

	class Canvas
	{
	private:
		sf::RenderWindow* window_;
		sf::VertexArray pixels_;

	public:
		Canvas(sf::RenderWindow& window);

		void setWindow(sf::RenderWindow& window);

		void clear(sf::Color color = sf::Color::Black);
		void putPixel(int x, int y, sf::Color color);
		void display();

		int getWidth() const;
		int getHeight() const;
	};

}