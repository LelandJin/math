////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Snorri Sturluson
// Created:		May 2013
// Copyright:	CCP 2013
//

#pragma once
#ifndef Vector3_h
#define Vector3_h

#include "xnamath.h"

struct Vector3
{
public:
	// ----------------------------------------------------------------------------------
	// Description
	//   Default constructor
	// ----------------------------------------------------------------------------------
	Vector3( void ) {}

	// ----------------------------------------------------------------------------------
	// Description
	//   Float-array constructor
	// Arguments:
	//   f - An array of 3 floats
	// ----------------------------------------------------------------------------------
	explicit Vector3( const float* f );

	// ----------------------------------------------------------------------------------
	// Description
	//   Float component constructor
	// Arguments:
	//   x - The x-component value to initialize
	//   y - The y-component value to initialize
	//   z - The z-component value to initialize
	// ----------------------------------------------------------------------------------
	Vector3( float x, float y, float z );

	// ----------------------------------------------------------------------------------
	// Description
	//   XMVECTOR assignment constructor
	// Arguments:
	//   other - The XMVECTOR to copy
	// ----------------------------------------------------------------------------------
	explicit Vector3( const XMVECTOR& other )
	{
		XMStoreFloat3( (XMFLOAT3*)this, other );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Copy constructor
	// Arguments:
	//   other - The Vector3 to copy
	// ----------------------------------------------------------------------------------
	Vector3( const Vector3& other );

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
	//   XMVECTOR constructed from the Vector3 (w-component uninitialized)
	// ----------------------------------------------------------------------------------
	operator XMVECTOR( void ) const 
	{
		return XMLoadFloat3( (const XMFLOAT3*)this ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   XMVECTOR assignment operator
	// Arguments:
	//   other - the XMVECTOR to assign to this Vector3
	// Return Value:
	//   Reference to this Vector3
	// ----------------------------------------------------------------------------------
	const Vector3& operator=( const XMVECTOR& other )
	{
		XMStoreFloat3( (XMFLOAT3*)this, other );
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Addition-assignment operator
	// Arguments:
	//   other - The Vector3 to add to this Vector3
	// Return Value:
	//   This Vector3, after adding the other Vector3
	// ----------------------------------------------------------------------------------
	Vector3& operator+=( const Vector3& other )
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Subtraction-assignment operator
	// Arguments:
	//   other - The Vector3 to subtract from this Vector3
	// Return Value:
	//   This Vector3, after subtracting off the other Vector3
	// ----------------------------------------------------------------------------------
	Vector3& operator-=( const Vector3& other )
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Multiplication-assignment operator
	// Arguments:
	//   other - The Vector3 by which to multiply this Vector3 component-wise
	// Return Value:
	//   This Vector3, after multiplying by the other Vector3 component-wise
	// ----------------------------------------------------------------------------------
	Vector3& operator*=( const Vector3& other )
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Scalar multiplication-assignment operator
	// Arguments:
	//   f - The scalar by which to multiply this Vector3
	// Return Value:
	//   This Vector3, after multiplying each component by the scalar
	// ----------------------------------------------------------------------------------
	Vector3& operator*=( float f )
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Scalar division-assignment operator
	// Arguments:
	//   f - The scalar by which to divide this Vector3
	// Return Value:
	//   This Vector3, after dividing by the scalar
	// ----------------------------------------------------------------------------------
	Vector3& operator/=( float f )
	{
		const float fDiv = 1.0f / f;
		x *= fDiv;
		y *= fDiv;
		z *= fDiv;
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Unary + operator (effectively a no-op)
	// Return Value:
	//   A copy of this Vector3
	// ----------------------------------------------------------------------------------
	Vector3 operator+( void ) const 
	{ 
		return Vector3( *this ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Unary negation operator
	// Return Value:
	//   A copy of this Vector3, with each component negated
	// ----------------------------------------------------------------------------------
	Vector3 operator-( void ) const 
	{ 
		return Vector3( -x, -y, -z ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary addition operator
	// Arguments:
	//   other - The Vector3 to add to this Vector3
	// Return Value:
	//   Vector3 containing the sum of this Vector3 and the other operand
	// ----------------------------------------------------------------------------------
	const Vector3 operator+( const Vector3& other ) const
	{
		return Vector3( *this ) += other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary subtraction operator
	// Arguments:
	//   other - The Vector3 to subtract from this Vector3
	// Return Value:
	//   Vector3 containing the result of the subtraction of the other operand from this
	//   Vector3
	// ----------------------------------------------------------------------------------
	const Vector3 operator-( const Vector3& other ) const
	{
		return Vector3( *this ) -= other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary multiplication operator
	// Arguments:
	//   other - The Vector3 by which to multiply this Vector3 component-wise
	// Return Value:
	//   Vector3 containing component-wise product of this Vector3 and the other operand
	// ----------------------------------------------------------------------------------
	const Vector3 operator*( const Vector3& other ) const
	{
		return Vector3( *this ) *= other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary scalar multiplication operator
	// Arguments:
	//   f - The scalar by which to multiply this Vector3
	// Return Value:
	//   Vector3 containing product of this Vector3 and the scalar operand
	// ----------------------------------------------------------------------------------
	const Vector3 operator*( float f ) const
	{
		return Vector3( *this ) *= f;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary scalar division operator
	// Arguments:
	//   f - The scalar by which to divide this Vector3
	// Return Value:
	//   Vector3 containing this Vector3 divided by the scalar operand
	// ----------------------------------------------------------------------------------
	const Vector3 operator/( float f ) const
	{
		return Vector3( *this ) /= f;
	}

	// Declare friend operator
	friend const Vector3 operator*( float f, const Vector3& other );

	// ----------------------------------------------------------------------------------
	// Description
	//   Equality comparison operator
	// Arguments:
	//   other - The Vector3 with which to compare for equality
	// Return Value:
	//   true, if the two Vector3's are component-wise equal
	//   false, if the two Vector3's are not component-wise equal
	// ----------------------------------------------------------------------------------
	bool operator==( const Vector3& other )
	{
		return ( x == other.x && y == other.y && z == other.z );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Inequality comparison operator
	// Arguments:
	//   other - The Vector3 with which to compare for inequality
	// Return Value:
	//   true, if the two Vector3's are not component-wise equal
	//   false, if the two Vector3's are component-wise equal
	// ----------------------------------------------------------------------------------
	bool operator!=( const Vector3& other )
	{
		return ( x != other.x || y != other.y || z != other.z );
	}

public:
	float x, y, z;
};

struct Vector4;
struct Matrix;

namespace CcpMath
{
float Vec3Length( const Vector3& v );

float Vec3LengthSq( const Vector3& v );

float Vec3Dot( const Vector3& v1, const Vector3& v2 );

Vector3& Vec3Cross( Vector3& out, const Vector3& v1, const Vector3& v2 );
Vector3 Vec3Cross( const Vector3& v1, const Vector3& v2 );

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
Vector3& Vec3Minimize( Vector3& out, const Vector3& v1, const Vector3& v2 );
Vector3 Vec3Minimize( const Vector3& v1, const Vector3& v2 );

// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
Vector3& Vec3Maximize( Vector3& out, const Vector3& v1, const Vector3& v2 );
Vector3 Vec3Maximize( const Vector3& v1, const Vector3& v2 );

// Linear interpolation. V1 + s(V2-V1)
Vector3& Vec3Lerp( Vector3& out, const Vector3& v1, const Vector3& v2, float s );
Vector3 Vec3Lerp( const Vector3& v1, const Vector3& v2, float s );

Vector3& Vec3Normalize( Vector3& out, const Vector3& v );
Vector3 Vec3Normalize( const Vector3& v );

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
Vector3& Vec3Hermite( Vector3& out, const Vector3& v1, const Vector3& t1, const Vector3& v2, const Vector3& t2, float s );
Vector3 Vec3Hermite( const Vector3& v1, const Vector3& t1, const Vector3& v2, const Vector3& t2, float s );

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
Vector3& Vec3CatmullRom( Vector3& out, const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, float s );
Vector3 Vec3CatmullRom( const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, float s );

Vector4& Vec3Transform( Vector4& out, const Vector3& v, const Matrix& m );
Vector4 Vec3Transform( const Vector3& v, const Matrix& m );

Vector3& Vec3TransformCoord( Vector3& out, const Vector3& v, const Matrix& m );
Vector3 Vec3TransformCoord( const Vector3& v, const Matrix& m );

Vector3& Vec3TransformNormal( Vector3& out, const Vector3& v, const Matrix& m );
Vector3 Vec3TransformNormal( const Vector3& v, const Matrix& m );

void Vec3TransformCoordArray( 
	Vector3* out, 
	uint32_t outStride, 
	const Vector3* in, 
	uint32_t inStride, 
	const Matrix& m, 
	uint32_t count );

bool SphereBoundProbe(
	const Vector3& center,
	float radius,
	const Vector3& rayPosition,
	const Vector3& rayDirection );

void ComputeBoundingSphere(
    const Vector3* firstPosition,
    uint32_t numVertices, 
    uint32_t stride,
    Vector3& center, 
    float& radius );

}

float D3DXVec3Length( const Vector3 *pV );
float D3DXVec3LengthSq( const Vector3 *pV );
float D3DXVec3Dot( const Vector3 *pV1, const Vector3 *pV2 );
Vector3* D3DXVec3Cross( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2 );
Vector3* D3DXVec3Add( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2 );
Vector3* D3DXVec3Subtract( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2 );
Vector3* D3DXVec3Minimize( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2 );
Vector3* D3DXVec3Maximize( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2 );
Vector3* D3DXVec3Scale( Vector3 *pOut, const Vector3 *pV, float s);
Vector3* D3DXVec3Lerp( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2, float s );
Vector3* D3DXVec3Normalize( Vector3 *pOut, const Vector3 *pV );
Vector3* D3DXVec3Hermite( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pT1, const Vector3 *pV2, const Vector3 *pT2, float s );
Vector3* D3DXVec3CatmullRom( Vector3 *pOut, const Vector3 *pV0, const Vector3 *pV1,	const Vector3 *pV2, const Vector3 *pV3, float s );

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
// Not used in trinity - skipping
Vector3* D3DXVec3BaryCentric
	( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2,
	const Vector3 *pV3, float f, float g);

// Transform (x, y, z, 1) by matrix.
Vector4* D3DXVec3Transform
	( Vector4 *pOut, const Vector3 *pV, const Matrix *pM );

// Transform (x, y, z, 1) by matrix, project result back into w=1.
Vector3* D3DXVec3TransformCoord
	( Vector3 *pOut, const Vector3 *pV, const Matrix *pM );

// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
// non-affine matrix, the matrix you pass to this function should be the 
// transpose of the inverse of the matrix you would use to transform a coord.
Vector3* D3DXVec3TransformNormal
	( Vector3 *pOut, const Vector3 *pV, const Matrix *pM );


// Transform Array (x, y, z, 1) by matrix. 
// Not used in trinity - skipping
Vector4* D3DXVec3TransformArray
	( Vector4 *pOut, uint32_t OutStride, const Vector3 *pV, uint32_t VStride, const Matrix *pM, uint32_t n );

// Transform Array (x, y, z, 1) by matrix, project result back into w=1.
// Not used in trinity - skipping
Vector3* D3DXVec3TransformCoordArray
	( Vector3 *pOut, uint32_t OutStride, const Vector3 *pV, uint32_t VStride, const Matrix *pM, uint32_t n );

// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
// non-affine matrix, the matrix you pass to this function should be the 
// transpose of the inverse of the matrix you would use to transform a coord.
// Not used in trinity - skipping
Vector3* D3DXVec3TransformNormalArray
	( Vector3 *pOut, uint32_t OutStride, const Vector3 *pV, uint32_t VStride, const Matrix *pM, uint32_t n );

bool D3DXSphereBoundProbe(
	const Vector3* pCenter,
	float Radius,
	const Vector3* pRayPosition,
	const Vector3* pRayDirection );

void D3DXComputeBoundingSphere(
    const Vector3* pFirstPosition,
    uint32_t NumVertices, 
    uint32_t dwStride,
    Vector3* pCenter, 
    float* pRadius );

bool D3DXIntersectTri( 
	const Vector3* p0, 
	const Vector3* p1, 
	const Vector3* p2, 
	const Vector3* rayPos, 
	const Vector3* rayDir, 
	float *u, 
	float *v, 
	float *dist );

#endif // Vector3_h
