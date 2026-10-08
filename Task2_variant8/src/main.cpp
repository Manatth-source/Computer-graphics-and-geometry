#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

#include "Core/Canvas.h"
#include "Core/Color.h"
#include "Graphics/TriangleRasterizer.h"

#define NOMINMAX
#include <windows.h>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	sf::RenderWindow window(sf::VideoMode({ 1600, 900 }), "Triangle rasterizer");
	window.setFramerateLimit(30);

	core::Canvas canvas(window);
	
	std::cout << "Ведите координаты (x, y) трёх точек: ";
	int ax, ay, bx, by, cx, cy; 
	std::cin >> ax >> ay >> bx >> by >> cx >> cy;

	std::cout << "Введите цвета для каждой из трёх точек в формате rgb:\n";
	core::Color color_a, color_b, color_c; std::cin >> color_a >> color_b >> color_c;

	Vertex a{ ax,  ay, color_a };
	Vertex b{ bx, by, color_b };
	Vertex c{ cx, cy, color_c };
	TriangleRasterizer triangle(a, b, c);


	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		canvas.clear(sf::Color::Black);
		triangle.fillTriangle(canvas);
		canvas.display();
	}

	return 0;
}