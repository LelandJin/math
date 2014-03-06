#include "CcpFloat.h"
#include "gtest/gtest.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <cstdint>
#include <cfloat>
#include "CcpMath/include/Plane.h"
#include "CcpMath/include/Vector3.h"
#include "CcpMath/include/Vector4.h"
#include "CcpMath/include/Matrix.h"

TEST( Plane, Constructors ) 
{
	Plane p1( 1.f, 2.f, 3.f, 4.f );
	EXPECT_EQ( 1.f, p1.a );
	EXPECT_EQ( 2.f, p1.b );
	EXPECT_EQ( 3.f, p1.c );
	EXPECT_EQ( 4.f, p1.d );

	Plane p2( p1 );
	EXPECT_EQ( 1.f, p2.a );
	EXPECT_EQ( 2.f, p2.b );
	EXPECT_EQ( 3.f, p2.c );
	EXPECT_EQ( 4.f, p2.d );

	float args[] = { 1.f, 2.f, 3.f, 4.f };
	Plane p3( args );
	EXPECT_EQ( 1.f, p3.a );
	EXPECT_EQ( 2.f, p3.b );
	EXPECT_EQ( 3.f, p3.c );
	EXPECT_EQ( 4.f, p3.d );
}

TEST( Plane, CastToFloatArray ) 
{
	const Plane p1( 1.f, 2.f, 3.f, 4.f );
	const float* array1( p1 );
	EXPECT_EQ( 1.f, array1[0] );
	EXPECT_EQ( 2.f, array1[1] );
	EXPECT_EQ( 3.f, array1[2] );
	EXPECT_EQ( 4.f, array1[3] );

	Plane p2( 1.f, 2.f, 3.f, 4.f );
	float* array2( p2 );
	EXPECT_EQ( 1.f, array2[0] );
	EXPECT_EQ( 2.f, array2[1] );
	EXPECT_EQ( 3.f, array2[2] );
	EXPECT_EQ( 4.f, array2[3] );
}

TEST( Plane, Scaling ) 
{
	Plane a( 1.f, 2.f, 3.f, 4.f );

	a *= 0.5f;
	EXPECT_EQ( 0.5f, a.a );
	EXPECT_EQ( 1.f, a.b );
	EXPECT_EQ( 1.5f, a.c );
	EXPECT_EQ( 2.f, a.d );

	Plane b = a * -10.f;
	EXPECT_EQ( -5.f, b.a );
	EXPECT_EQ( -10.f, b.b );
	EXPECT_EQ( -15.f, b.c );
	EXPECT_EQ( -20.f, b.d );

	b /= -2.f;
	EXPECT_EQ( 2.5f, b.a );
	EXPECT_EQ( 5.f, b.b );
	EXPECT_EQ( 7.5f, b.c );
	EXPECT_EQ( 10.f, b.d );

	Plane c = b / 0.1f;
	EXPECT_EQ( 25.f, c.a );
	EXPECT_EQ( 50.f, c.b );
	EXPECT_EQ( 75.f, c.c );
	EXPECT_EQ( 100.f, c.d );

	b *= 0.f;
	EXPECT_EQ( 0.f, b.a );
	EXPECT_EQ( 0.f, b.b );
	EXPECT_EQ( 0.f, b.c );
	EXPECT_EQ( 0.f, b.d );

	c /= b.a;
	EXPECT_FALSE( CcpIsFinite( c.a ) );
	EXPECT_FALSE( CcpIsFinite( c.b ) );
	EXPECT_FALSE( CcpIsFinite( c.c ) );
	EXPECT_FALSE( CcpIsFinite( c.d ) );

	Plane d( 3.f * a );
	EXPECT_EQ( 1.5f, d.a );
	EXPECT_EQ( 3.f, d.b );
	EXPECT_EQ( 4.5f, d.c );
	EXPECT_EQ( 6.f, d.d );
}

TEST( Plane, Signs ) 
{
	Plane a( 1.f, 2.f, 3.f, 4.f );

	Plane b( +a );
	EXPECT_EQ( 1.f, b.a );
	EXPECT_EQ( 2.f, b.b );
	EXPECT_EQ( 3.f, b.c );
	EXPECT_EQ( 4.f, b.d );

	Plane c( -a );
	EXPECT_EQ( -1.f, c.a );
	EXPECT_EQ( -2.f, c.b );
	EXPECT_EQ( -3.f, c.c );
	EXPECT_EQ( -4.f, c.d );
}

TEST( Plane, Comparisons ) 
{
	EXPECT_TRUE( Plane( 1.f, 2.f, 3.f, 4.f ) == Plane( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_FALSE( Plane( 1.f, 2.f, 3.f, 4.f ) == Plane( 3.f, 2.f, 3.f, 4.f ) );
	EXPECT_FALSE( Plane( 1.f, 2.f, 3.f, 4.f ) == Plane( 1.f, 0.f, 3.f, 4.f ) );
	EXPECT_FALSE( Plane( 1.f, 2.f, 3.f, 4.f ) == Plane( 1.f, 2.f, 0.f, 4.f ) );
	EXPECT_FALSE( Plane( 1.f, 0.f, 3.f, 4.f ) == Plane( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_FALSE( Plane( 1.f, 0.f, 3.f, 4.f ) == Plane( 1.f, 2.f, 3.f, 5.f ) );

	EXPECT_FALSE( Plane( 1.f, 2.f, 3.f, 4.f ) != Plane( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_TRUE( Plane( 1.f, 2.f, 3.f, 4.f ) != Plane( 3.f, 2.f, 3.f, 4.f ) );
	EXPECT_TRUE( Plane( 1.f, 2.f, 3.f, 4.f ) != Plane( 1.f, 0.f, 3.f, 4.f ) );
	EXPECT_TRUE( Plane( 1.f, 2.f, 3.f, 4.f ) != Plane( 1.f, 2.f, 0.f, 4.f ) );
	EXPECT_TRUE( Plane( 1.f, 0.f, 3.f, 4.f ) != Plane( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_TRUE( Plane( 1.f, 0.f, 3.f, 4.f ) != Plane( 1.f, 2.f, 3.f, 5.f ) );
}

TEST( Plane, PlaneDot ) 
{
	Plane a( 1.f, 2.f, 3.f, 4.f );
	Vector4 b( 4.f, 5.f, 6.f, 7.f );
	EXPECT_EQ( 60.f, CcpMath::PlaneDot( a, b ) );
	EXPECT_EQ( 60.f, D3DXPlaneDot( &a, &b ) );
}

TEST( Plane, PlaneDotCoord ) 
{
	Plane a( 1.f, 2.f, 3.f, 4.f );
	Vector3 b( 4.f, 5.f, 6.f );
	EXPECT_EQ( 36.f, CcpMath::PlaneDotCoord( a, b ) );
	EXPECT_EQ( 36.f, D3DXPlaneDotCoord( &a, &b ) );
}

TEST( Plane, PlaneDotNormal ) 
{
	Plane a( 1.f, 2.f, 3.f, 4.f );
	Vector3 b( 4.f, 5.f, 6.f );
	EXPECT_EQ( 32.f, CcpMath::PlaneDotNormal( a, b ) );
	EXPECT_EQ( 32.f, D3DXPlaneDotNormal( &a, &b ) );
}

TEST( Plane, PlaneNormalize ) 
{
	Plane a( 1.f, 2.f, 3.f, 4.f );
	float l = sqrt( a.a * a.a + a.b * a.b + a.c * a.c );
	Plane b;

	EXPECT_EQ( &b, &CcpMath::PlaneNormalize( b, a ) );
	EXPECT_FLOAT_EQ( a.a / l, b.a );
	EXPECT_FLOAT_EQ( a.b / l, b.b );
	EXPECT_FLOAT_EQ( a.c / l, b.c );
	EXPECT_FLOAT_EQ( a.d / l, b.d );

	b = CcpMath::PlaneNormalize( a );
	EXPECT_FLOAT_EQ( a.a / l, b.a );
	EXPECT_FLOAT_EQ( a.b / l, b.b );
	EXPECT_FLOAT_EQ( a.c / l, b.c );
	EXPECT_FLOAT_EQ( a.d / l, b.d );

	EXPECT_EQ( &b, D3DXPlaneNormalize( &b, &a ) );
	EXPECT_FLOAT_EQ( a.a / l, b.a );
	EXPECT_FLOAT_EQ( a.b / l, b.b );
	EXPECT_FLOAT_EQ( a.c / l, b.c );
	EXPECT_FLOAT_EQ( a.d / l, b.d );
}

TEST( Plane, PlaneIntersectLine ) 
{
	Plane p1( 1.f, 0.f, 0.f, 0.f );
	Vector3 a11( 0.0f, 2.0f, 0.0f );
	Vector3 a12( 0.0f, 3.0f, 0.0f );

	Vector3 r1, r2;
	EXPECT_FALSE( CcpMath::PlaneIntersectLine( r1, p1, a11, a12 ) );
	EXPECT_EQ( nullptr, D3DXPlaneIntersectLine( &r1, &p1, &a11, &a12 ) );

	Vector3 a21( 1.0f, 4.0f, 0.0f );
	Vector3 a22( 2.0f, 4.0f, 0.0f );
	Vector3 result( 0.0f, 4.0f, 0.0f );

	EXPECT_TRUE( CcpMath::PlaneIntersectLine( r1, p1, a21, a22 ) );
	EXPECT_TRUE( r1 == result );

	EXPECT_EQ( &r2, D3DXPlaneIntersectLine( &r2, &p1, &a21, &a22 ) );
	EXPECT_TRUE( r2 == result );
}

TEST( Plane, PlaneFromPoints ) 
{
	Vector3 a( 1.0f, 0.0f, 0.0f );
	Vector3 b( 0.0f, 2.0f, 0.0f );
	Vector3 c( 3.0f, 4.0f, 0.0f );

	Plane result( 0.0f, 0.0f, -1.0f, 0.0f );

	Plane p1, p2, p3;

	EXPECT_EQ( &p1, &CcpMath::PlaneFromPoints( p1, a, b, c ) );
	EXPECT_TRUE( p1 == result );

	p2 = CcpMath::PlaneFromPoints( a, b, c );
	EXPECT_TRUE( p2 == result );

	EXPECT_EQ( &p3, D3DXPlaneFromPoints( &p3, &a, &b, &c ) );
	EXPECT_TRUE( p3 == result );
}

TEST( Plane, PlaneTransformArray ) 
{
	struct TestInStream
	{
		Plane plane;
		uint16_t extra;
	};
	struct TestOutStream
	{
		Plane plane;
		uint32_t extra;
	};
	TestInStream in[2];
	in[0].plane = Plane( 1.f, 2.f, 3.f, 4.f );
	in[1].plane = Plane( 1.0f, 0.f, 0.f, -3.f );

	Matrix m = CcpMath::MatrixRotationX( 0.5 );
	TestOutStream result[2];
	result[0].plane = Plane( 1.0000000f, 0.31688845f, 3.5915987f, 4.0f );
	result[1].plane = Plane( 1.0f, 0.f, 0.f, -3.f );

	TestOutStream out1[2];
	out1[0].extra = 4;
	out1[1].extra = 5;
	CcpMath::PlaneTransformArray( 
		reinterpret_cast<Plane*>( out1 ), 
		sizeof( TestOutStream ), 
		reinterpret_cast<Plane*>( in ), 
		sizeof( TestInStream ),
		m,
		2 );
	for( uint32_t i = 0; i < 2; ++i )
	{
		EXPECT_TRUE( result[i].plane == out1[i].plane );
		EXPECT_EQ( 4 + i, out1[i].extra );
	}

	TestOutStream out2[2];
	out2[0].extra = 4;
	out2[1].extra = 5;
	EXPECT_EQ( 
		reinterpret_cast<Plane*>( out2 ), 
		D3DXPlaneTransformArray( 
			reinterpret_cast<Plane*>( out2 ), 
			sizeof( TestOutStream ), 
			reinterpret_cast<Plane*>( in ), 
			sizeof( TestInStream ),
			&m,
			2 ) );
	for( uint32_t i = 0; i < 2; ++i )
	{
		EXPECT_TRUE( result[i].plane == out2[i].plane );
		EXPECT_EQ( 4 + i, out2[i].extra );
	}
}
