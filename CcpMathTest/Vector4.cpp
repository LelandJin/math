#include "CcpFloat.h"
#include "gtest/gtest.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <cstdint>
#include <cfloat>
#include "CcpMath/include/Vector4.h"
#include "CcpMath/include/Vector3.h"
#include "CcpMath/include/Matrix.h"

TEST( Vector4Test, Constructors ) 
{
	Vector4 vec1( 1.f, 2.f, 3.f, 4.f );
	EXPECT_EQ( 1.f, vec1.x );
	EXPECT_EQ( 2.f, vec1.y );
	EXPECT_EQ( 3.f, vec1.z );
	EXPECT_EQ( 4.f, vec1.w );

	Vector4 vec2( vec1 );
	EXPECT_EQ( 1.f, vec2.x );
	EXPECT_EQ( 2.f, vec2.y );
	EXPECT_EQ( 3.f, vec2.z );
	EXPECT_EQ( 4.f, vec2.w );

	float args[] = { 1.f, 2.f, 3.f, 4.f };
	Vector4 vec3( args );
	EXPECT_EQ( 1.f, vec3.x );
	EXPECT_EQ( 2.f, vec3.y );
	EXPECT_EQ( 3.f, vec3.z );
	EXPECT_EQ( 4.f, vec3.w );

	Vector3 xyz( 1.0f, 2.0f, 3.0f );
	Vector4 vec4( xyz, 4.0f );
	EXPECT_EQ( 1.f, vec4.x );
	EXPECT_EQ( 2.f, vec4.y );
	EXPECT_EQ( 3.f, vec4.z );
	EXPECT_EQ( 4.f, vec4.w );
}

TEST( Vector4Test, Subscripts ) 
{
	Vector4 vec1( 1.f, 2.f, 3.f, 4.f );
	EXPECT_EQ( 1.f, vec1[0] );
	EXPECT_EQ( 2.f, vec1[1] );
	EXPECT_EQ( 3.f, vec1[2] );
	EXPECT_EQ( 4.f, vec1[3] );

	const Vector4 vec2( 1.f, 2.f, 3.f, 4.f );
	EXPECT_EQ( 1.f, vec2[0] );
	EXPECT_EQ( 2.f, vec2[1] );
	EXPECT_EQ( 3.f, vec2[2] );
	EXPECT_EQ( 4.f, vec2[3] );
}

TEST( Vector4Test, Additions ) 
{
	Vector4 a( 1.f, 2.f, 3.f, 4.f );
	Vector4 b( 4.f, 5.f, 6.f, 7.f );

	a += b;
	EXPECT_EQ( 5.f, a.x );
	EXPECT_EQ( 7.f, a.y );
	EXPECT_EQ( 9.f, a.z );
	EXPECT_EQ( 11.f, a.w );

	a += a;
	EXPECT_EQ( 10.f, a.x );
	EXPECT_EQ( 14.f, a.y );
	EXPECT_EQ( 18.f, a.z );
	EXPECT_EQ( 22.f, a.w );

	Vector4 c = a + b;
	EXPECT_EQ( 14.f, c.x );
	EXPECT_EQ( 19.f, c.y );
	EXPECT_EQ( 24.f, c.z );
	EXPECT_EQ( 29.f, c.w );
}

TEST( Vector4Test, Subtractions ) 
{
	Vector4 a( 12.f, 23.f, 4.f, 45.f );
	Vector4 b( 4.f, 5.f, 6.f, 7.f );

	a -= b;
	EXPECT_EQ( 8.f, a.x );
	EXPECT_EQ( 18.f, a.y );
	EXPECT_EQ( -2.f, a.z );
	EXPECT_EQ( 38.f, a.w );

	Vector4 c = a - b;
	EXPECT_EQ( 4.f, c.x );
	EXPECT_EQ( 13.f, c.y );
	EXPECT_EQ( -8.f, c.z );
	EXPECT_EQ( 31.f, c.w );

	a -= a;
	EXPECT_EQ( 0.f, a.x );
	EXPECT_EQ( 0.f, a.y );
	EXPECT_EQ( 0.f, a.z );
	EXPECT_EQ( 0.f, a.w );
}

TEST( Vector4Test, Scaling ) 
{
	Vector4 a( 1.f, 2.f, 3.f, 4.f );

	a *= 0.5f;
	EXPECT_EQ( 0.5f, a.x );
	EXPECT_EQ( 1.f, a.y );
	EXPECT_EQ( 1.5f, a.z );
	EXPECT_EQ( 2.f, a.w );

	Vector4 b = a * -10.f;
	EXPECT_EQ( -5.f, b.x );
	EXPECT_EQ( -10.f, b.y );
	EXPECT_EQ( -15.f, b.z );
	EXPECT_EQ( -20.f, b.w );

	b /= -2.f;
	EXPECT_EQ( 2.5f, b.x );
	EXPECT_EQ( 5.f, b.y );
	EXPECT_EQ( 7.5f, b.z );
	EXPECT_EQ( 10.f, b.w );

	Vector4 c = b / 0.1f;
	EXPECT_EQ( 25.f, c.x );
	EXPECT_EQ( 50.f, c.y );
	EXPECT_EQ( 75.f, c.z );
	EXPECT_EQ( 100.f, c.w );

	b *= 0.f;
	EXPECT_EQ( 0.f, b.x );
	EXPECT_EQ( 0.f, b.y );
	EXPECT_EQ( 0.f, b.z );
	EXPECT_EQ( 0.f, b.w );

	c /= b.x;
	EXPECT_FALSE( CcpIsFinite( c.x ) );
	EXPECT_FALSE( CcpIsFinite( c.y ) );
	EXPECT_FALSE( CcpIsFinite( c.z ) );
	EXPECT_FALSE( CcpIsFinite( c.w ) );

	Vector4 d( 3.f * a );
	EXPECT_EQ( 1.5f, d.x );
	EXPECT_EQ( 3.f, d.y );
	EXPECT_EQ( 4.5f, d.z );
	EXPECT_EQ( 6.f, d.w );
}

TEST( Vector4Test, Signs ) 
{
	Vector4 a( 1.f, 2.f, 3.f, 4.f );

	Vector4 b( +a );
	EXPECT_EQ( 1.f, b.x );
	EXPECT_EQ( 2.f, b.y );
	EXPECT_EQ( 3.f, b.z );
	EXPECT_EQ( 4.f, b.w );

	Vector4 c( -a );
	EXPECT_EQ( -1.f, c.x );
	EXPECT_EQ( -2.f, c.y );
	EXPECT_EQ( -3.f, c.z );
	EXPECT_EQ( -4.f, c.w );
}

TEST( Vector4Test, Comparisons ) 
{
	EXPECT_TRUE( Vector4( 1.f, 2.f, 3.f, 4.f ) == Vector4( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_FALSE( Vector4( 1.f, 2.f, 3.f, 4.f ) == Vector4( 3.f, 2.f, 3.f, 4.f ) );
	EXPECT_FALSE( Vector4( 1.f, 2.f, 3.f, 4.f ) == Vector4( 1.f, 0.f, 3.f, 4.f ) );
	EXPECT_FALSE( Vector4( 1.f, 2.f, 3.f, 4.f ) == Vector4( 1.f, 2.f, 0.f, 4.f ) );
	EXPECT_FALSE( Vector4( 1.f, 0.f, 3.f, 4.f ) == Vector4( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_FALSE( Vector4( 1.f, 0.f, 3.f, 4.f ) == Vector4( 1.f, 2.f, 3.f, 5.f ) );

	EXPECT_FALSE( Vector4( 1.f, 2.f, 3.f, 4.f ) != Vector4( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_TRUE( Vector4( 1.f, 2.f, 3.f, 4.f ) != Vector4( 3.f, 2.f, 3.f, 4.f ) );
	EXPECT_TRUE( Vector4( 1.f, 2.f, 3.f, 4.f ) != Vector4( 1.f, 0.f, 3.f, 4.f ) );
	EXPECT_TRUE( Vector4( 1.f, 2.f, 3.f, 4.f ) != Vector4( 1.f, 2.f, 0.f, 4.f ) );
	EXPECT_TRUE( Vector4( 1.f, 0.f, 3.f, 4.f ) != Vector4( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_TRUE( Vector4( 1.f, 0.f, 3.f, 4.f ) != Vector4( 1.f, 2.f, 3.f, 5.f ) );
}

TEST( Vector4Test, DotProduct ) 
{
	Vector4 a( 1.f, 2.f, 3.f, 4.f );
	Vector4 b( 4.f, 5.f, 6.f, 7.f );
	EXPECT_EQ( 60.f, CcpMath::Vec4Dot( a, b ) );
	EXPECT_EQ( 60.f, D3DXVec4Dot( &a, &b ) );
}

TEST( Vector4Test, Vec4Add ) 
{
	Vector4 a( 1.f, 2.f, 3.f, 4.f );
	Vector4 b( 2.f, 3.f, 4.f, 5.f );

	Vector4 c;
	EXPECT_EQ( &c, &CcpMath::Vec4Add( c, a, b ) );
	EXPECT_EQ( 3.f, c.x );
	EXPECT_EQ( 5.f, c.y );
	EXPECT_EQ( 7.f, c.z );
	EXPECT_EQ( 9.f, c.w );

	c = CcpMath::Vec4Add( a, b );
	EXPECT_EQ( 3.f, c.x );
	EXPECT_EQ( 5.f, c.y );
	EXPECT_EQ( 7.f, c.z );
	EXPECT_EQ( 9.f, c.w );

	EXPECT_EQ( &c, D3DXVec4Add( &c, &a, &b ) );
	EXPECT_EQ( 3.f, c.x );
	EXPECT_EQ( 5.f, c.y );
	EXPECT_EQ( 7.f, c.z );
	EXPECT_EQ( 9.f, c.w );
}

TEST( Vector4Test, Vec4Scale ) 
{
	Vector4 a( 1.f, 2.f, 3.f, 4.f );
	Vector4 b;

	EXPECT_EQ( &b, &CcpMath::Vec4Scale( b, a, 0.5f ) );
	EXPECT_EQ( 0.5f, b.x );
	EXPECT_EQ( 1.f, b.y );
	EXPECT_EQ( 1.5f, b.z );
	EXPECT_EQ( 2.f, b.w );

	b = CcpMath::Vec4Scale( a, 0.5f );
	EXPECT_EQ( 0.5f, b.x );
	EXPECT_EQ( 1.f, b.y );
	EXPECT_EQ( 1.5f, b.z );
	EXPECT_EQ( 2.f, b.w );

	EXPECT_EQ( &b, D3DXVec4Scale( &b, &a, 0.5f ) );
	EXPECT_EQ( 0.5f, b.x );
	EXPECT_EQ( 1.f, b.y );
	EXPECT_EQ( 1.5f, b.z );
	EXPECT_EQ( 2.f, b.w );
}

TEST( Vector4Test, Vec4Transform ) 
{
	Matrix rot(
		0.7816392183303833f, 0.5501171946525574f, -0.2939578592777252f, 0.0f, 
		-0.4829292893409729f, 0.832030177116394f, 0.27295631170272827f, 0.0f, 
		0.3947397768497467f, -0.07139250636100769f, 0.9160150289535522f, 0.0f, 
		1.0f, 2.0f, 3.0f, 1.0f );
	Vector4 result( 4.9317169f, 2.6718793f, 7.9081745f, 2.0f );

	Vector4 v( 1.f, -2.f, 3.f, 2.f );
	Vector4 r1;
	EXPECT_EQ( &r1, &CcpMath::Vec4Transform( r1, v, rot ) );
	EXPECT_TRUE( result == r1 );

	Vector4 r2 = CcpMath::Vec4Transform( v, rot );
	EXPECT_TRUE( result == r2 );

	Vector4 r3;
	EXPECT_EQ( &r3, D3DXVec4Transform( &r3, &v, &rot ) );
	EXPECT_TRUE( result == r3 );
}

TEST( Vector4Test, MultiplyByMatrix ) 
{
	Matrix rot(
		0.7816392183303833f, 0.5501171946525574f, -0.2939578592777252f, 0.0f, 
		-0.4829292893409729f, 0.832030177116394f, 0.27295631170272827f, 0.0f, 
		0.3947397768497467f, -0.07139250636100769f, 0.9160150289535522f, 0.0f, 
		1.0f, 2.0f, 3.0f, 1.0f );
	Vector4 result( 4.9317169f, 2.6718793f, 7.9081745f, 2.0f );

	Vector4 v( 1.f, -2.f, 3.f, 2.f );
	EXPECT_TRUE( result == v * rot );
}
