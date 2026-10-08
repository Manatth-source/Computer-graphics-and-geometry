#pragma once

#include "Core/Canvas.h"
#include "Core/Color.h"

struct Vertex 
{
	int x, y;
	core::Color color;
};


class TriangleRasterizer
{
private:
	Vertex A_;
	Vertex B_;
	Vertex C_;
public:
	TriangleRasterizer(Vertex a, Vertex b, Vertex c);

	void fillTriangle(core::Canvas& canves);
};