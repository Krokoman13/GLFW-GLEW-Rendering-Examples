#include "Clolor.hpp"

Color::Color(const unsigned int a_r, const unsigned int a_g, const unsigned int a_b, const unsigned int a_alpha)
{
	r = clamp(a_r);
	g = clamp(a_g);
	b = clamp(a_b);
	alpha = clamp(a_alpha);
}

Color::Color(const Color& a_other)
{
	r = a_other.r;
	g = a_other.g;
	b = a_other.b;
	alpha = a_other.alpha;
}

Color& Color::operator=(const Color a_other)
{
	r = a_other.r;
	g = a_other.g;
	b = a_other.b;
	alpha = a_other.alpha;
	return *this;
}

Color Color::operator/(const float a_value)
{
	return Color(r / a_value, g / a_value, b / a_value, alpha / a_value);
}

Color& Color::operator/=(const float a_value)
{
	this->r /= a_value;
	this->g /= a_value;
	this->b /= a_value;
	this->alpha /= a_value;
	return *this;
}

Color Color::operator*(const float a_value)
{
	return Color(r * a_value, g * a_value, b * a_value, alpha * a_value);
}

Color& Color::operator*=(const float a_value)
{
	this->r * a_value;
	this->g *= a_value;
	this->b *= a_value;
	this->alpha *= a_value;
	return *this;
}

Color Color::Hex(const unsigned int hexValue)
{
	Color rgbColor;
	rgbColor.r = ((hexValue >> 16) & 0xFF);  // Extract the RR byte
	rgbColor.g = ((hexValue >> 8) & 0xFF);   // Extract the GG byte
	rgbColor.b = ((hexValue) & 0xFF);        // Extract the BB byte
	return rgbColor;
}
