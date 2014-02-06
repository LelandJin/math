////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Filipp Pavlov
// Created:		June 2013
// Copyright:	CCP 2013
//

#include "CcpFloat.h"
#include "gtest/gtest.h"
#include "CcpMath/include/Float16.h"
#include <limits>

TEST( Float16, ConstructFromFloat ) 
{
	CcpMath::Float16 f1( 0.0f );
	EXPECT_EQ( 0, f1.GetUint16Value() );

	CcpMath::Float16 f2 = -0.0f;
	EXPECT_EQ( 0x8000, f2.GetUint16Value() );

	CcpMath::Float16 f3 = 1.0f;
	EXPECT_EQ( 0x3c00, f3.GetUint16Value() );

	CcpMath::Float16 f4 = -1.0f;
	EXPECT_EQ( f3.GetUint16Value() | 0x8000, f4.GetUint16Value() );
}

TEST( Float16, From32To16To32 ) 
{
	CcpMath::Float16 f1( 0.0f );
	EXPECT_EQ( 0.0f, float( f1 ) );

	CcpMath::Float16 f2( -0.0f );
	EXPECT_EQ( -0.0f, float( f2 ) );

	CcpMath::Float16 f3( 1.0f );
	EXPECT_EQ( 1.0f, float( f3 ) );

	CcpMath::Float16 f4( -1.0f );
	EXPECT_EQ( -1.0f, float( f4 ) );

	CcpMath::Float16 f5( std::numeric_limits<float>::quiet_NaN() );
	EXPECT_TRUE( CcpIsNaN( float( f5 ) ) );
}

TEST( Float16, Comparisons ) 
{
	EXPECT_TRUE( CcpMath::Float16( 0.0f ) == CcpMath::Float16( 0.0f ) );
	EXPECT_TRUE( CcpMath::Float16( 1.0f ) == CcpMath::Float16( 1.0f ) );
	EXPECT_TRUE( CcpMath::Float16( -1.0f ) == CcpMath::Float16( -1.0f ) );
	EXPECT_TRUE( CcpMath::Float16( std::numeric_limits<float>::quiet_NaN() ) == CcpMath::Float16( std::numeric_limits<float>::quiet_NaN() ) );

	EXPECT_FALSE( CcpMath::Float16( -0.0f ) == CcpMath::Float16( 0.0f ) );
	EXPECT_FALSE( CcpMath::Float16( 1.0f ) == CcpMath::Float16( 0.0f ) );
	EXPECT_FALSE( CcpMath::Float16( 0.0f ) == CcpMath::Float16( 1.0f ) );
	EXPECT_FALSE( CcpMath::Float16( -1.0f ) == CcpMath::Float16( 1.0f ) );

	EXPECT_FALSE( CcpMath::Float16( 0.0f ) != CcpMath::Float16( 0.0f ) );
	EXPECT_FALSE( CcpMath::Float16( 1.0f ) != CcpMath::Float16( 1.0f ) );
	EXPECT_FALSE( CcpMath::Float16( -1.0f ) != CcpMath::Float16( -1.0f ) );
	EXPECT_FALSE( CcpMath::Float16( std::numeric_limits<float>::quiet_NaN() ) != CcpMath::Float16( std::numeric_limits<float>::quiet_NaN() ) );

	EXPECT_TRUE( CcpMath::Float16( -0.0f ) != CcpMath::Float16( 0.0f ) );
	EXPECT_TRUE( CcpMath::Float16( 1.0f ) != CcpMath::Float16( 0.0f ) );
	EXPECT_TRUE( CcpMath::Float16( 0.0f ) != CcpMath::Float16( 1.0f ) );
	EXPECT_TRUE( CcpMath::Float16( -1.0f ) != CcpMath::Float16( 1.0f ) );
}

TEST( Float16, Float16To32Array ) 
{
	float expected[] = { 0.0f, -0.0f, 1.0f, -1.0f, std::numeric_limits<float>::quiet_NaN() };
	const size_t count = sizeof( expected ) / sizeof( expected[0] );

	CcpMath::Float16 in[count];
	float out[count];

	for( size_t i = 0; i < count; ++i )
	{
		in[i] = expected[i];
	}

	EXPECT_EQ( out, CcpMath::Float16To32Array( out, in, count ) );
	for( size_t i = 0; i + 1 < count; ++i )
	{
		EXPECT_EQ( expected[i], out[i] );
	}
	EXPECT_TRUE( CcpIsNaN( expected[count - 1] ) );
}

TEST( Float16, Float32To16Array ) 
{
	uint16_t expected[] = { 0, 0x8000, 0x3c00, 0x3c00 | 0x8000, 0x7fff };
	const size_t count = sizeof( expected ) / sizeof( expected[0] );
	float in[] = { 0.0f, -0.0f, 1.0f, -1.0f, std::numeric_limits<float>::quiet_NaN() };

	CcpMath::Float16 out[count];

	EXPECT_EQ( (CcpMath::Float16*)out, CcpMath::Float32To16Array( out, in, count ) );
	for( size_t i = 0; i < count; ++i )
	{
		EXPECT_EQ( expected[i], out[i].GetUint16Value() );
	}
}

TEST( Float16, D3DXFloat16To32Array ) 
{
	float expected[] = { 0.0f, -0.0f, 1.0f, -1.0f, std::numeric_limits<float>::quiet_NaN() };
	const size_t count = sizeof( expected ) / sizeof( expected[0] );

	D3DXFLOAT16 in[count];
	float out[count];

	for( size_t i = 0; i < count; ++i )
	{
		in[i] = expected[i];
	}

	EXPECT_EQ( out, D3DXFloat16To32Array( out, in, count ) );
	for( size_t i = 0; i + 1 < count; ++i )
	{
		EXPECT_EQ( expected[i], out[i] );
	}
	EXPECT_TRUE( CcpIsNaN( expected[count - 1] ) );
}

TEST( Float16, D3DXFloat32To16Array ) 
{
	uint16_t expected[] = { 0, 0x8000, 0x3c00, 0x3c00 | 0x8000, 0x7fff };
	const size_t count = sizeof( expected ) / sizeof( expected[0] );
	float in[] = { 0.0f, -0.0f, 1.0f, -1.0f, std::numeric_limits<float>::quiet_NaN() };

	D3DXFLOAT16 out[count];

	EXPECT_EQ( (D3DXFLOAT16*)out, D3DXFloat32To16Array( out, in, count ) );
	for( size_t i = 0; i < count; ++i )
	{
		EXPECT_EQ( expected[i], out[i].GetUint16Value() );
	}
}
