////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Snorri Sturluson
// Created:		May 2013
// Copyright:	CCP 2013
//

#pragma once
#ifndef Color_h
#define Color_h

#include <cstdint>

struct Color
{
public:
	Color() {}
	Color( uint32_t argb );
	Color( const float * );
	Color( float r, float g, float b, float a );

	// casting
	operator uint32_t () const;

	operator float* ();
	operator const float* () const;

	// assignment operators
	Color& operator += ( const Color& );
	Color& operator -= ( const Color& );
	Color& operator *= ( float );
	Color& operator /= ( float );

	// unary operators
	Color operator + () const;
	Color operator - () const;

	// binary operators
	Color operator + ( const Color& ) const;
	Color operator - ( const Color& ) const;
	Color operator * ( float ) const;
	Color operator / ( float ) const;

	friend Color operator * ( float, const Color& );

	bool operator == ( const Color& ) const;
	bool operator != ( const Color& ) const;

	float r, g, b, a;
};

inline Color* D3DXColorNegative
	(Color *pOut, const Color *pC)
{
#ifdef D3DX_DEBUG
	if(!pOut || !pC)
		return NULL;
#endif

	pOut->r = 1.0f - pC->r;
	pOut->g = 1.0f - pC->g;
	pOut->b = 1.0f - pC->b;
	pOut->a = pC->a;
	return pOut;
}

inline Color* D3DXColorAdd
	(Color *pOut, const Color *pC1, const Color *pC2)
{
#ifdef D3DX_DEBUG
	if(!pOut || !pC1 || !pC2)
		return NULL;
#endif

	pOut->r = pC1->r + pC2->r;
	pOut->g = pC1->g + pC2->g;
	pOut->b = pC1->b + pC2->b;
	pOut->a = pC1->a + pC2->a;
	return pOut;
}

inline Color* D3DXColorSubtract
	(Color *pOut, const Color *pC1, const Color *pC2)
{
#ifdef D3DX_DEBUG
	if(!pOut || !pC1 || !pC2)
		return NULL;
#endif

	pOut->r = pC1->r - pC2->r;
	pOut->g = pC1->g - pC2->g;
	pOut->b = pC1->b - pC2->b;
	pOut->a = pC1->a - pC2->a;
	return pOut;
}

inline Color* D3DXColorScale
	(Color *pOut, const Color *pC, float s)
{
#ifdef D3DX_DEBUG
	if(!pOut || !pC)
		return NULL;
#endif

	pOut->r = pC->r * s;
	pOut->g = pC->g * s;
	pOut->b = pC->b * s;
	pOut->a = pC->a * s;
	return pOut;
}

inline Color* D3DXColorModulate
	(Color *pOut, const Color *pC1, const Color *pC2)
{
#ifdef D3DX_DEBUG
	if(!pOut || !pC1 || !pC2)
		return NULL;
#endif

	pOut->r = pC1->r * pC2->r;
	pOut->g = pC1->g * pC2->g;
	pOut->b = pC1->b * pC2->b;
	pOut->a = pC1->a * pC2->a;
	return pOut;
}

inline Color* D3DXColorLerp
	(Color *pOut, const Color *pC1, const Color *pC2, float s)
{
#ifdef D3DX_DEBUG
	if(!pOut || !pC1 || !pC2)
		return NULL;
#endif

	pOut->r = pC1->r + s * (pC2->r - pC1->r);
	pOut->g = pC1->g + s * (pC2->g - pC1->g);
	pOut->b = pC1->b + s * (pC2->b - pC1->b);
	pOut->a = pC1->a + s * (pC2->a - pC1->a);
	return pOut;
}

inline Color* D3DXColorAdjustContrast( Color* out, const Color* color, float contrast )
{
	out->r = 0.5f + contrast * ( color->r - 0.5f );
	out->g = 0.5f + contrast * ( color->g - 0.5f );
	out->b = 0.5f + contrast * ( color->b - 0.5f );
	out->a = color->a;
	return out;
}

inline Color* D3DXColorAdjustSaturation( Color* out, const Color* color, float saturation )
{
    float grey = color->r * 0.2125f + color->g * 0.7154f + color->b * 0.0721f;
    out->r = grey + saturation * ( color->r - grey );
    out->g = grey + saturation * ( color->g - grey );
    out->b = grey + saturation * ( color->b - grey );
    out->a = color->a;
    return out;
}
#endif // Color_h