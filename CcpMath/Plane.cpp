////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Filipp Pavlov
// Created:		May 2013
// Copyright:	CCP 2013
//

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif
#include <cstdint>
#include "include/Plane.h"
#include "include/Vector3.h"
#include "include/Vector4.h"
#include "include/Matrix.h"

Plane::Plane() 
{
}

Plane::Plane( const float* data )
	:a( data[0] ),
	b( data[1] ),
	c( data[2] ),
	d( data[3] )
{
}

Plane::Plane( float aa, float ab, float ac, float ad )
	:a( aa ),
	b( ab ),
	c( ac ),
	d( ad )
{
}

Plane::operator float* ()
{
	return &a;
}

Plane::operator const float* () const
{
	return &a;
}

Plane& Plane::operator *= ( float scale )
{
	a *= scale;
	b *= scale;
	c *= scale;
	d *= scale;
	return *this;
}

Plane& Plane::operator /= ( float scale )
{
	a /= scale;
	b /= scale;
	c /= scale;
	d /= scale;
	return *this;
}

Plane Plane::operator + () const
{
	return *this;
}

Plane Plane::operator - () const
{
	return Plane( -a, -b, -c, -d );
}

Plane Plane::operator * ( float scale ) const
{
	return Plane( a * scale, b * scale, c * scale, d * scale );
}

Plane Plane::operator / ( float scale ) const
{
	return Plane( a / scale, b / scale, c / scale, d / scale );
}

Plane operator * ( float scale, const Plane& plane )
{
	return plane * scale;
}

bool Plane::operator == ( const Plane& other ) const
{
	return a == other.a && b == other.b && c == other.c && d == other.d;
}

bool Plane::operator != ( const Plane& other ) const
{
	return a != other.a || b != other.b || c != other.c || d != other.d;
}


float CcpMath::PlaneDot( const Plane& p, const Vector4& v )
{
	return p.a * v.x + p.b * v.y + p.c * v.z + p.d * v.w;
}

float CcpMath::PlaneDotCoord( const Plane& p, const Vector3& v )
{
	return p.a * v.x + p.b * v.y + p.c * v.z + p.d;
}

float CcpMath::PlaneDotNormal( const Plane& p, const Vector3& v )
{
	return p.a * v.x + p.b * v.y + p.c * v.z;
}

Plane& CcpMath::PlaneNormalize( Plane& out, const Plane& p )
{
	float l = 1.0f / Vec3Length( reinterpret_cast<const Vector3&>( p ) );
	out.a = p.a * l;
	out.b = p.b * l;
	out.c = p.c * l;
	out.d = p.d * l;
	return out;
}

Plane CcpMath::PlaneNormalize( const Plane& p )
{
	Plane out;
	return PlaneNormalize( out, p );
}

bool CcpMath::PlaneIntersectLine( 
	Vector3& out, 
	const Plane& p, 
	const Vector3& v1,
	const Vector3& v2 )
{
	Vector3 direction = v2 - v1;
	Vector3 normal;
	normal.x = p.a;
	normal.y = p.b;
	normal.z = p.c;

	float dot = Vec3Dot( normal, direction );
	if ( dot == 0.0f ) 
	{
		return false;
	}
	float temp = ( p.d + Vec3Dot( normal, v1 ) ) / dot;
	out.x = v1.x - temp * direction.x;
	out.y = v1.y - temp * direction.y;
	out.z = v1.z - temp * direction.z;
	return true;
}

Plane& CcpMath::PlaneFromPoints( 
	Plane& out, 
	const Vector3& v1, 
	const Vector3& v2,
	const Vector3& v3 )
{
	Vector3 edge1 = v2 - v1;
	Vector3 edge2 = v3 - v1;
	Vec3Normalize( reinterpret_cast<Vector3&>( out ), Vec3Cross( edge1, edge2 ) );
	out.d = -Vec3Dot( v1, reinterpret_cast<Vector3&>( out ) );
	return out;
}

Plane CcpMath::PlaneFromPoints( 
	const Vector3& v1, 
	const Vector3& v2,
	const Vector3& v3 )
{
	Plane out;
	return PlaneFromPoints( out, v1, v2, v3 );
}

void CcpMath::PlaneTransformArray( 
	Plane *out, 
	uint32_t outStride, 
	const Plane* in, 
	uint32_t inStride, 
	const Matrix& m, 
	uint32_t count )
{
	for( uint32_t i = 0; i < count; ++i )
	{
		Plane plane = *in;
		out->a = m.m[0][0] * plane.a + m.m[1][0] * plane.b + m.m[2][0] * plane.c + m.m[3][0] * plane.d;
		out->b = m.m[0][1] * plane.a + m.m[1][1] * plane.b + m.m[2][1] * plane.c + m.m[3][1] * plane.d;
		out->c = m.m[0][2] * plane.a + m.m[1][2] * plane.b + m.m[2][2] * plane.c + m.m[3][2] * plane.d;
		out->d = m.m[0][3] * plane.a + m.m[1][3] * plane.b + m.m[2][3] * plane.c + m.m[3][3] * plane.d;

		out = reinterpret_cast<Plane*>( reinterpret_cast<uint8_t*>( out ) + outStride );
		in = reinterpret_cast<const Plane*>( reinterpret_cast<const uint8_t*>( in ) + inStride );
	}
}





float D3DXPlaneDot( const Plane *pP, const Vector4 *pV)
{
	return CcpMath::PlaneDot( *pP, *pV );
}

float D3DXPlaneDotCoord( const Plane *pP, const Vector3 *pV )
{
	return CcpMath::PlaneDotCoord( *pP, *pV );
}

float D3DXPlaneDotNormal( const Plane *pP, const Vector3 *pV )
{
	return CcpMath::PlaneDotNormal( *pP, *pV );
}

Plane* D3DXPlaneNormalize( Plane *pOut, const Plane *pP )
{
	return &CcpMath::PlaneNormalize( *pOut, *pP );
}

Vector3* D3DXPlaneIntersectLine( 
	Vector3 *pOut, 
	const Plane *pP, 
	const Vector3 *pV1,
	const Vector3 *pV2)
{
	if( CcpMath::PlaneIntersectLine( *pOut, *pP, *pV1, *pV2 ) )
	{
		return pOut;
	}
	return nullptr;
}

Plane* D3DXPlaneFromPoints( Plane *pOut, const Vector3 *pV1, const Vector3 *pV2, const Vector3 *pV3)
{
	return &CcpMath::PlaneFromPoints( *pOut, *pV1, *pV2, *pV3 );
}

Plane* D3DXPlaneTransformArray( Plane *pOut, uint32_t OutStride, const Plane *pP, uint32_t PStride, const Matrix *pM, uint32_t n )
{
	CcpMath::PlaneTransformArray( pOut, OutStride, pP, PStride, *pM, n );
	return pOut;
}
