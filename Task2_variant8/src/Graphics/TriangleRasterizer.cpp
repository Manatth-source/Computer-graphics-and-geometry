#include "Graphics/TriangleRasterizer.h"


TriangleRasterizer::TriangleRasterizer(Vertex a, Vertex b, Vertex c)
	: A_(a)
	, B_(b)
	, C_(c)
{
}


void TriangleRasterizer::fillTriangle(core::Canvas & canves)
{
	if (A_.y > B_.y) std::swap(A_, B_);
	if (A_.y > C_.y) std::swap(A_, C_);
	if (B_.y > C_.y) std::swap(B_, C_);
}