#pragma once
#include <cstdint>
#include <iostream>


namespace core {
	struct Color
	{
		std::uint8_t r = 0;
		std::uint8_t g = 0;
		std::uint8_t b = 0;
	};

    inline std::istream& operator>>(std::istream& in, Color& color)
    {
        short r, g, b;
        in >> r >> g >> b;
        color.r = static_cast<std::uint8_t>(std::clamp(r, (short)0, (short)255));
        color.g = static_cast<std::uint8_t>(std::clamp(g, (short)0, (short)255));
        color.b = static_cast<std::uint8_t>(std::clamp(b, (short)0, (short)255));

        return in;
    }

}