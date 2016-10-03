////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Filipp Pavlov
// Created:		June 2013
// Copyright:	CCP 2013
//

#pragma once
#ifndef Float16_H
#define Float16_H

#include <cstdint>
#include <cstddef>

namespace CcpMath
{

class Float16
{
public:
    Float16() {};
    Float16( float value );

    operator float () const;

	uint16_t GetUint16Value() const;

    bool operator == ( const Float16& other ) const;
    bool operator != ( const Float16& other ) const;
protected:
    uint16_t m_value;
};

struct Vector2_16
{
    Vector2_16() {};
    Vector2_16( const float* coords )
		:x( coords[0] ),
		y( coords[1] )
	{
	}

    Vector2_16( const Float16* coords )
		:x( coords[0] ),
		y( coords[1] )
	{
	}

    Vector2_16( const Float16 &x_, const Float16 &y_ )
		:x( x_ ),
		y( y_ )
	{
	}

    bool operator == ( const Vector2_16& other ) const
	{
		return x == other.x && y == other.y;
	}

    bool operator != ( const Vector2_16& other ) const
	{
		return x != other.x || y != other.y;
	}

    Float16 x, y;

};


float* Float16To32Array( float* output, const Float16* input, size_t count );
Float16* Float32To16Array( Float16* output, const float* input, size_t count );

}

typedef CcpMath::Float16 D3DXFLOAT16;
typedef CcpMath::Vector2_16 D3DXVECTOR2_16F;

float* D3DXFloat16To32Array( float* pOut, const D3DXFLOAT16 *pIn, uint32_t n );
D3DXFLOAT16* D3DXFloat32To16Array( D3DXFLOAT16* pOut, const float *pIn, uint32_t n );

#endif