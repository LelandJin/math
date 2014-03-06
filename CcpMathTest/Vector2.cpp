#include "CcpFloat.h"
#include "gtest/gtest.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <cstdint>
#include <cfloat>
#include "CcpMath/include/Vector2.h"

TEST( Vector2Test, Constructors ) 
{
	Vector2 vec1( 1.f, 2.f );
	EXPECT_EQ( 1.f, vec1.x );
	EXPECT_EQ( 2.f, vec1.y );

	Vector2 vec2( vec1 );
	EXPECT_EQ( 1.f, vec2.x );
	EXPECT_EQ( 2.f, vec2.y );

	float args[] = { 1.f, 2.f };
	Vector2 vec3( args );
	EXPECT_EQ( 1.f, vec3.x );
	EXPECT_EQ( 2.f, vec3.y );
}

TEST( Vector2Test, CastToFloatArray ) 
{
	const Vector2 vec1( 1.f, 2.f );
	const float* array1( vec1 );
	EXPECT_EQ( 1.f, array1[0] );
	EXPECT_EQ( 2.f, array1[1] );

	Vector2 vec2( 1.f, 2.f );
	float* array2( vec2 );
	EXPECT_EQ( 1.f, array2[0] );
	EXPECT_EQ( 2.f, array2[1] );
}

TEST( Vector2Test, Additions ) 
{
	Vector2 a( 1.f, 2.f );
	Vector2 b( 4.f, 5.f );

	a += b;
	EXPECT_EQ( 5.f, a.x );
	EXPECT_EQ( 7.f, a.y );

	a += a;
	EXPECT_EQ( 10.f, a.x );
	EXPECT_EQ( 14.f, a.y );

	Vector2 c = a + b;
	EXPECT_EQ( 14.f, c.x );
	EXPECT_EQ( 19.f, c.y );
}

TEST( Vector2Test, Subtractions ) 
{
	Vector2 a( 12.f, 23.f );
	Vector2 b( 4.f, 5.f );

	a -= b;
	EXPECT_EQ( 8.f, a.x );
	EXPECT_EQ( 18.f, a.y );

	Vector2 c = a - b;
	EXPECT_EQ( 4.f, c.x );
	EXPECT_EQ( 13.f, c.y );

	a -= a;
	EXPECT_EQ( 0.f, a.x );
	EXPECT_EQ( 0.f, a.y );
}

TEST( Vector2Test, Scaling ) 
{
	Vector2 a( 1.f, 2.f );

	a *= 0.5f;
	EXPECT_EQ( 0.5f, a.x );
	EXPECT_EQ( 1.f, a.y );

	Vector2 b = a * -10.f;
	EXPECT_EQ( -5.f, b.x );
	EXPECT_EQ( -10.f, b.y );

	b /= -2.f;
	EXPECT_EQ( 2.5f, b.x );
	EXPECT_EQ( 5.f, b.y );

	Vector2 c = b / 0.1f;
	EXPECT_EQ( 25.f, c.x );
	EXPECT_EQ( 50.f, c.y );

	b *= 0.f;
	EXPECT_EQ( 0.f, b.x );
	EXPECT_EQ( 0.f, b.y );

	c /= b.x;
	EXPECT_FALSE( CcpIsFinite( c.x ) );
	EXPECT_FALSE( CcpIsFinite( c.y ) );

	Vector2 d( 3.f * a );
	EXPECT_EQ( 1.5f, d.x );
	EXPECT_EQ( 3.f, d.y );
}

TEST( Vector2Test, Signs ) 
{
	Vector2 a( 1.f, 2.f );

	Vector2 b( +a );
	EXPECT_EQ( 1.f, b.x );
	EXPECT_EQ( 2.f, b.y );

	Vector2 c( -a );
	EXPECT_EQ( -1.f, c.x );
	EXPECT_EQ( -2.f, c.y );
}

TEST( Vector2Test, Comparisons ) 
{
	EXPECT_TRUE( Vector2( 1.f, 2.f ) == Vector2( 1.f, 2.f ) );
	EXPECT_FALSE( Vector2( 1.f, 2.f ) == Vector2( 3.f, 2.f ) );
	EXPECT_FALSE( Vector2( 1.f, 2.f ) == Vector2( 1.f, 0.f ) );
	EXPECT_FALSE( Vector2( 1.f, 0.f ) == Vector2( 1.f, 2.f ) );

	EXPECT_FALSE( Vector2( 1.f, 2.f ) != Vector2( 1.f, 2.f ) );
	EXPECT_TRUE( Vector2( 1.f, 2.f ) != Vector2( 3.f, 2.f ) );
	EXPECT_TRUE( Vector2( 1.f, 2.f ) != Vector2( 1.f, 0.f ) );
	EXPECT_TRUE( Vector2( 1.f, 0.f ) != Vector2( 1.f, 2.f ) );
}

TEST( Vector2Test, Length ) 
{
	Vector2 a( 1.f, 2.f );
	EXPECT_EQ( sqrtf( 5.f ), CcpMath::Vec2Length( a ) );
	EXPECT_EQ( sqrtf( 5.f ), D3DXVec2Length( &a ) );
	EXPECT_EQ( 5.f, CcpMath::Vec2LengthSq( a ) );
	EXPECT_EQ( 5.f, D3DXVec2LengthSq( &a ) );
}

TEST( Vector2Test, DotProduct ) 
{
	Vector2 a( 1.f, 2.f );
	Vector2 b( 4.f, 5.f );
	EXPECT_EQ( 14.f, CcpMath::Vec2Dot( a, b ) );
	EXPECT_EQ( 14.f, D3DXVec2Dot( &a, &b ) );
}

TEST( Vector2Test, Vec2CCW ) 
{
	Vector2 a( 1.f, 2.f );
	Vector2 b( 2.f, 3.f );

	EXPECT_EQ( -1.f, CcpMath::Vec2CCW( a, b ) );
	EXPECT_EQ( -1.f, D3DXVec2CCW( &a, &b ) );
}

TEST( Vector2Test, Vec2Scale ) 
{
	Vector2 a( 1.f, 2.f );
	Vector2 b;

	EXPECT_EQ( &b, &CcpMath::Vec2Scale( b, a, 0.5f ) );
	EXPECT_EQ( 0.5f, b.x );
	EXPECT_EQ( 1.f, b.y );

	b = CcpMath::Vec2Scale( a, 0.5f );
	EXPECT_EQ( 0.5f, b.x );
	EXPECT_EQ( 1.f, b.y );

	EXPECT_EQ( &b, D3DXVec2Scale( &b, &a, 0.5f ) );
	EXPECT_EQ( 0.5f, b.x );
	EXPECT_EQ( 1.f, b.y );
}

TEST( Vector2Test, Vec2Normalize ) 
{
	Vector2 a( 1.f, 2.f );
	float l = sqrt( a.x * a.x + a.y * a.y );
	Vector2 b;

	EXPECT_EQ( &b, &CcpMath::Vec2Normalize( b, a ) );
	EXPECT_EQ( a.x / l, b.x );
	EXPECT_EQ( a.y / l, b.y );

	b = CcpMath::Vec2Normalize( a );
	EXPECT_EQ( a.x / l, b.x );
	EXPECT_EQ( a.y / l, b.y );

	EXPECT_EQ( &b, D3DXVec2Normalize( &b, &a ) );
	EXPECT_EQ( a.x / l, b.x );
	EXPECT_EQ( a.y / l, b.y );
}
