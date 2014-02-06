////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Snorri Sturluson
// Created:		May 2013
// Copyright:	CCP 2013
//

#pragma once
#ifndef Plane_h
#define Plane_h

struct Vector3;
struct Vector4;
struct Matrix;

struct Plane
{
public:
	Plane();
	Plane( const float* );
	Plane( float a, float b, float c, float d );

	// casting
	operator float* ();
	operator const float* () const;

	// assignment operators
	Plane& operator *= ( float );
	Plane& operator /= ( float );

	// unary operators
	Plane operator + () const;
	Plane operator - () const;

	// binary operators
	Plane operator * ( float ) const;
	Plane operator / ( float ) const;

	friend Plane operator * ( float, const Plane& );

	bool operator == ( const Plane& ) const;
	bool operator != ( const Plane& ) const;

	float a, b, c, d;
};

namespace CcpMath
{

float PlaneDot( const Plane& p, const Vector4& v );

float PlaneDotCoord( const Plane& p, const Vector3& v );

float PlaneDotNormal( const Plane& p, const Vector3& v );

Plane& PlaneNormalize( Plane& out, const Plane& p );
Plane PlaneNormalize( const Plane& p );

bool PlaneIntersectLine( 
	Vector3& out, 
	const Plane& p, 
	const Vector3& v1,
	const Vector3& v2 );

Plane& PlaneFromPoints( 
	Plane& out, 
	const Vector3& v1, 
	const Vector3& v2,
	const Vector3& v3 );
Plane PlaneFromPoints( 
	const Vector3& v1, 
	const Vector3& v2,
	const Vector3& v3 );

void PlaneTransformArray( 
	Plane *out, 
	uint32_t outStride, 
	const Plane* in, 
	uint32_t inStride, 
	const Matrix& m, 
	uint32_t count );

}

typedef struct Plane D3DXPLANE;

// ax + by + cz + dw
float D3DXPlaneDot
	( const Plane *pP, const Vector4 *pV);

// ax + by + cz + d
float D3DXPlaneDotCoord
	( const Plane *pP, const Vector3 *pV);

// ax + by + cz
float D3DXPlaneDotNormal
	( const Plane *pP, const Vector3 *pV);

// Not used in trinity - skipping
Plane* D3DXPlaneScale
	(Plane *pOut, const Plane *pP, float s);

// Normalize plane (so that |a,b,c| == 1)
Plane* D3DXPlaneNormalize
	( Plane *pOut, const Plane *pP);

// Find the intersection between a plane and a line.  If the line is
// parallel to the plane, NULL is returned.
Vector3* D3DXPlaneIntersectLine
	( Vector3 *pOut, const Plane *pP, const Vector3 *pV1,
	const Vector3 *pV2);

// Construct a plane from a point and a normal
// Not used in trinity - skipping
Plane* D3DXPlaneFromPointNormal
	( Plane *pOut, const Vector3 *pPoint, const Vector3 *pNormal);

// Construct a plane from 3 points
Plane* D3DXPlaneFromPoints
	( Plane *pOut, const Vector3 *pV1, const Vector3 *pV2,
	const Vector3 *pV3);

// Transform a plane by a matrix.  The vector (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
// Not used in trinity - skipping
Plane* D3DXPlaneTransform
	( Plane *pOut, const Plane *pP, const Matrix *pM );

// Transform an array of planes by a matrix.  The vectors (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
Plane* D3DXPlaneTransformArray
	( Plane *pOut, uint32_t OutStride, const Plane *pP, uint32_t PStride, const Matrix *pM, uint32_t n );

#endif // Plane_h