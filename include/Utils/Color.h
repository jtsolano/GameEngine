#pragma once

class Color
{
public:

	Color() = default;
	~Color() = default;

	float R = 1.0f;
	float G = 1.0f;
	float B = 1.0f;

};

namespace Colors
{
	static const Color Cyan{ 0.0f, 1.0f, 1.0f };
	static const Color Green{ 0.0f, 1.0f, 0.0f };
	static const Color Blue{ 0.0f, 0.0f, 1.0f };
}