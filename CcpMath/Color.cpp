////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Snorri Sturluson
// Created:		May 2013
// Copyright:	CCP 2013
//

#include "include/Color.h"

Color::Color( uint32_t argb )
{
	const float f = 1.0f / 255.0f;
	r = f * (float) (unsigned char) (argb >> 16);
	g = f * (float) (unsigned char) (argb >>  8);
	b = f * (float) (unsigned char) (argb >>  0);
	a = f * (float) (unsigned char) (argb >> 24);
}

Color::Color( const float *pf )
{
	r = pf[0];
	g = pf[1];
	b = pf[2];
	a = pf[3];
}

Color::Color( float rIn, float gIn, float bIn, float aIn ) :
	r( rIn ),
	g( gIn ),
	b( bIn ),
	a( aIn )
{
}

Color::operator uint32_t() const
{
	uint8_t ia = (uint8_t)(a * 255.0f);
	uint8_t ir = (uint8_t)(r * 255.0f);
	uint8_t ig = (uint8_t)(g * 255.0f);
	uint8_t ib = (uint8_t)(b * 255.0f);

	return ia << 24 | ir << 16 | ig << 8 | ib;
}

Color::operator float*()
{
	return &r;
}

Color::operator const float*() const
{
	return &r;
}

Color& Color::operator+=( const Color& other )
{
	r += other.r;
	g += other.g;
	b += other.b;
	a += other.a;

	return *this;
}

Color& Color::operator-=( const Color& other )
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
	a -= other.a;

	return *this;
}

Color& Color::operator*=( float scale )
{
	r *= scale;
	g *= scale;
	b *= scale;
	a *= scale;

	return *this;
}

Color& Color::operator/=( float scale )
{
	r /= scale;
	g /= scale;
	b /= scale;
	a /= scale;

	return *this;
}

Color Color::operator+() const
{
	return *this;
}

Color Color::operator+( const Color& other ) const
{
	return Color( r + other.r, g + other.g, b + other.b, a + other.a );
}

Color Color::operator-() const
{
	return Color( -r, -g, -b, -a );
}

Color Color::operator-( const Color& other ) const
{
	return Color( r - other.r, g - other.g, b - other.b, a - other.a );
}

Color Color::operator*( float scale ) const
{
	return Color( r * scale, g * scale, b * scale, a * scale );
}

Color operator*( float scale, const Color& color )
{
	return color * scale;
}

Color Color::operator/( float scale ) const
{
	return Color( r / scale, g / scale, b / scale, a / scale );
}

bool Color::operator==( const Color& other ) const
{
	return ((r == other.r) && (g == other.g) && (b == other.b) && (a == other.a));
}

bool Color::operator!=( const Color& other ) const
{
	return ((r != other.r) || (g != other.g) || (b != other.b) || (a != other.a));
}
