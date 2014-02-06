#include "CcpFloat.h"
#include "gtest/gtest.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <cstdint>
#include <cfloat>
#include "CcpMath/include/Vector3.h"
#include "CcpMath/include/Vector4.h"
#include "CcpMath/include/Matrix.h"

TEST( Vector3Test, Constructors ) 
{
	Vector3 vec1( 1.f, 2.f, 3.f );
	EXPECT_EQ( 1.f, vec1.x );
	EXPECT_EQ( 2.f, vec1.y );
	EXPECT_EQ( 3.f, vec1.z );

	Vector3 vec2( vec1 );
	EXPECT_EQ( 1.f, vec2.x );
	EXPECT_EQ( 2.f, vec2.y );
	EXPECT_EQ( 3.f, vec2.z );

	float args[] = { 1.f, 2.f, 3.f };
	Vector3 vec3( args );
	EXPECT_EQ( 1.f, vec3.x );
	EXPECT_EQ( 2.f, vec3.y );
	EXPECT_EQ( 3.f, vec3.z );
}

TEST( Vector3Test, CastToFloatArray ) 
{
	const Vector3 vec1( 1.f, 2.f, 3.f );
	const float* array1( vec1 );
	EXPECT_EQ( 1.f, array1[0] );
	EXPECT_EQ( 2.f, array1[1] );
	EXPECT_EQ( 3.f, array1[2] );

	Vector3 vec2( 1.f, 2.f, 3.f );
	float* array2( vec2 );
	EXPECT_EQ( 1.f, array2[0] );
	EXPECT_EQ( 2.f, array2[1] );
	EXPECT_EQ( 3.f, array2[2] );
}

TEST( Vector3Test, Additions ) 
{
	Vector3 a( 1.f, 2.f, 3.f );
	Vector3 b( 4.f, 5.f, 6.f );

	a += b;
	EXPECT_EQ( 5.f, a.x );
	EXPECT_EQ( 7.f, a.y );
	EXPECT_EQ( 9.f, a.z );

	a += a;
	EXPECT_EQ( 10.f, a.x );
	EXPECT_EQ( 14.f, a.y );
	EXPECT_EQ( 18.f, a.z );

	Vector3 c = a + b;
	EXPECT_EQ( 14.f, c.x );
	EXPECT_EQ( 19.f, c.y );
	EXPECT_EQ( 24.f, c.z );
}

TEST( Vector3Test, Subtractions ) 
{
	Vector3 a( 12.f, 23.f, 4.f );
	Vector3 b( 4.f, 5.f, 6.f );

	a -= b;
	EXPECT_EQ( 8.f, a.x );
	EXPECT_EQ( 18.f, a.y );
	EXPECT_EQ( -2.f, a.z );

	Vector3 c = a - b;
	EXPECT_EQ( 4.f, c.x );
	EXPECT_EQ( 13.f, c.y );
	EXPECT_EQ( -8.f, c.z );

	a -= a;
	EXPECT_EQ( 0.f, a.x );
	EXPECT_EQ( 0.f, a.y );
	EXPECT_EQ( 0.f, a.z );
}

TEST( Vector3Test, Scaling ) 
{
	Vector3 a( 1.f, 2.f, 3.f );

	a *= 0.5f;
	EXPECT_EQ( 0.5f, a.x );
	EXPECT_EQ( 1.f, a.y );
	EXPECT_EQ( 1.5f, a.z );

	Vector3 b = a * -10.f;
	EXPECT_EQ( -5.f, b.x );
	EXPECT_EQ( -10.f, b.y );
	EXPECT_EQ( -15.f, b.z );

	b /= -2.f;
	EXPECT_EQ( 2.5f, b.x );
	EXPECT_EQ( 5.f, b.y );
	EXPECT_EQ( 7.5f, b.z );

	Vector3 c = b / 0.1f;
	EXPECT_EQ( 25.f, c.x );
	EXPECT_EQ( 50.f, c.y );
	EXPECT_EQ( 75.f, c.z );

	b *= 0.f;
	EXPECT_EQ( 0.f, b.x );
	EXPECT_EQ( 0.f, b.y );
	EXPECT_EQ( 0.f, b.z );

	c /= b.x;
	EXPECT_FALSE( CcpIsFinite( c.x ) );
	EXPECT_FALSE( CcpIsFinite( c.y ) );
	EXPECT_FALSE( CcpIsFinite( c.z ) );

	Vector3 d( 3.f * a );
	EXPECT_EQ( 1.5f, d.x );
	EXPECT_EQ( 3.f, d.y );
	EXPECT_EQ( 4.5f, d.z );
}

TEST( Vector3Test, Signs ) 
{
	Vector3 a( 1.f, 2.f, 3.f );

	Vector3 b( +a );
	EXPECT_EQ( 1.f, b.x );
	EXPECT_EQ( 2.f, b.y );
	EXPECT_EQ( 3.f, b.z );

	Vector3 c( -a );
	EXPECT_EQ( -1.f, c.x );
	EXPECT_EQ( -2.f, c.y );
	EXPECT_EQ( -3.f, c.z );
}

TEST( Vector3Test, Comparisons ) 
{
	EXPECT_TRUE( Vector3( 1.f, 2.f, 3.f ) == Vector3( 1.f, 2.f, 3.f ) );
	EXPECT_FALSE( Vector3( 1.f, 2.f, 3.f ) == Vector3( 3.f, 2.f, 3.f ) );
	EXPECT_FALSE( Vector3( 1.f, 2.f, 3.f ) == Vector3( 1.f, 0.f, 3.f ) );
	EXPECT_FALSE( Vector3( 1.f, 2.f, 3.f ) == Vector3( 1.f, 2.f, 0.f ) );
	EXPECT_FALSE( Vector3( 1.f, 0.f, 3.f ) == Vector3( 1.f, 2.f, 3.f ) );

	EXPECT_FALSE( Vector3( 1.f, 2.f, 3.f ) != Vector3( 1.f, 2.f, 3.f ) );
	EXPECT_TRUE( Vector3( 1.f, 2.f, 3.f ) != Vector3( 3.f, 2.f, 3.f ) );
	EXPECT_TRUE( Vector3( 1.f, 2.f, 3.f ) != Vector3( 1.f, 0.f, 3.f ) );
	EXPECT_TRUE( Vector3( 1.f, 2.f, 3.f ) != Vector3( 1.f, 2.f, 0.f ) );
	EXPECT_TRUE( Vector3( 1.f, 0.f, 3.f ) != Vector3( 1.f, 2.f, 3.f ) );
}

TEST( Vector3Test, DotProduct ) 
{
	Vector3 a( 1.f, 2.f, 3.f );
	Vector3 b( 4.f, 5.f, 6.f );
	EXPECT_EQ( 32.f, CcpMath::Vec3Dot( a, b ) );
	EXPECT_EQ( 32.f, D3DXVec3Dot( &a, &b ) );
}

TEST( Vector3Test, Length ) 
{
	Vector3 a( 1.f, 2.f, 3.f );
	EXPECT_EQ( sqrt( 14.f ), CcpMath::Vec3Length( a ) );
	EXPECT_EQ( sqrt( 14.f ), D3DXVec3Length( &a ) );
	EXPECT_EQ( 14.f, CcpMath::Vec3LengthSq( a ) );
	EXPECT_EQ( 14.f, D3DXVec3LengthSq( &a ) );
}

TEST( Vector3Test, CrossProduct ) 
{
	Vector3 a( 1.f, 2.f, 3.f );
	Vector3 b( 2.f, 3.f, 4.f );
	Vector3 c;
	CcpMath::Vec3Cross( c, a, b );
	EXPECT_EQ( -1.f, c.x );
	EXPECT_EQ( 2.f, c.y );
	EXPECT_EQ( -1.f, c.z );

	c = CcpMath::Vec3Cross( a, b );
	EXPECT_EQ( -1.f, c.x );
	EXPECT_EQ( 2.f, c.y );
	EXPECT_EQ( -1.f, c.z );

	EXPECT_EQ( &c, D3DXVec3Cross( &c, &a, &b ) );
	EXPECT_EQ( -1.f, c.x );
	EXPECT_EQ( 2.f, c.y );
	EXPECT_EQ( -1.f, c.z );
}

TEST( Vector3Test, AddSubtractFunctions ) 
{
	Vector3 a( 1.f, 2.f, 3.f );
	Vector3 b( 2.f, 3.f, 4.f );

	Vector3 c;
	EXPECT_EQ( &c, D3DXVec3Add( &c, &a, &b ) );
	EXPECT_EQ( 3.f, c.x );
	EXPECT_EQ( 5.f, c.y );
	EXPECT_EQ( 7.f, c.z );

	Vector3 d;
	EXPECT_EQ( &d, D3DXVec3Subtract( &d, &c, &a ) );
	EXPECT_EQ( 2.f, d.x );
	EXPECT_EQ( 3.f, d.y );
	EXPECT_EQ( 4.f, d.z );
}

TEST( Vector3Test, Vec3Minimize ) 
{
	Vector3 a( 14.f, 2.f, 53.f );
	Vector3 b( 3.f, 32.f, 4.f );

	Vector3 c;
	EXPECT_EQ( &c, &CcpMath::Vec3Minimize( c, a, b ) );
	EXPECT_EQ( 3.f, c.x );
	EXPECT_EQ( 2.f, c.y );
	EXPECT_EQ( 4.f, c.z );

	c = CcpMath::Vec3Minimize( a, b );
	EXPECT_EQ( 3.f, c.x );
	EXPECT_EQ( 2.f, c.y );
	EXPECT_EQ( 4.f, c.z );

	EXPECT_EQ( &c, D3DXVec3Minimize( &c, &a, &b ) );
	EXPECT_EQ( 3.f, c.x );
	EXPECT_EQ( 2.f, c.y );
	EXPECT_EQ( 4.f, c.z );
}

TEST( Vector3Test, Vec3Maximize ) 
{
	Vector3 a( 14.f, 2.f, 53.f );
	Vector3 b( 3.f, 32.f, 4.f );

	Vector3 c;
	EXPECT_EQ( &c, &CcpMath::Vec3Maximize( c, a, b ) );
	EXPECT_EQ( 14.f, c.x );
	EXPECT_EQ( 32.f, c.y );
	EXPECT_EQ( 53.f, c.z );

	c = CcpMath::Vec3Maximize( a, b );
	EXPECT_EQ( 14.f, c.x );
	EXPECT_EQ( 32.f, c.y );
	EXPECT_EQ( 53.f, c.z );

	EXPECT_EQ( &c, D3DXVec3Maximize( &c, &a, &b ) );
	EXPECT_EQ( 14.f, c.x );
	EXPECT_EQ( 32.f, c.y );
	EXPECT_EQ( 53.f, c.z );
}

TEST( Vector3Test, Vec3Scale ) 
{
	Vector3 a( 1.f, 2.f, 3.f );

	Vector3 b;
	EXPECT_EQ( &b, D3DXVec3Scale( &b, &a, 0.5f ) );
	EXPECT_EQ( 0.5f, b.x );
	EXPECT_EQ( 1.f, b.y );
	EXPECT_EQ( 1.5f, b.z );
}

TEST( Vector3Test, Vec3Lerp ) 
{
	Vector3 a( 1.f, 2.f, 3.f );
	Vector3 b( 2.f, 10.f, 14.f );

	Vector3 c;
	EXPECT_EQ( &c, &CcpMath::Vec3Lerp( c, a, b, 0.5f ) );
	EXPECT_EQ( 1.5f, c.x );
	EXPECT_EQ( 6.0f, c.y );
	EXPECT_EQ( 8.5f, c.z );

	EXPECT_EQ( &c, &CcpMath::Vec3Lerp( c, a, b, 0.f ) );
	EXPECT_EQ( 1.f, c.x );
	EXPECT_EQ( 2.f, c.y );
	EXPECT_EQ( 3.f, c.z );

	EXPECT_EQ( &c, &CcpMath::Vec3Lerp( c, a, b, 1.f ) );
	EXPECT_EQ( 2.f, c.x );
	EXPECT_EQ( 10.f, c.y );
	EXPECT_EQ( 14.f, c.z );

	EXPECT_EQ( &c, &CcpMath::Vec3Lerp( c, a, b, -1.f ) );
	EXPECT_EQ( 0.f, c.x );
	EXPECT_EQ( -6.f, c.y );
	EXPECT_EQ( -8.f, c.z );

	EXPECT_EQ( &c, &CcpMath::Vec3Lerp( c, a, b, 3.f ) );
	EXPECT_EQ( 4.f, c.x );
	EXPECT_EQ( 26.f, c.y );
	EXPECT_EQ( 36.f, c.z );

	c = CcpMath::Vec3Lerp( a, b, 0.5f );
	EXPECT_EQ( 1.5f, c.x );
	EXPECT_EQ( 6.0f, c.y );
	EXPECT_EQ( 8.5f, c.z );

	c = CcpMath::Vec3Lerp( c, a, b, 0.f );
	EXPECT_EQ( 1.f, c.x );
	EXPECT_EQ( 2.f, c.y );
	EXPECT_EQ( 3.f, c.z );

	c = CcpMath::Vec3Lerp( a, b, 1.f );
	EXPECT_EQ( 2.f, c.x );
	EXPECT_EQ( 10.f, c.y );
	EXPECT_EQ( 14.f, c.z );

	c = CcpMath::Vec3Lerp( c, a, b, -1.f );
	EXPECT_EQ( 0.f, c.x );
	EXPECT_EQ( -6.f, c.y );
	EXPECT_EQ( -8.f, c.z );

	c = CcpMath::Vec3Lerp( c, a, b, 3.f );
	EXPECT_EQ( 4.f, c.x );
	EXPECT_EQ( 26.f, c.y );
	EXPECT_EQ( 36.f, c.z );

	EXPECT_EQ( &c, D3DXVec3Lerp( &c, &a, &b, 0.5f ) );
	EXPECT_EQ( 1.5f, c.x );
	EXPECT_EQ( 6.0f, c.y );
	EXPECT_EQ( 8.5f, c.z );

	EXPECT_EQ( &c, D3DXVec3Lerp( &c, &a, &b, 0.f ) );
	EXPECT_EQ( 1.f, c.x );
	EXPECT_EQ( 2.f, c.y );
	EXPECT_EQ( 3.f, c.z );

	EXPECT_EQ( &c, D3DXVec3Lerp( &c, &a, &b, 1.f ) );
	EXPECT_EQ( 2.f, c.x );
	EXPECT_EQ( 10.f, c.y );
	EXPECT_EQ( 14.f, c.z );

	EXPECT_EQ( &c, D3DXVec3Lerp( &c, &a, &b, -1.f ) );
	EXPECT_EQ( 0.f, c.x );
	EXPECT_EQ( -6.f, c.y );
	EXPECT_EQ( -8.f, c.z );

	EXPECT_EQ( &c, D3DXVec3Lerp( &c, &a, &b, 3.f ) );
	EXPECT_EQ( 4.f, c.x );
	EXPECT_EQ( 26.f, c.y );
	EXPECT_EQ( 36.f, c.z );
}

TEST( Vector3Test, Vec3Normalize ) 
{
	Vector3 a( 1.f, 2.f, 3.f );
	float l = sqrt( a.x * a.x + a.y * a.y + a.z * a.z );
	Vector3 b;

	EXPECT_EQ( &b, &CcpMath::Vec3Normalize( b, a ) );
	EXPECT_EQ( a.x / l, b.x );
	EXPECT_EQ( a.y / l, b.y );
	EXPECT_EQ( a.z / l, b.z );

	b = CcpMath::Vec3Normalize( a );
	EXPECT_EQ( a.x / l, b.x );
	EXPECT_EQ( a.y / l, b.y );
	EXPECT_EQ( a.z / l, b.z );

	EXPECT_EQ( &b, D3DXVec3Normalize( &b, &a ) );
	EXPECT_EQ( a.x / l, b.x );
	EXPECT_EQ( a.y / l, b.y );
	EXPECT_EQ( a.z / l, b.z );
}

TEST( Vector3Test, Vec3Hermite ) 
{
	Vector3 v0( 1.f, 2.f, 3.f );
	Vector3 v1( 4.f, 5.f, 6.f );
	Vector3 t0( 7.f, 8.f, 9.f );
	Vector3 t1( 10.f, 11.f, 12.f );
	Vector3 c;

	EXPECT_EQ( &c, &CcpMath::Vec3Hermite( c, v0, t0, v1, t1, 0.f ) );
	EXPECT_TRUE( c == v0 );
	EXPECT_EQ( &c, &CcpMath::Vec3Hermite( c, v0, t0, v1, t1, 1.f ) );
	EXPECT_TRUE( c == v1 );

	c = CcpMath::Vec3Hermite( v0, t0, v1, t1, 0.f );
	EXPECT_TRUE( c == v0 );
	c = CcpMath::Vec3Hermite( v0, t0, v1, t1, 1.f );
	EXPECT_TRUE( c == v1 );

	EXPECT_EQ( &c, D3DXVec3Hermite( &c, &v0, &t0, &v1, &t1, 0.f ) );
	EXPECT_TRUE( c == v0 );
	EXPECT_EQ( &c, D3DXVec3Hermite( &c, &v0, &t0, &v1, &t1, 1.f ) );
	EXPECT_TRUE( c == v1 );
}

TEST( Vector3Test, Vec3CatmullRom ) 
{
	Vector3 v0( 1.f, 2.f, 3.f );
	Vector3 v1( 4.f, 5.f, 6.f );
	Vector3 v2( 7.f, 8.f, 9.f );
	Vector3 v3( 10.f, 11.f, 12.f );
	Vector3 c;

	EXPECT_EQ( &c, &CcpMath::Vec3CatmullRom( c, v0, v1, v2, v3, 0.f ) );
	EXPECT_TRUE( c == v1 );
	EXPECT_EQ( &c, &CcpMath::Vec3CatmullRom( c, v0, v1, v2, v3, 1.f ) );
	EXPECT_TRUE( c == v2 );

	c = CcpMath::Vec3CatmullRom( v0, v1, v2, v3, 0.f );
	EXPECT_TRUE( c == v1 );
	c = CcpMath::Vec3CatmullRom( v0, v1, v2, v3, 1.f );
	EXPECT_TRUE( c == v2 );

	EXPECT_EQ( &c, D3DXVec3CatmullRom( &c, &v0, &v1, &v2, &v3, 0.f ) );
	EXPECT_TRUE( c == v1 );
	EXPECT_EQ( &c, D3DXVec3CatmullRom( &c, &v0, &v1, &v2, &v3, 1.f ) );
	EXPECT_TRUE( c == v2 );
}

TEST( Vector3Test, Vec3Transform ) 
{
	Matrix rot(
		0.7816392183303833f, 0.5501171946525574f, -0.2939578592777252f, 0.0f, 
		-0.4829292893409729f, 0.832030177116394f, 0.27295631170272827f, 0.0f, 
		0.3947397768497467f, -0.07139250636100769f, 0.9160150289535522f, 0.0f, 
		1.0f, 2.0f, 3.0f, 1.0f );
	Vector4 result( 3.9317171573638916f, 0.6718793f, 4.9081746f, 1.0f );

	Vector3 v( 1.f, -2.f, 3.f );
	Vector4 r1;
	EXPECT_EQ( &r1, &CcpMath::Vec3Transform( r1, v, rot ) );
	EXPECT_TRUE( result == r1 );

	Vector4 r2 = CcpMath::Vec3Transform( v, rot );
	EXPECT_TRUE( result == r2 );

	Vector4 r3;
	EXPECT_EQ( &r3, D3DXVec3Transform( &r3, &v, &rot ) );
	EXPECT_TRUE( result == r3 );
}

TEST( Vector3Test, Vec3TransformCoord ) 
{
	Matrix rot(
		0.7816392183303833f, 0.5501171946525574f, -0.2939578592777252f, 0.0f, 
		-0.4829292893409729f, 0.832030177116394f, 0.27295631170272827f, 0.0f, 
		0.3947397768497467f, -0.07139250636100769f, 0.9160150289535522f, 0.0f, 
		1.0f, 2.0f, 3.0f, 1.0f );
	Vector3 result( 3.9317171573638916f, 0.6718793f, 4.9081746f );

	Vector3 v( 1.f, -2.f, 3.f );
	Vector3 r1;
	EXPECT_EQ( &r1, &CcpMath::Vec3TransformCoord( r1, v, rot ) );
	EXPECT_TRUE( result == r1 );

	Vector3 r2 = CcpMath::Vec3TransformCoord( v, rot );
	EXPECT_TRUE( result == r2 );

	Vector3 r3;
	EXPECT_EQ( &r3, D3DXVec3TransformCoord( &r3, &v, &rot ) );
	EXPECT_TRUE( result == r3 );
}

TEST( Vector3Test, Vec3TransformNormal ) 
{
	Matrix rot(
		0.7816392183303833f, 0.5501171946525574f, -0.2939578592777252f, 0.0f, 
		-0.4829292893409729f, 0.832030177116394f, 0.27295631170272827f, 0.0f, 
		0.3947397768497467f, -0.07139250636100769f, 0.9160150289535522f, 0.0f, 
		1.0f, 2.0f, 3.0f, 1.0f );
	Vector3 result( 2.9317171573638916f, -1.3281207f, 1.9081746f );

	Vector3 v( 1.f, -2.f, 3.f );
	Vector3 r1;
	EXPECT_EQ( &r1, &CcpMath::Vec3TransformNormal( r1, v, rot ) );
	EXPECT_TRUE( result == r1 );

	Vector3 r2 = CcpMath::Vec3TransformNormal( v, rot );
	EXPECT_TRUE( result == r2 );

	Vector3 r3;
	EXPECT_EQ( &r3, D3DXVec3TransformNormal( &r3, &v, &rot ) );
	EXPECT_TRUE( result == r3 );
}

TEST( Vector3Test, Vec3TransformCoordArray ) 
{
	struct TestInStream
	{
		Vector3 vec3;
		uint16_t extra;
	};
	struct TestOutStream
	{
		Vector3 vec3;
		uint32_t extra1;
		uint32_t extra2;
	};
	TestInStream in[2];
	in[0].vec3 = Vector3( 1.f, 2.f, 3.f );
	in[1].vec3 = Vector3( 1.0f, 0.f, 0.f );

	Matrix m = CcpMath::MatrixRotationX( 0.5 );
	TestOutStream result[2];
	result[0].vec3 = Vector3( 1.0f, 0.3168884515762329f, 3.5915987491607666f );
	result[1].vec3 = Vector3( 1.0f, 0.f, 0.f );

	TestOutStream out1[2];
	out1[0].extra1 = 4;
	out1[0].extra2 = 14;
	out1[1].extra1 = 5;
	out1[1].extra2 = 15;
	CcpMath::Vec3TransformCoordArray( 
		reinterpret_cast<Vector3*>( out1 ), 
		sizeof( TestOutStream ), 
		reinterpret_cast<Vector3*>( in ), 
		sizeof( TestInStream ),
		m,
		2 );
	for( uint32_t i = 0; i < 2; ++i )
	{
		EXPECT_TRUE( result[i].vec3 == out1[i].vec3 );
		EXPECT_EQ( 4 + i, out1[i].extra1 );
		EXPECT_EQ( 14 + i, out1[i].extra2 );
	}

	TestOutStream out2[2];
	out2[0].extra1 = 4;
	out2[0].extra2 = 14;
	out2[1].extra1 = 5;
	out2[1].extra2 = 15;
	EXPECT_EQ( 
		reinterpret_cast<Vector3*>( out2 ), 
		D3DXVec3TransformCoordArray( 
			reinterpret_cast<Vector3*>( out2 ), 
			sizeof( TestOutStream ), 
			reinterpret_cast<Vector3*>( in ), 
			sizeof( TestInStream ),
			&m,
			2 ) );
	for( uint32_t i = 0; i < 2; ++i )
	{
		EXPECT_TRUE( result[i].vec3 == out2[i].vec3 );
		EXPECT_EQ( 4 + i, out2[i].extra1 );
		EXPECT_EQ( 14 + i, out2[i].extra2 );
	}
}

TEST( Vector3Test, SphereBoundProbe ) 
{
	float radius;
	Vector3 center, rayDirection, rayPosition;

	radius = sqrt(77.0f);
	center.x = 1.0f; center.y = 2.0f; center.z = 3.0f;
	rayDirection.x = 2.0f; rayDirection.y = -4.0f; rayDirection.z = 2.0f;
	rayPosition.x = 5.0f; rayPosition.y = 5.0f; rayPosition.z = 9.0f;
	EXPECT_TRUE( CcpMath::SphereBoundProbe( center, radius, rayPosition, rayDirection ) );
	EXPECT_TRUE( D3DXSphereBoundProbe( &center, radius, &rayPosition, &rayDirection ) );

	rayPosition.x = 45.0f; rayPosition.y = -75.0f; rayPosition.z = 49.0f;
	EXPECT_FALSE( CcpMath::SphereBoundProbe( center, radius, rayPosition, rayDirection ) );
	EXPECT_FALSE( D3DXSphereBoundProbe( &center, radius, &rayPosition, &rayDirection ) );

	rayPosition.x = 5.0f; rayPosition.y = 7.0f; rayPosition.z = 9.0f;
	EXPECT_FALSE( CcpMath::SphereBoundProbe( center, radius, rayPosition, rayDirection ) );
	EXPECT_FALSE( D3DXSphereBoundProbe( &center, radius, &rayPosition, &rayDirection ) );

	rayPosition.x = 5.0f; rayPosition.y = 11.0f; rayPosition.z = 9.0f;
	EXPECT_FALSE( CcpMath::SphereBoundProbe( center, radius, rayPosition, rayDirection ) );
	EXPECT_FALSE( D3DXSphereBoundProbe( &center, radius, &rayPosition, &rayDirection ) );
}

TEST( Vector3Test, ComputeBoundingSphere ) 
{
	struct TestStream
	{
		Vector3 point;
		uint16_t padding;
	};

	TestStream stream[2];
	stream[0].point = Vector3( 1.0f, 2.0f, 3.0f );
	stream[0].padding = 1;
	stream[1].point = Vector3( 3.0f, 2.0f, 4.0f );
	stream[1].padding = 2;

	Vector3 center1;
	float radius1;
	Vector3 center2;
	float radius2;

	CcpMath::ComputeBoundingSphere( &stream[0].point, 0, sizeof( TestStream ), center1, radius1 );
	EXPECT_EQ( 0.0f, radius1 );
	EXPECT_TRUE( center1 == Vector3( 0.0f, 0.0f, 0.0f ) );
	D3DXComputeBoundingSphere( &stream[0].point, 0, sizeof( TestStream ), &center2, &radius2 );
	EXPECT_EQ( 0.0f, radius2 );
	EXPECT_TRUE( center2 == Vector3( 0.0f, 0.0f, 0.0f ) );

	CcpMath::ComputeBoundingSphere( &stream[0].point, 1, sizeof( TestStream ), center1, radius1 );
	EXPECT_EQ( 0.0f, radius1 );
	EXPECT_TRUE( center1 == stream[0].point );
	D3DXComputeBoundingSphere( &stream[0].point, 1, sizeof( TestStream ), &center2, &radius2 );
	EXPECT_EQ( 0.0f, radius2 );
	EXPECT_TRUE( center2 == stream[0].point );

	CcpMath::ComputeBoundingSphere( &stream[0].point, 2, sizeof( TestStream ), center1, radius1 );
	EXPECT_EQ( 1.118034f, radius1 );
	EXPECT_TRUE( center1 == Vector3( 2.0f, 2.0f, 3.5f ) );
	D3DXComputeBoundingSphere( &stream[0].point, 2, sizeof( TestStream ), &center2, &radius2 );
	EXPECT_EQ( 1.118034f, radius2 );
	EXPECT_TRUE( center2 == Vector3( 2.0f, 2.0f, 3.5f ) );
}

TEST( Vector3Test, IntersectTri ) 
{
    Vector3 position, ray, vertex[3];
    float u, v, dist;

    vertex[0] = Vector3( 1.0f, 0.0f, 0.0f );
    vertex[1] = Vector3( 2.0f, 0.0f, 0.0f );
    vertex[2] = Vector3( 1.0f, 1.0f, 0.0f );

    position = Vector3( -14.5f, -23.75f, -32.0f );
    ray = Vector3( 2.0f, 3.0f, 4.0f );

    EXPECT_TRUE( D3DXIntersectTri( &vertex[0], &vertex[1], &vertex[2], &position, &ray, &u, &v, &dist ) );
    EXPECT_EQ( 0.5f, u );
    EXPECT_EQ( 0.25f, v );
    EXPECT_EQ( 8.0f, dist );

    vertex[0] = Vector3( 1.0f, 0.0f, 0.0f );
    vertex[1] = Vector3( 2.0f, 0.0f, 0.0f );
    vertex[2] = Vector3( 1.0f, 1.0f, 0.0f );

    position = Vector3( 17.5f, 24.25f, 32.0f );
    ray = Vector3( 2.0f, 3.0f, 4.0f );

    EXPECT_FALSE( D3DXIntersectTri( &vertex[0], &vertex[1], &vertex[2], &position, &ray, &u, &v, &dist ) );

    vertex[0] = Vector3( 4.0f, 0.0f, 0.0f );
    vertex[1] = Vector3( 6.0f, 0.0f, 0.0f );
    vertex[2] = Vector3( 4.0f, 2.0f, 0.0f );

    position = Vector3( 1.0f, 1.0f, 0.0f );
    ray = Vector3( 1.0f, 0.0f, 0.0f );

    EXPECT_FALSE( D3DXIntersectTri( &vertex[0], &vertex[1], &vertex[2], &position, &ray, &u, &v, &dist ) );
}