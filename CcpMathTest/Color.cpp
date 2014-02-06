#include "gtest/gtest.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include "CcpMath/include/Color.h"

TEST( Color, ColorAdjustContrast ) 
{
	Color c2;
	Color c3( 0.1f, 0.2f, 0.3f, 0.4f );
	EXPECT_EQ( &c2, D3DXColorAdjustContrast( &c2, &c3, 0.0f ) );
	EXPECT_TRUE( Color( 0.5f, 0.5f, 0.5f, 0.4f ) == c2 );
	
	EXPECT_EQ( &c2, D3DXColorAdjustContrast( &c2, &c3, 1.0f ) );
    EXPECT_FLOAT_EQ( c3.r, c2.r );
	EXPECT_FLOAT_EQ( c3.g, c2.g );
	EXPECT_FLOAT_EQ( c3.b, c2.b );
	EXPECT_FLOAT_EQ( c3.a, c2.a );
}

TEST( Color, ColorAdjustSaturation ) 
{
	Color c2;
	Color c3( 0.1f, 0.2f, 0.3f, 0.4f );
	float grey = c3.r * 0.2125f + c3.g * 0.7154f + c3.b * 0.0721f;
	EXPECT_EQ( &c2, D3DXColorAdjustSaturation( &c2, &c3, 0.0f ) );
	EXPECT_FLOAT_EQ( grey, c2.r );
	EXPECT_FLOAT_EQ( grey, c2.g );
	EXPECT_FLOAT_EQ( grey, c2.b );
	EXPECT_FLOAT_EQ( c3.a, c2.a );
	
	EXPECT_EQ( &c2, D3DXColorAdjustSaturation( &c2, &c3, 1.0f ) );
	EXPECT_FLOAT_EQ( c3.r, c2.r );
	EXPECT_FLOAT_EQ( c3.g, c2.g );
	EXPECT_FLOAT_EQ( c3.b, c2.b );
	EXPECT_FLOAT_EQ( c3.a, c2.a );
}