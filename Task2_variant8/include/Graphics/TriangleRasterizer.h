#pragma once

#include "Core/Canvas.h"


struct Vertex 
{
	int x, y;
	sf::Color color;
};


class TriangleRasterizer
{
private:
	Vertex A_;
	Vertex B_;
	Vertex C_;
public:
	TriangleRasterizer(Vertex a, Vertex b, Vertex c);

	void fillTriangle(const Canvas& canves);
};