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

	const float ax = static_cast<float>(A_.x), ay = static_cast<float>(A_.y);
	const float bx = static_cast<float>(B_.x), by = static_cast<float>(B_.y);
	const float cx = static_cast<float>(C_.x), cy = static_cast<float>(C_.y);

	const float denom = (by - cy) * (ax - cx) + (cx - bx) * (ay - cy);
	if (denom == 0.0f) return;

	for (int y = A_.y; y <= C_.y; ++y)
	{
		const float fy = static_cast<float>(y);

		const float xLong = ax + (fy - ay) / (cy - ay) * (cx - ax);

		float xShort;
		if (fy < by) 
			xShort = ax + (fy - ay) / (by - ay) * (bx - ax);
		else if (cy == by)
			xShort = bx;
		else
			xShort = bx + (fy - by) / (cy - by) * (cx - bx);

		const int xStart = static_cast<int>(std::lround(std::min(xLong, xShort)));
		const int xEnd = static_cast<int>(std::lround(std::max(xLong, xShort)));

		for (int x = xStart; x <= xEnd; ++x)
		{
			const float fx = static_cast<float>(x);

			const float alpha = ((by - cy) * (fx - cx) + (cx - bx) * (fy - cy)) / denom;
			const float beta = ((cy - ay) * (fx - cx) + (ax - cx) * (fy - cy)) / denom;
			const float gamma = 1.0f - alpha - beta;

			const float r = alpha * A_.color.r + beta * B_.color.r + gamma * C_.color.r;
			const float g = alpha * A_.color.g + beta * B_.color.g + gamma * C_.color.g;
			const float b = alpha * A_.color.b + beta * B_.color.b + gamma * C_.color.b;

			canves.putPixel(x, y, sf::Color(
				static_cast<std::uint8_t>(std::clamp(r, 0.0f, 255.0f)),
				static_cast<std::uint8_t>(std::clamp(g, 0.0f, 255.0f)),
				static_cast<std::uint8_t>(std::clamp(b, 0.0f, 255.0f))));
		}
	}
}