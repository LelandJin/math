////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Snorri Sturluson
// Created:		May 2013
// Copyright:	CCP 2013
//

#pragma once
#ifndef Quaternion_h
#define Quaternion_h

struct Quaternion;
struct Vector3;
struct Matrix;

#include "xnamath.h"

struct Quaternion
{
public:
	// ----------------------------------------------------------------------------------
	// Description
	//   Default constructor
	// ----------------------------------------------------------------------------------
	Quaternion();

	// ----------------------------------------------------------------------------------
	// Description
	//   Float-array constructor
	// Arguments:
	//   f - An array of 4 floats
	// ----------------------------------------------------------------------------------
	Quaternion( const float* f );

	// ----------------------------------------------------------------------------------
	// Description
	//   Float component constructor
	// Arguments:
	//   x - The x-component value to initialize
	//   y - The y-component value to initialize
	//   z - The z-component value to initialize
	//   w - The w-component value to initialize
	// ----------------------------------------------------------------------------------
	Quaternion( float x, float y, float z, float w );

	// ----------------------------------------------------------------------------------
	// Description
	//   Quaternion assignment constructor
	// Arguments:
	//   other - The Quaternion to copy
	// ----------------------------------------------------------------------------------
	Quaternion( const Quaternion& other );

	// ----------------------------------------------------------------------------------
	// Description
	//   XMVECTOR assignment constructor
	// Arguments:
	//   other - The XMVECTOR to copy
	// ----------------------------------------------------------------------------------
	explicit Quaternion( const XMVECTOR& other )
	{
		XMStoreFloat4( (XMFLOAT4*)this, other );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Float-array conversion operator
	// Return Value:
	//   Pointer to the x-component of the Quaternion
	// ----------------------------------------------------------------------------------
	operator float*( void ) 
	{ 
		return &x; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Const float-array conversion operator
	// Return Value:
	//   Pointer to the x-component of the Quaternion
	// ----------------------------------------------------------------------------------
	operator const float*( void ) const 
	{ 
		return &x; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Const XMVECTOR conversion operator
	// Return Value:
	//   XMVECTOR constructed from the Quaternion
	// ----------------------------------------------------------------------------------
	operator const XMVECTOR( void ) const 
	{
		return XMLoadFloat4( (const XMFLOAT4*)this ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   XMVECTOR assignment operator
	// Arguments:
	//   other - the XMVECTOR to assign to this Quaternion
	// Return Value:
	//   Reference to this Quaternion
	// ----------------------------------------------------------------------------------
	const Quaternion& operator=( const XMVECTOR& other )
	{
		XMStoreFloat4( (XMFLOAT4*)this, other );
		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Addition-assignment operator
	// Arguments:
	//   other - The Quaternion to add to this Quaternion
	// Return Value:
	//   This Quaternion, after adding the other Quaternion
	// ----------------------------------------------------------------------------------
	Quaternion& operator+=( const Quaternion& other )
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
	//   other - The Quaternion to subtract from this Quaternion
	// Return Value:
	//   This Quaternion, after subtracting off the other Quaternion
	// ----------------------------------------------------------------------------------
	Quaternion& operator-=( const Quaternion& other )
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
	//   other - The Quaternion by which to multiply this Quaternion
	// Return Value:
	//   This Quaternion, after multiplying by the other Quaternion
	// ----------------------------------------------------------------------------------
	Quaternion& operator*=( const Quaternion& other );

	// ----------------------------------------------------------------------------------
	// Description
	//   Scalar multiplication-assignment operator
	// Arguments:
	//   f - The scalar by which to multiply this Quaternion
	// Return Value:
	//   This Quaternion, after multiplying each component by the scalar
	// ----------------------------------------------------------------------------------
	Quaternion& operator*=( float f )
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
	//   f - The scalar by which to divide this Quaternion
	// Return Value:
	//   This Quaternion, after dividing by the scalar
	// ----------------------------------------------------------------------------------
	Quaternion& operator/=( float f )
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
	//   A copy of this Quaternion
	// ----------------------------------------------------------------------------------
	Quaternion operator+( void ) const 
	{ 
		return Quaternion( *this ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Unary negation operator
	// Return Value:
	//   A copy of this Quaternion, with each component negated
	// ----------------------------------------------------------------------------------
	Quaternion operator-( void ) const 
	{ 
		return Quaternion( -x, -y, -z, -w ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary addition operator
	// Arguments:
	//   other - The Quaternion to add to this Quaternion
	// Return Value:
	//   Quaternion containing the sum of this Quaternion and the other operand
	// ----------------------------------------------------------------------------------
	const Quaternion operator+( const Quaternion& other ) const
	{
		return Quaternion( *this ) += other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary subtraction operator
	// Arguments:
	//   other - The Quaternion to subtract from this Quaternion
	// Return Value:
	//   Quaternion containing the result of the subtraction of the other operand from 
	//   this Quaternion
	// ----------------------------------------------------------------------------------
	const Quaternion operator-( const Quaternion& other ) const
	{
		return Quaternion( *this ) -= other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary multiplication operator
	// Arguments:
	//   other - The Quaternion by which to multiply this Quaternion
	// Return Value:
	//   Quaternion containing the product of this Quaternion and the other operand
	// ----------------------------------------------------------------------------------
	const Quaternion operator*( const Quaternion& other ) const
	{
		return Quaternion( *this ) *= other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary scalar multiplication operator
	// Arguments:
	//   f - The scalar by which to multiply this Quaternion
	// Return Value:
	//   Quaternion containing product of this Quaternion and the scalar operand
	// ----------------------------------------------------------------------------------
	const Quaternion operator*( float f ) const
	{
		return Quaternion( *this ) *= f;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary scalar division operator
	// Arguments:
	//   f - The scalar by which to divide this Quaternion
	// Return Value:
	//   Quaternion containing this Quaternion divided by the scalar operand
	// ----------------------------------------------------------------------------------
	const Quaternion operator/( float f ) const
	{
		return Quaternion( *this ) /= f;
	}

	// Declare friend operator
	friend const Quaternion operator*( float f, const Quaternion& other );

	// ----------------------------------------------------------------------------------
	// Description
	//   Equality comparison operator
	// Arguments:
	//   other - The Quaternion with which to compare for equality
	// Return Value:
	//   true, if the two Quaternions are component-wise equal
	//   false, if the two Quaternions are not component-wise equal
	// ----------------------------------------------------------------------------------
	bool operator==( const Quaternion& other ) const
	{
		return ( x == other.x && y == other.y && z == other.z && w == other.w );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Inequality comparison operator
	// Arguments:
	//   other - The Quaternion with which to compare for inequality
	// Return Value:
	//   true, if the two Quaternions are not component-wise equal
	//   false, if the two Quaternions are component-wise equal
	// ----------------------------------------------------------------------------------
	bool operator!=( const Quaternion& other ) const
	{
		return ( x != other.x || y != other.y || z != other.z || w != other.w );
	}

	float x, y, z, w;
};

namespace CcpMath
{

float QuaternionLength( const Quaternion& q );

float QuaternionLengthSq( const Quaternion& q );

float QuaternionDot( const Quaternion& q1, const Quaternion& q2 );

Quaternion& QuaternionIdentity( Quaternion& out );
const Quaternion& QuaternionIdentity();

bool QuaternionIsIdentity( const Quaternion& q );

Quaternion& QuaternionConjugate( Quaternion& out, const Quaternion& q );
Quaternion QuaternionConjugate( const Quaternion& q );

void QuaternionToAxisAngle( const Quaternion& q, Vector3& axis, float& angle );

Quaternion& QuaternionRotationMatrix( Quaternion& out, const Matrix& m );
Quaternion QuaternionRotationMatrix( const Matrix& m );

Quaternion& QuaternionRotationAxis( Quaternion& out, const Vector3& axis, float angle );
Quaternion QuaternionRotationAxis( const Vector3& axis, float angle );

Quaternion& QuaternionRotationYawPitchRoll( Quaternion& out, float yaw, float pitch, float roll );
Quaternion QuaternionRotationYawPitchRoll( float yaw, float pitch, float roll );

Quaternion& QuaternionMultiply( Quaternion& out, const Quaternion& q1, const Quaternion& q2 );
Quaternion QuaternionMultiply( const Quaternion& q1, const Quaternion& q2 );

Quaternion& QuaternionNormalize( Quaternion& out, const Quaternion& q );
Quaternion QuaternionNormalize( const Quaternion& q );

Quaternion& QuaternionInverse( Quaternion& out, const Quaternion& q );
Quaternion QuaternionInverse( const Quaternion& q );

Quaternion& QuaternionLn( Quaternion& out, const Quaternion& q );
Quaternion QuaternionLn( const Quaternion& q );

Quaternion& QuaternionExp( Quaternion& out, const Quaternion& q );
Quaternion QuaternionExp( const Quaternion& q );

Quaternion& QuaternionSlerp( 
	Quaternion& out, 
	const Quaternion& q1,
	const Quaternion& q2, 
	float t );
Quaternion QuaternionSlerp( 
	const Quaternion& q1,
	const Quaternion& q2, 
	float t );

Quaternion& QuaternionSquad( 
	Quaternion& out, 
	const Quaternion& q1,
	const Quaternion& a, 
	const Quaternion& b,
	const Quaternion& c, 
	float t );
Quaternion QuaternionSquad( 
	const Quaternion& q1,
	const Quaternion& a, 
	const Quaternion& b,
	const Quaternion& c, 
	float t );

void QuaternionSquadSetup( 
	Quaternion& a, 
	Quaternion& b, 
	Quaternion& c,
	const Quaternion& q0, 
	const Quaternion& q1, 
	const Quaternion& q2, 
	const Quaternion& q3 );

}

float D3DXQuaternionLength
	( const Quaternion *pQ );

// Length squared, or "norm"
float D3DXQuaternionLengthSq
	( const Quaternion *pQ );

float D3DXQuaternionDot
	( const Quaternion *pQ1, const Quaternion *pQ2 );

// (0, 0, 0, 1)
Quaternion* D3DXQuaternionIdentity
	( Quaternion *pOut );

bool D3DXQuaternionIsIdentity
	( const Quaternion *pQ );

// (-x, -y, -z, w)
Quaternion* D3DXQuaternionConjugate
	( Quaternion *pOut, const Quaternion *pQ );

// Compute a quaternin's axis and angle of rotation. Expects unit quaternions.
void D3DXQuaternionToAxisAngle
	( const Quaternion *pQ, Vector3 *pAxis, float *pAngle );

// Build a quaternion from a rotation matrix.
Quaternion* D3DXQuaternionRotationMatrix
	( Quaternion *pOut, const Matrix *pM);

// Rotation about arbitrary axis.
Quaternion* D3DXQuaternionRotationAxis
	( Quaternion *pOut, const Vector3 *pV, float Angle );

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
Quaternion* D3DXQuaternionRotationYawPitchRoll
	( Quaternion *pOut, float Yaw, float Pitch, float Roll );

// Quaternion multiplication.  The result represents the rotation Q2
// followed by the rotation Q1.  (Out = Q2 * Q1)
Quaternion* D3DXQuaternionMultiply
	( Quaternion *pOut, const Quaternion *pQ1,
	const Quaternion *pQ2 );

Quaternion* D3DXQuaternionNormalize
	( Quaternion *pOut, const Quaternion *pQ );

// Conjugate and re-norm
Quaternion* D3DXQuaternionInverse
	( Quaternion *pOut, const Quaternion *pQ );

// Expects unit quaternions.
// if q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
Quaternion* D3DXQuaternionLn
	( Quaternion *pOut, const Quaternion *pQ );

// Expects pure quaternions. (w == 0)  w is ignored in calculation.
// if q = (0, theta * v); exp(q) = (cos(theta), sin(theta) * v)
Quaternion* D3DXQuaternionExp
	( Quaternion *pOut, const Quaternion *pQ );

// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
// Expects unit quaternions.
Quaternion* D3DXQuaternionSlerp
	( Quaternion *pOut, const Quaternion *pQ1,
	const Quaternion *pQ2, float t );

// Spherical quadrangle interpolation.
// Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
Quaternion* D3DXQuaternionSquad
	( Quaternion *pOut, const Quaternion *pQ1,
	const Quaternion *pA, const Quaternion *pB,
	const Quaternion *pC, float t );

// Setup control points for spherical quadrangle interpolation
// from Q1 to Q2.  The control points are chosen in such a way 
// to ensure the continuity of tangents with adjacent segments.
void D3DXQuaternionSquadSetup
	( Quaternion *pAOut, Quaternion *pBOut, Quaternion *pCOut,
	const Quaternion *pQ0, const Quaternion *pQ1, 
	const Quaternion *pQ2, const Quaternion *pQ3 );

// Barycentric interpolation.
// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))]
// Not used in trinity - skipping
Quaternion* D3DXQuaternionBaryCentric
	( Quaternion *pOut, const Quaternion *pQ1,
	const Quaternion *pQ2, const Quaternion *pQ3,
	float f, float g );


#endif // Quaternion_h