////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Snorri Sturluson
// Created:		May 2013
// Copyright:	CCP 2013
//

#pragma once
#ifndef Vector4_h
#define Vector4_h

#include "xnamath.h"

struct Vector3;
struct Matrix;

struct Vector4
{
public:
	// ----------------------------------------------------------------------------------
	// Description
	//   Default constructor
	// ----------------------------------------------------------------------------------
	Vector4( void ) {}

	// ----------------------------------------------------------------------------------
	// Description
	//   Float-array constructor
	// Arguments:
	//   f - An array of 4 floats
	// ----------------------------------------------------------------------------------
	explicit Vector4( const float* f )
		:x( f[0] ),
		y( f[1] ),
		z( f[2] ),
		w( f[3] )
	{
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Float component constructor
	// Arguments:
	//   vx - The x-component value to initialize
	//   vy - The y-component value to initialize
	//   vz - The z-component value to initialize
	//   vw - The w-component value to initialize
	// ----------------------------------------------------------------------------------
	Vector4( float vx, float vy, float vz, float vw )
		:x( vx ),
		y( vy ),
		z( vz ),
		w( vw )
	{
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   XMVECTOR assignment constructor
	// Arguments:
	//   other - The XMVECTOR to copy
	// ----------------------------------------------------------------------------------
	explicit Vector4( const XMVECTOR& other )
	{
		XMStoreFloat4( (XMFLOAT4*)this, other );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Copy constructor
	// Arguments:
	//   other - The Vector4 to copy
	// ----------------------------------------------------------------------------------
	Vector4( const Vector4& other )
		:x( other.x ),
		y( other.y ),
		z( other.z ),
		w( other.w )
	{
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Vector3 assignment constructor
	// Arguments:
	//   other - The Vector3 to copy x-, y-, and z-components
	//   w - The w component to copy
	// ----------------------------------------------------------------------------------
	Vector4( const Vector3& xyz, float w );

	// ----------------------------------------------------------------------------------
	// Description
	//   Const XMVECTOR conversion operator
	// Return Value:
	//   XMVECTOR constructed from the Vector4
	// ----------------------------------------------------------------------------------
	operator XMVECTOR( void ) const 
	{
		return XMLoadFloat4( (const XMFLOAT4*)this ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   XMVECTOR assignment operator
	// Arguments:
	//   other - the XMVECTOR to assign to this Vector4
	// Return Value:
	//   Reference to this Vector4
	// ----------------------------------------------------------------------------------
	const Vector4& operator=( const XMVECTOR& other )
	{
		XMStoreFloat4( (XMFLOAT4*)this, other );
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Access to individual vector elements by index.
	// Arguments:
	//   index - element index (from 0 to 3)
	// Return Value:
	//   Reference to vector element
	// ----------------------------------------------------------------------------------
	float& operator[]( uint32_t index );
	const float& operator[]( uint32_t index ) const;

	// ----------------------------------------------------------------------------------
	// Description
	//   Addition-assignment operator
	// Arguments:
	//   other - The Vector4 to add to this Vector4
	// Return Value:
	//   This Vector4, after adding the other Vector4
	// ----------------------------------------------------------------------------------
	Vector4& operator+=( const Vector4& other )
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Subtraction-assignment operator
	// Arguments:
	//   other - The Vector4 to subtract from this Vector4
	// Return Value:
	//   This Vector4, after subtracting off the other Vector4
	// ----------------------------------------------------------------------------------
	Vector4& operator-=( const Vector4& other )
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Multiplication-assignment operator
	// Arguments:
	//   other - The Vector4 by which to multiply this Vector4 component-wise
	// Return Value:
	//   This Vector4, after multiplying by the other Vector4 component-wise
	// ----------------------------------------------------------------------------------
	Vector4& operator*=( const Vector4& other )
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Scalar multiplication-assignment operator
	// Arguments:
	//   f - The scalar by which to multiply this Vector4
	// Return Value:
	//   This Vector4, after multiplying each component by the scalar
	// ----------------------------------------------------------------------------------
	Vector4& operator*=( float f )
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Scalar division-assignment operator
	// Arguments:
	//   f - The scalar by which to divide this Vector4
	// Return Value:
	//   This Vector4, after dividing by the scalar
	// ----------------------------------------------------------------------------------
	Vector4& operator/=( float f )
	{
		const float fDiv = 1.0f / f;
		x *= fDiv;
		y *= fDiv;
		z *= fDiv;
		w *= fDiv;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Unary + operator (effectively a no-op)
	// Return Value:
	//   A copy of this Vector4
	// ----------------------------------------------------------------------------------
	Vector4 operator+( void ) const 
	{ 
		return Vector4( *this ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Unary negation operator
	// Return Value:
	//   A copy of this Vector4, with each component negated
	// ----------------------------------------------------------------------------------
	Vector4 operator-( void ) const 
	{ 
		return Vector4( -x, -y, -z, -w ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary addition operator
	// Arguments:
	//   other - The Vector4 to add to this Vector4
	// Return Value:
	//   Vector4 containing the sum of this Vector4 and the other operand
	// ----------------------------------------------------------------------------------
	const Vector4 operator+( const Vector4& other ) const
	{
		return Vector4( *this ) += other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary subtraction operator
	// Arguments:
	//   other - The Vector4 to subtract from this Vector4
	// Return Value:
	//   Vector4 containing the result of the subtraction of the other operand from this
	//   Vector4
	// ----------------------------------------------------------------------------------
	const Vector4 operator-( const Vector4& other ) const
	{
		return Vector4( *this ) -= other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary multiplication operator
	// Arguments:
	//   other - The Vector4 by which to multiply this Vector4 component-wise
	// Return Value:
	//   Vector4 containing component-wise product of this Vector4 and the other operand
	// ----------------------------------------------------------------------------------
	const Vector4 operator*( const Vector4& other ) const
	{
		return Vector4( *this ) *= other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary scalar multiplication operator
	// Arguments:
	//   f - The scalar by which to multiply this Vector4
	// Return Value:
	//   Vector4 containing product of this Vector4 and the scalar operand
	// ----------------------------------------------------------------------------------
	const Vector4 operator*( float f ) const
	{
		return Vector4( *this ) *= f;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary scalar division operator
	// Arguments:
	//   f - The scalar by which to divide this Vector4
	// Return Value:
	//   Vector4 containing this Vector4 divided by the scalar operand
	// ----------------------------------------------------------------------------------
	const Vector4 operator/( float f ) const
	{
		return Vector4( *this ) /= f;
	}

	// Declare friend operator
	friend const Vector4 operator*( float f, const Vector4& other );

	// ----------------------------------------------------------------------------------
	// Description
	//   Equality comparison operator
	// Arguments:
	//   other - The Vector4 with which to compare for equality
	// Return Value:
	//   true, if the two Vector4's are component-wise equal
	//   false, if the two Vector4's are not component-wise equal
	// ----------------------------------------------------------------------------------
	bool operator==( const Vector4& other )
	{
		return ( x == other.x && y == other.y && z == other.z && w == other.w );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Inequality comparison operator
	// Arguments:
	//   other - The Vector4 with which to compare for inequality
	// Return Value:
	//   true, if the two Vector4's are not component-wise equal
	//   false, if the two Vector4's are component-wise equal
	// ----------------------------------------------------------------------------------
	bool operator!=( const Vector4& other )
	{
		return ( x != other.x || y != other.y || z != other.z || w != other.w );
	}

	// ----------------------------------------------------------------------------------
	const Vector3& GetXYZ() const
	{
		return *reinterpret_cast<const Vector3*>( &x );
	}

	// ----------------------------------------------------------------------------------
	Vector3& GetXYZ()
	{
		return *reinterpret_cast<Vector3*>( &x );
	}

	Vector4 operator*( const Matrix& m );
public:
	float x, y, z, w;
};

namespace CcpMath
{

float Vec4Dot( const Vector4& v1, const Vector4& v2 );

Vector4& Vec4Add( Vector4& out, const Vector4& v1, const Vector4& v2);
Vector4 Vec4Add( const Vector4& v1, const Vector4& v2);

Vector4& Vec4Scale( Vector4& out, const Vector4& v, float s);
Vector4 Vec4Scale( const Vector4& v, float s);

Vector4& Vec4Transform( Vector4& out, const Vector4& v, const Matrix& m );
Vector4 Vec4Transform( const Vector4& v, const Matrix& m );

}

// Not used in trinity - skipping
float D3DXVec4Length
	( const Vector4 *pV );

// Not used in trinity - skipping
float D3DXVec4LengthSq
	( const Vector4 *pV );

float D3DXVec4Dot
	( const Vector4 *pV1, const Vector4 *pV2 );

Vector4* D3DXVec4Add
	( Vector4 *pOut, const Vector4 *pV1, const Vector4 *pV2);

// Not used in trinity - skipping
Vector4* D3DXVec4Subtract
	( Vector4 *pOut, const Vector4 *pV1, const Vector4 *pV2);

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
// Not used in trinity - skipping
Vector4* D3DXVec4Minimize
	( Vector4 *pOut, const Vector4 *pV1, const Vector4 *pV2);

// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
// Not used in trinity - skipping
Vector4* D3DXVec4Maximize
	( Vector4 *pOut, const Vector4 *pV1, const Vector4 *pV2);

Vector4* D3DXVec4Scale
	( Vector4 *pOut, const Vector4 *pV, float s);

// Linear interpolation. V1 + s(V2-V1)
// Not used in trinity - skipping
Vector4* D3DXVec4Lerp
	( Vector4 *pOut, const Vector4 *pV1, const Vector4 *pV2,
	float s );

// Cross-product in 4 dimensions.
// Not used in trinity - skipping
Vector4* D3DXVec4Cross
	( Vector4 *pOut, const Vector4 *pV1, const Vector4 *pV2,
	const Vector4 *pV3);

// Not used in trinity - skipping
Vector4* D3DXVec4Normalize
	( Vector4 *pOut, const Vector4 *pV );

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
// Not used in trinity - skipping
Vector4* D3DXVec4Hermite
	( Vector4 *pOut, const Vector4 *pV1, const Vector4 *pT1,
	const Vector4 *pV2, const Vector4 *pT2, float s );

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
// Not used in trinity - skipping
Vector4* D3DXVec4CatmullRom
	( Vector4 *pOut, const Vector4 *pV0, const Vector4 *pV1,
	const Vector4 *pV2, const Vector4 *pV3, float s );

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
// Not used in trinity - skipping
Vector4* D3DXVec4BaryCentric
	( Vector4 *pOut, const Vector4 *pV1, const Vector4 *pV2,
	const Vector4 *pV3, float f, float g);

// Transform vector by matrix.
Vector4* D3DXVec4Transform
	( Vector4 *pOut, const Vector4 *pV, const Matrix *pM );

// Transform vector array by matrix.
Vector4* D3DXVec4TransformArray
	( Vector4 *pOut, uint32_t OutStride, const Vector4 *pV, uint32_t VStride, const Matrix *pM, uint32_t n );

#endif // Vector4_h
