////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Snorri Sturluson
// Created:		May 2013
// Copyright:	CCP 2013
//

#pragma once
#ifndef Vector2_h
#define Vector2_h

#include "xnamath.h"

struct Vector4;
struct Matrix;

struct Vector2
{
public:
	// ----------------------------------------------------------------------------------
	// Description
	//   Default constructor
	// ----------------------------------------------------------------------------------
	Vector2( void ) {}

	// ----------------------------------------------------------------------------------
	// Description
	//   Float-array constructor
	// Arguments:
	//   f - An array of 2 floats
	// ----------------------------------------------------------------------------------
	explicit Vector2( const float* f )
		:x( f[0] ),
		y( f[1] )
	{
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Float component constructor
	// Arguments:
	//   x - The x-component value to initialize
	//   y - The y-component value to initialize
	// ----------------------------------------------------------------------------------
	Vector2( float vx, float vy )
		:x( vx ),
		y( vy )
	{
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   XMVECTOR assignment constructor
	// Arguments:
	//   other - The XMVECTOR to copy
	// ----------------------------------------------------------------------------------
	explicit Vector2( const XMVECTOR& other )
	{
		XMStoreFloat2( (XMFLOAT2*)this, other );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Copy constructor
	// Arguments:
	//   other - The Vector2 to copy
	// ----------------------------------------------------------------------------------
	Vector2( const Vector2& other )
		:x( other.x ),
		y( other.y )
	{
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Float-array conversion operator
	// Return Value:
	//   Pointer to the x-component of the vector
	// ----------------------------------------------------------------------------------
	operator float*( void ) 
	{ 
		return &x; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Const float-array conversion operator
	// Return Value:
	//   Pointer to the x-component of the vector
	// ----------------------------------------------------------------------------------
	operator const float*( void ) const 
	{ 
		return &x; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Const XMVECTOR conversion operator
	// Return Value:
	//   XMVECTOR constructed from the Vector2 (z- and w-components uninitialized)
	// ----------------------------------------------------------------------------------
	operator const XMVECTOR( void ) const 
	{ 
		return XMLoadFloat2( (const XMFLOAT2*)this ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   XMVECTOR assignment operator
	// Arguments:
	//   other - the XMVECTOR to assign to this Vector2
	// Return Value:
	//   Reference to this Vector2
	// ----------------------------------------------------------------------------------
	const Vector2& operator=( const XMVECTOR& other )
	{
		XMStoreFloat2( (XMFLOAT2*)this, other );
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Addition-assignment operator
	// Arguments:
	//   other - The Vector2 to add to this Vector2
	// Return Value:
	//   This Vector2, after adding the other Vector2
	// ----------------------------------------------------------------------------------
	Vector2& operator+=( const Vector2& other )
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Subtraction-assignment operator
	// Arguments:
	//   other - The Vector2 to subtract from this Vector2
	// Return Value:
	//   This Vector2, after subtracting off the other Vector2
	// ----------------------------------------------------------------------------------
	Vector2& operator-=( const Vector2& other )
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Multiplication-assignment operator
	// Arguments:
	//   other - The Vector2 by which to multiply this Vector2 component-wise
	// Return Value:
	//   This Vector2, after multiplying by the other Vector2 component-wise
	// ----------------------------------------------------------------------------------
	Vector2& operator*=( const Vector2& other )
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Division-assignment operator
	// Arguments:
	//   other - The Vector2 by which to divide this Vector2 component-wise
	// Return Value:
	//   This Vector2, after dividing by the other Vector2 component-wise
	// ----------------------------------------------------------------------------------
	Vector2& operator/=( const Vector2& other )
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Scalar multiplication-assignment operator
	// Arguments:
	//   f - The scalar by which to multiply this Vector2
	// Return Value:
	//   This Vector2, after multiplying each component by the scalar
	// ----------------------------------------------------------------------------------
	Vector2& operator*=( float f )
	{
		x *= f;
		y *= f;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Scalar division-assignment operator
	// Arguments:
	//   f - The scalar by which to divide this Vector2
	// Return Value:
	//   This Vector2, after dividing by the scalar
	// ----------------------------------------------------------------------------------
	Vector2& operator/=( float f )
	{
		const float fDiv = 1.0f / f;
		x *= fDiv;
		y *= fDiv;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Unary + operator (effectively a no-op)
	// Return Value:
	//   A copy of this Vector2
	// ----------------------------------------------------------------------------------
	Vector2 operator+( void ) const 
	{
		return Vector2( *this ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Unary negation operator
	// Return Value:
	//   A copy of this Vector2, with each component negated
	// ----------------------------------------------------------------------------------
	Vector2 operator-( void ) const 
	{ 
		return Vector2( -x, -y ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary addition operator
	// Arguments:
	//   other - The Vector2 to add to this Vector2
	// Return Value:
	//   Vector2 containing the sum of this Vector2 and the other operand
	// ----------------------------------------------------------------------------------
	const Vector2 operator+( const Vector2& other ) const
	{
		return Vector2( *this ) += other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary subtraction operator
	// Arguments:
	//   other - The Vector2 to subtract from this Vector2
	// Return Value:
	//   Vector2 containing the result of the subtraction of the other operand from this
	//   Vector2
	// ----------------------------------------------------------------------------------
	const Vector2 operator-( const Vector2& other ) const
	{
		return Vector2( *this ) -= other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary multiplication operator
	// Arguments:
	//   other - The Vector2 by which to multiply this Vector2 component-wise
	// Return Value:
	//   Vector2 containing component-wise product of this Vector2 and the other operand
	// ----------------------------------------------------------------------------------
	const Vector2 operator*( const Vector2& other ) const
	{
		return Vector2( *this ) *= other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary division operator
	// Arguments:
	//   other - The Vector2 by which to divide this Vector2 component-wise
	// Return Value:
	//   Vector2 containing component-wise division of this Vector2 and the other operand
	// ----------------------------------------------------------------------------------
	const Vector2 operator/( const Vector2& other ) const
	{
		return Vector2( *this ) /= other;
	}


	// ----------------------------------------------------------------------------------
	// Description
	//   Binary scalar multiplication operator
	// Arguments:
	//   f - The scalar by which to multiply this Vector2
	// Return Value:
	//   Vector2 containing product of this Vector2 and the scalar operand
	// ----------------------------------------------------------------------------------
	const Vector2 operator*( float f ) const
	{
		return Vector2( *this ) *= f;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary scalar division operator
	// Arguments:
	//   f - The scalar by which to divide this Vector2
	// Return Value:
	//   Vector2 containing this Vector2 divided by the scalar operand
	// ----------------------------------------------------------------------------------
	const Vector2 operator/( float f ) const
	{
		return Vector2( *this ) /= f;
	}

	// Declare friend operator
	friend const Vector2 operator*( float f, const Vector2& other );

	// ----------------------------------------------------------------------------------
	// Description
	//   Equality comparison operator
	// Arguments:
	//   other - The Vector2 with which to compare for equality
	// Return Value:
	//   true, if the two Vector2's are component-wise equal
	//   false, if the two Vector2's are not component-wise equal
	// ----------------------------------------------------------------------------------
	bool operator==( const Vector2& other )
	{
		return ( x == other.x && y == other.y );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Inequality comparison operator
	// Arguments:
	//   other - The Vector2 with which to compare for inequality
	// Return Value:
	//   true, if the two Vector2's are not component-wise equal
	//   false, if the two Vector2's are component-wise equal
	// ----------------------------------------------------------------------------------
	bool operator!=( const Vector2& other )
	{
		return ( x != other.x || y != other.y );
	}

public:
	float x, y;
};

namespace CcpMath
{

float Vec2Length( const Vector2& v );

float Vec2LengthSq( const Vector2& v );

float Vec2Dot( const Vector2& v1, const Vector2& v2 );

// Z component of ((x1,y1,0) cross (x2,y2,0))
float Vec2CCW( const Vector2& v1, const Vector2& v2 );

Vector2& Vec2Scale( Vector2& out, const Vector2& v, float s );
Vector2 Vec2Scale( const Vector2& v, float s );

Vector2& Vec2Normalize( Vector2& out, const Vector2& v );
Vector2 Vec2Normalize( const Vector2& v );

Vector4& Vec2Transform( Vector4& out, const Vector2& v, const Matrix& m );
Vector4 Vec2Transform( const Vector2& v, const Matrix& m );

}

float D3DXVec2Length( const Vector2 *pV );
float D3DXVec2LengthSq( const Vector2 *pV );
float D3DXVec2Dot( const Vector2 *pV1, const Vector2 *pV2 );
float D3DXVec2CCW( const Vector2 *pV1, const Vector2 *pV2 );

// Not used in trinity - skipping
Vector2* D3DXVec2Add
	( Vector2 *pOut, const Vector2 *pV1, const Vector2 *pV2 );

// Not used in trinity - skipping
Vector2* D3DXVec2Subtract
	( Vector2 *pOut, const Vector2 *pV1, const Vector2 *pV2 );

// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
// Not used in trinity - skipping
Vector2* D3DXVec2Minimize
	( Vector2 *pOut, const Vector2 *pV1, const Vector2 *pV2 );

// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
// Not used in trinity - skipping
Vector2* D3DXVec2Maximize
	( Vector2 *pOut, const Vector2 *pV1, const Vector2 *pV2 );

Vector2* D3DXVec2Scale( Vector2 *pOut, const Vector2 *pV, float s );

// Linear interpolation. V1 + s(V2-V1)
// Not used in trinity - skipping
Vector2* D3DXVec2Lerp
	( Vector2 *pOut, const Vector2 *pV1, const Vector2 *pV2,
	float s );

Vector2* D3DXVec2Normalize
	( Vector2 *pOut, const Vector2 *pV );

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
// Not used in trinity - skipping
Vector2* D3DXVec2Hermite
	( Vector2 *pOut, const Vector2 *pV1, const Vector2 *pT1,
	const Vector2 *pV2, const Vector2 *pT2, float s );

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
// Not used in trinity - skipping
Vector2* D3DXVec2CatmullRom
	( Vector2 *pOut, const Vector2 *pV0, const Vector2 *pV1,
	const Vector2 *pV2, const Vector2 *pV3, float s );

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
// Not used in trinity - skipping
Vector2* D3DXVec2BaryCentric
	( Vector2 *pOut, const Vector2 *pV1, const Vector2 *pV2,
	const Vector2 *pV3, float f, float g);

// Transform (x, y, 0, 1) by matrix.
// Not used in trinity - skipping
Vector4* D3DXVec2Transform
	( Vector4 *pOut, const Vector2 *pV, const Matrix *pM );

// Transform (x, y, 0, 1) by matrix, project result back into w=1.
// Not used in trinity - skipping
Vector2* D3DXVec2TransformCoord
	( Vector2 *pOut, const Vector2 *pV, const Matrix *pM );

// Transform (x, y, 0, 0) by matrix.
// Not used in trinity - skipping
Vector2* D3DXVec2TransformNormal
	( Vector2 *pOut, const Vector2 *pV, const Matrix *pM );

// Transform Array (x, y, 0, 1) by matrix.
// Not used in trinity - skipping
Vector4* D3DXVec2TransformArray
	( Vector4 *pOut, uint32_t OutStride, const Vector2 *pV, uint32_t VStride, const Matrix *pM, uint32_t n);

// Transform Array (x, y, 0, 1) by matrix, project result back into w=1.
// Not used in trinity - skipping
Vector2* D3DXVec2TransformCoordArray
	( Vector2 *pOut, uint32_t OutStride, const Vector2 *pV, uint32_t VStride, const Matrix *pM, uint32_t n );

// Transform Array (x, y, 0, 0) by matrix.
// Not used in trinity - skipping
Vector2* D3DXVec2TransformNormalArray
	( Vector2 *pOut, uint32_t OutStride, const Vector2 *pV, uint32_t VStride, const Matrix *pM, uint32_t n );

#endif // Vector2_h
