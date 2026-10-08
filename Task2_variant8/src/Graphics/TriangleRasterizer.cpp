#include "Graphics/TriangleRasterizer.h"


TriangleRasterizer::TriangleRasterizer(Vertex a, Vertex b, Vertex c)
	: A_(a)
	, B_(b)
	, C_(c)
{
}


void TriangleRasterizer::fillTriangle(core::Canvas& canvas)
{
	if (A_.y > B_.y) std::swap(A_, B_);
	if (A_.y > C_.y) std::swap(A_, C_);
	if (B_.y > C_.y) std::swap(B_, C_);

	const long long denomI =
		static_cast<long long>(B_.y - C_.y) * (A_.x - C_.x) +
		static_cast<long long>(C_.x - B_.x) * (A_.y - C_.y);
	if (denomI == 0) return; 

	const float ax = static_cast<float>(A_.x), ay = static_cast<float>(A_.y);
	const float bx = static_cast<float>(B_.x), by = static_cast<float>(B_.y);
	const float cx = static_cast<float>(C_.x), cy = static_cast<float>(C_.y);

	const float invDenom = 1.0f / static_cast<float>(denomI);

	const float dAlpha = (by - cy) * invDenom;
	const float dBeta = (cy - ay) * invDenom;

	const int width = canvas.getWidth();
	const int height = canvas.getHeight();

	const int yFrom = std::max(A_.y, 0);
	const int yTo = std::min(C_.y, height - 1);

	for (int y = yFrom; y <= yTo; ++y)
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

		const int xStart = std::max(static_cast<int>(std::lround(std::min(xLong, xShort))), 0);
		const int xEnd = std::min(static_cast<int>(std::lround(std::max(xLong, xShort))), width - 1);
		if (xStart > xEnd) continue;

		const float fx0 = static_cast<float>(xStart);
		float alpha = ((by - cy) * (fx0 - cx) + (cx - bx) * (fy - cy)) * invDenom;
		float beta = ((cy - ay) * (fx0 - cx) + (ax - cx) * (fy - cy)) * invDenom;

		for (int x = xStart; x <= xEnd; ++x)
		{
			const float gamma = 1.0f - alpha - beta;

			const float r = alpha * A_.color.r + beta * B_.color.r + gamma * C_.color.r;
			const float g = alpha * A_.color.g + beta * B_.color.g + gamma * C_.color.g;
			const float b = alpha * A_.color.b + beta * B_.color.b + gamma * C_.color.b;

			canvas.putPixel(x, y, sf::Color(
				static_cast<std::uint8_t>(std::clamp(r, 0.0f, 255.0f)),
				static_cast<std::uint8_t>(std::clamp(g, 0.0f, 255.0f)),
				static_cast<std::uint8_t>(std::clamp(b, 0.0f, 255.0f))));

			alpha += dAlpha;
			beta += dBeta;
		}
	}
}