#pragma once
#include <string>

struct Color
{
	inline static unsigned int max = 255;

	unsigned int r;		//value between 0 and 255
	unsigned int g;		//value between 0 and 255
	unsigned int b;		//value between 0 and 255
	unsigned int alpha;	//value between 0 and 255

	Color() : Color(0, 0, 0, max) {};
	Color(const unsigned int a_r, const unsigned int a_g, const unsigned int a_b, const unsigned int a_alpha);
	Color(const unsigned int a_r, const unsigned int a_g, const unsigned int a_b) : Color(a_r, a_g, a_b, max){};
	Color(const Color& a_other);

	inline float GetRedUnit()	{ return (float)r / (float)max; };
	inline float GetGreenUnit() { return (float)g / (float)max; };
	inline float GetBlueUnit()	{ return (float)b / (float)max; };
	inline float GetAlphaUnit() { return (float)alpha / (float)max; };

	Color& operator=(const Color a_other);

	Color operator/(const float a_value);
	Color& operator/=(const float a_value);

	Color operator*(const float a_value);
	Color& operator*=(const float a_value);

	static Color Hex(const unsigned int a_hexValue);

private:
	inline unsigned int clamp(const unsigned int a_value) { return a_value < max ? a_value : max; };
};