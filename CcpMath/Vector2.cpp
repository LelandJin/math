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
#include <algorithm>
#include "include/Vector2.h"
#include "include/Vector4.h"
#include "include/Matrix.h"

const Vector2 operator*( float f, const Vector2& other )
{
	return Vector2( f * other.x, f * other.y );
}

float CcpMath::Vec2Length( const Vector2& v )
{
	return sqrt( v.x * v.x + v.y * v.y );
}

float CcpMath::Vec2LengthSq( const Vector2& v )
{
	return v.x * v.x + v.y * v.y;
}

float CcpMath::Vec2Dot( const Vector2& v1, const Vector2& v2 )
{
	return v1.x * v2.x + v1.y * v2.y;
}

float CcpMath::Vec2CCW( const Vector2& v1, const Vector2& v2 )
{
	return v1.x * v2.y - v1.y * v2.x;
}

Vector2& CcpMath::Vec2Scale( Vector2& out, const Vector2& v, float s )
{
	out.x = v.x * s;
	out.y = v.y * s;
	return out;
}

Vector2 CcpMath::Vec2Scale( const Vector2& v, float s )
{
	Vector2 out;
	return Vec2Scale( out, v, s );
}

Vector2& CcpMath::Vec2Normalize( Vector2& out, const Vector2& v )
{
	float l = 1.f / sqrt( v.x * v.x + v.y * v.y );
	out.x = v.x * l;
	out.y = v.y * l;
	return out;
}

Vector2 CcpMath::Vec2Normalize( const Vector2& v )
{
	Vector2 out;
	return Vec2Normalize( out, v );
}

Vector4& CcpMath::Vec2Transform( Vector4& out, const Vector2& v, const Matrix& m )
{
	out.x = v.x * m._11 + v.y * m._21 + m._41;
	out.y = v.x * m._12 + v.y * m._22 + m._42;
	out.z = v.x * m._13 + v.y * m._23 + m._43;
	out.w = v.x * m._14 + v.y * m._24 + m._44;
	return out;
}

Vector4 CcpMath::Vec2Transform( const Vector2& v, const Matrix& m )
{
    Vector4 result;
    Vec2Transform( result, v, m );
    return result;
}


float D3DXVec2Length( const Vector2 *pV )
{
	return CcpMath::Vec2Length( *pV );
}

float D3DXVec2LengthSq( const Vector2 *pV )
{
	return CcpMath::Vec2LengthSq( *pV );
}

float D3DXVec2Dot( const Vector2 *pV1, const Vector2 *pV2 )
{
	return CcpMath::Vec2Dot( *pV1, *pV2 );
}

float D3DXVec2CCW( const Vector2 *pV1, const Vector2 *pV2 )
{
	return CcpMath::Vec2CCW( *pV1, *pV2 );
}

Vector2* D3DXVec2Scale( Vector2 *pOut, const Vector2 *pV, float s )
{
	return &CcpMath::Vec2Scale( *pOut, *pV, s );
}

Vector2* D3DXVec2Normalize( Vector2 *pOut, const Vector2 *pV )
{
	return &CcpMath::Vec2Normalize( *pOut, *pV );
}

Vector4* D3DXVec2Transform( Vector4 *pOut, const Vector2 *pV, const Matrix *pM )
{
    return &CcpMath::Vec2Transform( *pOut, *pV, *pM );
}

