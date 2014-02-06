#include "CcpFloat.h"
#include "gtest/gtest.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <cstdint>
#include <cfloat>
#include "CcpMath/include/Matrix.h"
#include "CcpMath/include/Quaternion.h"
#include "CcpMath/include/Vector2.h"
#include "CcpMath/include/Plane.h"
#include "CcpMath/include/Vector4.h"

#define EXPECT_MATRIX_EQ( expected, actual )								\
{																			\
	for( int i = 0; i < 4; ++i )											\
		for( int j = 0; j < 4; ++j )										\
			EXPECT_FLOAT_EQ( ( expected ).m[i][j], ( actual ).m[i][j] );	\
}

TEST( Matrix, Constructors ) 
{
	Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( ( i + 1 ) * 10 + ( j + 1 ), mat1.m[i][j] );
		}
	}

	Matrix mat2( mat1 );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( ( i + 1 ) * 10 + ( j + 1 ), mat1.m[i][j] );
		}
	}

	float elements[] = { 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f };

	Matrix mat3( elements );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( ( i + 1 ) * 10 + ( j + 1 ), mat1.m[i][j] );
		}
	}
}

TEST( Matrix, ElementAccess ) 
{
	Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( ( i + 1 ) * 10 + ( j + 1 ), mat1( i, j ) );
		}
	}

	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			mat1( i, j ) *= i + j;
			EXPECT_EQ( ( ( i + 1 ) * 10 + ( j + 1 ) ) * ( i + j ), mat1( i, j ) );
		}
	}
}

TEST( Matrix, Additions ) 
{
	Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	Matrix mat2( 
		55.f, 56.f, 57.f, 58.f,
		65.f, 66.f, 67.f, 68.f,
		75.f, 76.f, 77.f, 78.f,
		85.f, 86.f, 87.f, 88.f );

	mat1 += mat2;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			float element = float( i + 1 ) * 10 + ( j + 1 ) + ( i + 5 ) * 10 + ( j + 5 );
			EXPECT_EQ( element, mat1.m[i][j] );
		}
	}

	Matrix mat3 = mat1 + mat2;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat1.m[i][j] + mat2.m[i][j], mat3.m[i][j] );
		}
	}
}

TEST( Matrix, Subtractions ) 
{
	Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );

	float elements[16];
	for( int i = 0; i < 16; ++i )
	{
		elements[i] = 16.f - float( i );
	}
	Matrix mat2( elements );

	mat1 -= mat2;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( ( i + 1 ) * 10 + ( j + 1 ) - mat2.m[i][j], mat1.m[i][j] );
		}
	}

	Matrix mat3 = mat1 - mat2;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat1.m[i][j] - mat2.m[i][j], mat3.m[i][j] );
		}
	}
}

TEST( Matrix, Scaling ) 
{
	Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );

	mat1 *= 0.5f;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( ( ( i + 1 ) * 10 + ( j + 1 ) ) * 0.5f, mat1.m[i][j] );
		}
	}

	Matrix mat2 = mat1 * 10.f;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( ( ( i + 1 ) * 10 + ( j + 1 ) ) * 5.f, mat2.m[i][j] );
		}
	}

	mat2 /= 2.f;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( ( ( i + 1 ) * 10 + ( j + 1 ) ) * 2.5f, mat2.m[i][j] );
		}
	}

	Matrix mat3 = mat2 / 0.1f;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( ( ( i + 1 ) * 10 + ( j + 1 ) ) * 25.f, mat3.m[i][j] );
		}
	}

	mat2 *= 0.f;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( 0.f, mat2.m[i][j] );
		}
	}

	mat3 /= mat2._11;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_FALSE( CcpIsFinite( mat3.m[i][j] ) );
		}
	}

	Matrix mat4( 3.f * mat1 );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( ( ( i + 1 ) * 10 + ( j + 1 ) ) * 1.5f, mat4.m[i][j] );
		}
	}
}

TEST( Matrix, Signs ) 
{
	Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );

	Matrix mat2( +mat1 );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat1.m[i][j], mat2.m[i][j] );
		}
	}

	Matrix mat3( -mat1 );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( -mat1.m[i][j], mat3.m[i][j] );
		}
	}
}

TEST( Matrix, Comparisons ) 
{
	Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	Matrix mat2( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	Matrix mat3( 
		55.f, 56.f, 57.f, 58.f,
		65.f, 66.f, 67.f, 68.f,
		75.f, 76.f, 77.f, 78.f,
		85.f, 86.f, 87.f, 88.f );

	EXPECT_TRUE( mat1 == mat2 );
	EXPECT_FALSE( mat1 == mat3 );
	EXPECT_FALSE( mat1 != mat2 );
	EXPECT_TRUE( mat2 != mat3 );

	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			Matrix mat4( mat1 );
			mat4.m[i][j] += 1.f;
			EXPECT_FALSE( mat4 == mat1 );
			EXPECT_TRUE( mat4 != mat1 );
		}
	}
}

TEST( Matrix, Translation ) 
{
	const Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	Matrix mat2( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );

	EXPECT_TRUE( Vector3( 41.f, 42.f, 43.f ) == mat1.GetTranslation() );
	mat2.GetTranslation().x = 123.f;
	EXPECT_TRUE( Vector3( 123.f, 42.f, 43.f ) == mat2.GetTranslation() );
	Vector3 newTranslation( 1.f, 2.f, 3.f );
	mat2.SetTranslation( &newTranslation );
	EXPECT_TRUE( newTranslation == mat2.GetTranslation() );
}

TEST( Matrix, XRow ) 
{
	const Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	Matrix mat2( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );

	EXPECT_TRUE( Vector3( 11.f, 12.f, 13.f ) == mat1.GetX() );
	mat2.GetX().x = 123.f;
	EXPECT_TRUE( Vector3( 123.f, 12.f, 13.f ) == mat2.GetX() );
}

TEST( Matrix, YRow ) 
{
	const Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	Matrix mat2( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );

	EXPECT_TRUE( Vector3( 21.f, 22.f, 23.f ) == mat1.GetY() );
	mat2.GetY().x = 123.f;
	EXPECT_TRUE( Vector3( 123.f, 22.f, 23.f ) == mat2.GetY() );
}

TEST( Matrix, ZRow ) 
{
	const Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	Matrix mat2( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );

	EXPECT_TRUE( Vector3( 31.f, 32.f, 33.f ) == mat1.GetZ() );
	mat2.GetZ().x = 123.f;
	EXPECT_TRUE( Vector3( 123.f, 32.f, 33.f ) == mat2.GetZ() );
}


TEST( Matrix, MatrixIdentity ) 
{
	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixIdentity( mat1 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( i == j ? 1.f : 0.f, mat1.m[i][j] );
		}
	}

	Matrix mat2 = CcpMath::MatrixIdentity();
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( i == j ? 1.f : 0.f, mat2.m[i][j] );
		}
	}

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixIdentity( &mat3 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( i == j ? 1.f : 0.f, mat3.m[i][j] );
		}
	}
}

TEST( Matrix, MatrixIsIdentity ) 
{
	const Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	EXPECT_FALSE( CcpMath::MatrixIsIdentity( mat1 ) );
	EXPECT_FALSE( D3DXMatrixIsIdentity( &mat1 ) );

	Matrix mat2 = CcpMath::MatrixIdentity();
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat2 ) );
	EXPECT_TRUE( D3DXMatrixIsIdentity( &mat2 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			Matrix mat3 = mat2;
			mat3.m[i][j] = 2.f;
			EXPECT_FALSE( CcpMath::MatrixIsIdentity( mat3 ) );
			EXPECT_FALSE( D3DXMatrixIsIdentity( &mat3 ) );
		}
	}
}

TEST( Matrix, MatrixDeterminant ) 
{
	const Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );

	EXPECT_EQ( 0.f, CcpMath::MatrixDeterminant( mat1 ) );

	EXPECT_EQ( 1.f, CcpMath::MatrixDeterminant( CcpMath::MatrixIdentity() ) );
}

TEST( Matrix, MatrixTranspose ) 
{
	Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );

	Matrix mat2;
	EXPECT_EQ( &mat2, &CcpMath::MatrixTranspose( mat2, mat1 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat1.m[i][j], mat2.m[j][i] );
		}
	}

	Matrix mat3 = CcpMath::MatrixTranspose( mat1 );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat1.m[i][j], mat3.m[j][i] );
		}
	}

	Matrix mat4;
	EXPECT_EQ( &mat4, D3DXMatrixTranspose( &mat4, &mat1 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat1.m[i][j], mat4.m[j][i] );
		}
	}

	EXPECT_EQ( &mat1, &CcpMath::MatrixTranspose( mat1, mat1 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat2.m[i][j], mat1.m[i][j] );
		}
	}

	EXPECT_EQ( &mat1, D3DXMatrixTranspose( &mat1, &mat1 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat2.m[i][j], mat1.m[j][i] );
		}
	}
}

TEST( Matrix, MatrixMultiply ) 
{
	Matrix mat1( 
		11.f, 12.f, 13.f, 14.f,
		21.f, 22.f, 23.f, 24.f,
		31.f, 32.f, 33.f, 34.f,
		41.f, 42.f, 43.f, 44.f );
	Matrix mat2( 
		55.f, 56.f, 57.f, 58.f,
		65.f, 66.f, 67.f, 68.f,
		75.f, 76.f, 77.f, 78.f,
		85.f, 86.f, 87.f, 88.f );

	Matrix mat12(
		3550.f, 3600.f, 3650.f, 3700.f, 
		6350.f, 6440.f, 6530.f, 6620.f, 
		9150.f, 9280.f, 9410.f, 9540.f, 
		11950.f, 12120.f, 12290.f, 12460.f );
	Matrix mat11(
		1350.f, 1400.f, 1450.f, 1500.f, 
		2390.f, 2480.f, 2570.f, 2660.f, 
		3430.f, 3560.f, 3690.f, 3820.f, 
		4470.f, 4640.f, 4810.f, 4980.f );

	Matrix mat3 = mat1 * mat2;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat12.m[i][j], mat3.m[i][j] );
		}
	}

	Matrix mat4 = mat1;
	mat4 *= mat4;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat11.m[i][j], mat4.m[i][j] );
		}
	}

	Matrix mat5;
	EXPECT_EQ( &mat5, &CcpMath::MatrixMultiply( mat5, mat1, mat2 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat12.m[i][j], mat5.m[i][j] );
		}
	}

	mat5 = CcpMath::MatrixMultiply( mat1, mat2 );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat12.m[i][j], mat5.m[i][j] );
		}
	}

	Matrix mat6( mat1 );
	EXPECT_EQ( &mat6, &CcpMath::MatrixMultiply( mat6, mat6, mat2 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat12.m[i][j], mat6.m[i][j] );
		}
	}

	Matrix mat7;
	EXPECT_EQ( &mat7, D3DXMatrixMultiply( &mat7, &mat1, &mat2 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat12.m[i][j], mat7.m[i][j] );
		}
	}

	Matrix mat8( mat1 );
	EXPECT_EQ( &mat8, D3DXMatrixMultiply( &mat8, &mat8, &mat2 ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( mat12.m[i][j], mat8.m[i][j] );
		}
	}
}

TEST( Matrix, MatrixInverse ) 
{
	Matrix mat1;
	CcpMath::MatrixIdentity( mat1 );
	Matrix mat2;
	float det1;
	EXPECT_EQ( &mat2, &CcpMath::MatrixInverse( mat2, det1, mat1 ) );
	EXPECT_EQ( 1.f, det1 );
	EXPECT_TRUE( mat2 == mat1 );

	Matrix mat3;
	EXPECT_EQ( &mat3, &CcpMath::MatrixInverse( mat3, mat1 ) );
	EXPECT_TRUE( mat3 == mat1 );

	float det2;
	Matrix mat4 = CcpMath::MatrixInverse( det2, mat1 );
	EXPECT_EQ( 1.f, det2 );
	EXPECT_TRUE( mat4 == mat1 );

	float det3;
	Matrix mat5;
	EXPECT_EQ( &mat5, D3DXMatrixInverse( &mat5, &det3, &mat1 ) );
	EXPECT_EQ( 1.f, det3 );
	EXPECT_TRUE( mat5 == mat1 );

	Matrix mat6(
		9.45227336883545f, 0.f, 0.f, 0.f, 
		0.f, 6.616590976715088f, 0.f, 0.f, 
		0.f, 0.f, 1.001001000404358f, 1.f, 
		0.f, 0.f, -0.10010010004043579f, 0.f );
	Matrix mat6inv(
		0.10579466074705124f, 0.f, 0.f, 0.f, 
		0.f, 0.15113522112369537f, 0.f, 0.f, 
		0.f, 0.f, 0.f, -9.989999771118164f, 
		0.f, 0.f, 1.f, 10.f );

	EXPECT_EQ( &mat2, &CcpMath::MatrixInverse( mat2, det1, mat6 ) );
	EXPECT_EQ( 6.260443210601807f, det1 );
	EXPECT_TRUE( mat2 == mat6inv );

	EXPECT_EQ( &mat3, &CcpMath::MatrixInverse( mat3, mat6 ) );
	EXPECT_TRUE( mat3 == mat6inv );

	mat4 = CcpMath::MatrixInverse( det2, mat6 );
	EXPECT_EQ( 6.260443210601807f, det2 );
	EXPECT_TRUE( mat4 == mat6inv );

	EXPECT_EQ( &mat5, D3DXMatrixInverse( &mat5, &det3, &mat6 ) );
	EXPECT_EQ( 6.260443210601807f, det3 );
	EXPECT_TRUE( mat5 == mat6inv );

	Matrix mat7;
	EXPECT_EQ( &mat7, D3DXMatrixInverse( &mat7, nullptr, &mat6 ) );
	EXPECT_TRUE( mat7 == mat6inv );

	Matrix mat8 = mat6;
	EXPECT_TRUE( mat6inv == CcpMath::MatrixInverse( mat8, mat8 ) );
}


TEST( Matrix, MatrixScaling ) 
{
	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixScaling( mat1, 4.f, 3.f, 2.f ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( i == j ? float( 4 - i ) : 0.f, mat1.m[i][j] );
		}
	}

	Matrix mat2 = CcpMath::MatrixScaling( 4.f, 3.f, 2.f );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( i == j ? float( 4 - i ) : 0.f, mat2.m[i][j] );
		}
	}

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixScaling( &mat3, 4.f, 3.f, 2.f ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			EXPECT_EQ( i == j ? float( 4 - i ) : 0.f, mat3.m[i][j] );
		}
	}
}

TEST( Matrix, MatrixTranslation ) 
{
	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixTranslation( mat1, 4.f, 3.f, 2.f ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			if( i == 3 )
			{
				EXPECT_EQ( 4.f - j, mat1.m[i][j] );
			}
			else
			{
				EXPECT_EQ( i == j ? 1.f : 0.f, mat1.m[i][j] );
			}
		}
	}

	Matrix mat2 = CcpMath::MatrixTranslation( 4.f, 3.f, 2.f );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			if( i == 3 )
			{
				EXPECT_EQ( 4.f - j, mat2.m[i][j] );
			}
			else
			{
				EXPECT_EQ( i == j ? 1.f : 0.f, mat2.m[i][j] );
			}
		}
	}

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixTranslation( &mat3, 4.f, 3.f, 2.f ) );
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			if( i == 3 )
			{
				EXPECT_EQ( 4.f - j, mat3.m[i][j] );
			}
			else
			{
				EXPECT_EQ( i == j ? 1.f : 0.f, mat3.m[i][j] );
			}
		}
	}
}

TEST( Matrix, MatrixRotationX ) 
{
	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationX( mat1, 0.f ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat1 ) );

	Matrix mat2 = CcpMath::MatrixRotationX( 0.f );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat2 ) );

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixRotationX( &mat3, 0.f ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat3 ) );

	Matrix rot03(
		1.f, 0.f, 0.f, 0.f, 
		0.f, 0.9553365111351013f, 0.29552021622657776f, 0.f, 
		0.f, -0.29552021622657776f, 0.9553365111351013f, 0.f, 
		0.f, 0.f, 0.f, 1.f );

	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationX( mat1, 0.3f ) );
	EXPECT_TRUE( rot03 == mat1 );

	mat2 = CcpMath::MatrixRotationX( 0.3f );
	EXPECT_TRUE( rot03 == mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixRotationX( &mat3, 0.3f ) );
	EXPECT_TRUE( rot03 == mat3 );
}

TEST( Matrix, MatrixRotationY ) 
{
	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationY( mat1, 0.f ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat1 ) );

	Matrix mat2 = CcpMath::MatrixRotationY( 0.f );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat2 ) );

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixRotationY( &mat3, 0.f ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat3 ) );

	Matrix rot04(
		0.9210609793663025f, 0.f, -0.3894183337688446f, 0.f, 
		0.f, 1.f, 0.f, 0.f, 
		0.3894183337688446f, 0.f, 0.9210609793663025f, 0.f, 
		0.f, 0.f, 0.f, 1.f );

	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationY( mat1, 0.4f ) );
	EXPECT_TRUE( rot04 == mat1 );

	mat2 = CcpMath::MatrixRotationY( 0.4f );
	EXPECT_TRUE( rot04 == mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixRotationY( &mat3, 0.4f ) );
	EXPECT_TRUE( rot04 == mat3 );
}

TEST( Matrix, MatrixRotationZ ) 
{
	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationZ( mat1, 0.f ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat1 ) );

	Matrix mat2 = CcpMath::MatrixRotationZ( 0.f );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat2 ) );

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixRotationZ( &mat3, 0.f ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat3 ) );

	Matrix rot05(
		0.8775825500488281f, 0.4794255495071411f, 0.f, 0.f, 
		-0.4794255495071411f, 0.8775825500488281f, 0.f, 0.f, 
		0.f, 0.f, 1.f, 0.f, 
		0.f, 0.f, 0.f, 1.f );

	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationZ( mat1, 0.5f ) );
	EXPECT_TRUE( rot05 == mat1 );

	mat2 = CcpMath::MatrixRotationZ( 0.5f );
	EXPECT_TRUE( rot05 == mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixRotationZ( &mat3, 0.5f ) );
	EXPECT_TRUE( rot05 == mat3 );
}

TEST( Matrix, MatrixRotationAxis ) 
{
	Matrix mat1;
	Vector3 axis( 1.f, 2.f, 3.f );
	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationAxis( mat1, axis, 0.f ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat1 ) );

	Matrix mat2 = CcpMath::MatrixRotationAxis( axis, 0.f );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat2 ) );

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixRotationAxis( &mat3, &axis, 0.f ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat3 ) );

	Matrix result(
		0.9585267305374146f, 0.24332378804683685f, -0.148391455411911f, 0.f, 
		-0.23056279122829437f, 0.9680975079536438f, 0.0981225893f, 0.f, 
		0.16753295063972473f, -0.059839606285095215f, 0.9840487241744995f, 0.f, 
		0.f, 0.f, 0.f, 1.f );

	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationAxis( mat1, axis, 0.3f ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixRotationAxis( axis, 0.3f );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixRotationAxis( &mat3, &axis, 0.3f ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixRotationQuaternion ) 
{
	Quaternion q1( 0.f, 0.f, 0.f, 1.f );
	Quaternion q2( 1.f, 2.f, 3.f, 4.f );
	Matrix result(
		-25.0f, 28.0f, -10.0f, 0.0f, 
		-20.0f, -19.0f, 20.0f, 0.0, 
		22.0f, 4.0f, -9.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0 );

	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationQuaternion( mat1, q1 ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat1 ) );

	Matrix mat2 = CcpMath::MatrixRotationQuaternion( q1 );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat2 ) );

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixRotationQuaternion( &mat3, &q1 ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat3 ) );

	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationQuaternion( mat1, q2 ) );
	EXPECT_TRUE( result == mat1 );

	mat2 = CcpMath::MatrixRotationQuaternion( q2 );
	EXPECT_TRUE( result == mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixRotationQuaternion( &mat3, &q2 ) );
	EXPECT_TRUE( result == mat3 );
}

TEST( Matrix, MatrixRotationYawPitchRoll ) 
{
	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationYawPitchRoll( mat1, 0.f, 0.f, 0.f ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat1 ) );

	Matrix mat2 = CcpMath::MatrixRotationYawPitchRoll( 0.f, 0.f, 0.f );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat2 ) );

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixRotationYawPitchRoll( &mat3, 0.f, 0.f, 0.f ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat3 ) );

	Matrix result(
		-0.42691749f, -0.058726668f, 0.90238154f, 0.0f, 
		-0.83373761f, 0.41198230f, -0.36763042f, 0.0f, 
		-0.35017547f, -0.90929741f, -0.22484501f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f );

	EXPECT_EQ( &mat1, &CcpMath::MatrixRotationYawPitchRoll( mat1, 1.f, 2.f, 3.f ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixRotationYawPitchRoll( 1.f, 2.f, 3.f );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixRotationYawPitchRoll( &mat3, 1.f, 2.f, 3.f ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixTransformation ) 
{
	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixTransformation( mat1, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat1 ) );

	Matrix mat2 = CcpMath::MatrixTransformation( nullptr, nullptr, nullptr, nullptr, nullptr, nullptr );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat2 ) );

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixTransformation( &mat3, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat3 ) );

	Vector3 scalingCenter( 1.f, 2.f, 3.f );
	Quaternion scalingRotation( 1.f, 2., 3.f, 4.f );
	Vector3 scaling( 1.f, 2., 3.f );
	Vector3 rotationCenter( 10.f, 2.f, -3.f );
	Quaternion rotation( 4.f, -3.f, 2.f, 3.f );
	Vector3 translation( 10.f, -20.f, 30.f );

	Matrix result(
		-25.0f, -12.0f, 34.0f, 0.0f, 
		-72.0f, -78.0f, 24.0f, 0.0f,
		-6.0f, -108.0f, -147.0f, 0.0f,
		420.0f, 366.0f, -214.0f, 1.0f );

	// We don't test scalingRotation parameter because D3DX  D3DXMatrixTransformation 
	// returns incorrect result when this parameter is used, so we don't know "ground
	// truth" results for calls with this parameter.
	EXPECT_EQ( &mat1, &CcpMath::MatrixTransformation( mat1, &scalingCenter, nullptr, &scaling, &rotationCenter, &rotation, &translation ) );
	EXPECT_TRUE( mat1 == result );

	mat2 = CcpMath::MatrixTransformation( &scalingCenter, nullptr, &scaling, &rotationCenter, &rotation, &translation );
	EXPECT_TRUE( mat2 == result );

	EXPECT_EQ( &mat3, D3DXMatrixTransformation( &mat3, &scalingCenter, nullptr, &scaling, &rotationCenter, &rotation, &translation ) );
	EXPECT_TRUE( mat3 == result );

}

TEST( Matrix, MatrixTransformation2D ) 
{
	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixTransformation2D( mat1, nullptr, 0.0f, nullptr, nullptr, 0.0f, nullptr ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat1 ) );

	Matrix mat2 = CcpMath::MatrixTransformation2D( nullptr, 0.0f, nullptr, nullptr, 0.0f, nullptr );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat2 ) );

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixTransformation2D( &mat3, nullptr, 0.0f, nullptr, nullptr, 0.0f, nullptr ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat3 ) );

	Vector2 scalingCenter( 1.f, 2.f );
	Vector2 scaling( 1.f, 2.f );
	Vector2 rotationCenter( 10.f, 2.f );
	float rotation( 4.f );
	Vector2 translation( 10.f, -20.f );

	Matrix result(
		-0.65364361f, -0.75680250f, 0.0f, 0.0f,
		1.5136050f, -1.3072872f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		23.509226f, -7.8174000f, 0.0f, 1.0f );

	// We don't test scalingRotation parameter because D3DX  D3DXMatrixTransformation2D
	// returns incorrect result when this parameter is used, so we don't know "ground
	// truth" results for calls with this parameter.
	EXPECT_EQ( &mat1, &CcpMath::MatrixTransformation2D( mat1, &scalingCenter, 0.0f, &scaling, &rotationCenter, rotation, &translation ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixTransformation2D( &scalingCenter, 0.0f, &scaling, &rotationCenter, rotation, &translation );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixTransformation2D( &mat3, &scalingCenter, 0.0f, &scaling, &rotationCenter, rotation, &translation ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixAffineTransformation ) 
{
	Matrix mat1;
	EXPECT_EQ( &mat1, &CcpMath::MatrixAffineTransformation( mat1, 1.0f, nullptr, nullptr, nullptr ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat1 ) );

	Matrix mat2 = CcpMath::MatrixAffineTransformation( 1.0f, nullptr, nullptr, nullptr );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat2 ) );

	Matrix mat3;
	EXPECT_EQ( &mat3, D3DXMatrixAffineTransformation( &mat3, 1.0f, nullptr, nullptr, nullptr ) );
	EXPECT_TRUE( CcpMath::MatrixIsIdentity( mat3 ) );

	float scaling( 2.f );
	Vector3 rotationCenter( 10.f, 2.f, -3.f );
	Quaternion rotation( 4.f, -3.f, 2.f, 3.f );
	Vector3 translation( 10.f, -20.f, 30.f );

	Matrix result(
		-50.0f, -24.0f, 68.0f, 0.0f,
		-72.0f, -78.0f, 24.0f, 0.0f,
		-4.0f, -72.0f, -98.0f, 0.0f,
		336.0f, 72.0f, -484.0f, 1.0f );

	EXPECT_EQ( &mat1, &CcpMath::MatrixAffineTransformation( mat1, scaling, &rotationCenter, &rotation, &translation ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixAffineTransformation( scaling, &rotationCenter, &rotation, &translation );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixAffineTransformation( &mat3, scaling, &rotationCenter, &rotation, &translation ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixLookAtRH ) 
{
	Vector3 eye( 1.0f, 2.0f, 3.0f );
	Vector3 at( 4.0f, 5.0f, 6.0f );
	Vector3 up( -1.0f, 2.0f, -3.0f );

	Matrix result(
		-0.81110710f, -0.093658589f, -0.57735026f, 0.00000000f,
		0.32444286f, 0.74926865f, -0.57735026f, 0.00000000f,
		0.48666430f, -0.65561008f, -0.57735026f, 0.00000000f,
		-1.2977715f, 0.56195152f, 3.4641016f, 1.0000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixLookAtRH( mat1, eye, at, up ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixLookAtRH( eye, at, up );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixLookAtRH( &mat3, &eye, &at, &up ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixLookAtLH ) 
{
	Vector3 eye( 1.0f, 2.0f, 3.0f );
	Vector3 at( 4.0f, 5.0f, 6.0f );
	Vector3 up( -1.0f, 2.0f, -3.0f );

	Matrix result(
		0.81110710f, -0.093658589f, 0.57735026f, 0.00000000f,
		-0.32444286f, 0.74926865f, 0.57735026f, 0.00000000f,
		-0.48666430f, -0.65561008f, 0.57735026f, 0.00000000f,
		1.2977715f, 0.56195152f, -3.4641016f, 1.0000000 );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixLookAtLH( mat1, eye, at, up ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixLookAtLH( eye, at, up );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixLookAtLH( &mat3, &eye, &at, &up ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixPerspectiveRH ) 
{
	float w = 123.0f;
	float h = 32.7f;
	float zn = 0.1f;
	float zf = 1000.0f;

	Matrix result(
		0.0016260163f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.0061162077f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.00000000f, -1.0001000f, -1.0000000f,
		0.00000000f, 0.00000000f, -0.10001000f, 0.00000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixPerspectiveRH( mat1, w, h, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixPerspectiveRH( w, h, zn, zf );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixPerspectiveRH( &mat3, w, h, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixPerspectiveLH ) 
{
	float w = 123.0f;
	float h = 32.7f;
	float zn = 0.1f;
	float zf = 1000.0f;

	Matrix result(
		0.0016260163f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.0061162077f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.00000000f, 1.0001000f, 1.0000000f,
		0.00000000f, 0.00000000f, -0.10001000f, 0.00000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixPerspectiveLH( mat1, w, h, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixPerspectiveLH( w, h, zn, zf );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixPerspectiveLH( &mat3, w, h, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixPerspectiveFovRH ) 
{
	float fovy = 0.3f;
	float aspect = 3.0f;
	float zn = 0.1f;
	float zf = 1000.0f;

	Matrix result(
		2.2055304f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, 6.6165910f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.00000000f, -1.0001000f, -1.0000000f,
		0.00000000f, 0.00000000f, -0.10001000f, 0.00000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixPerspectiveFovRH( mat1, fovy, aspect, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixPerspectiveFovRH( fovy, aspect, zn, zf );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixPerspectiveFovRH( &mat3, fovy, aspect, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixPerspectiveFovLH ) 
{
	float fovy = 0.3f;
	float aspect = 3.0f;
	float zn = 0.1f;
	float zf = 1000.0f;

	Matrix result(
		2.2055304f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, 6.6165910f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.00000000f, 1.0001000f, 1.0000000f,
		0.00000000f, 0.00000000f, -0.10001000f, 0.00000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixPerspectiveFovLH( mat1, fovy, aspect, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixPerspectiveFovLH( fovy, aspect, zn, zf );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixPerspectiveFovLH( &mat3, fovy, aspect, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

void MatrixEqualApprox( const Matrix& expected, const Matrix& actual )
{

}

TEST( Matrix, MatrixPerspectiveOffCenterRH ) 
{
	float l = -10.3f;
	float r = 13.0f;
	float t = 2.4f;
	float b = 3.2f;
	float zn = 0.1f;
	float zf = 1000.0f;

	Matrix result(
		0.0085836910f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, -0.25000003f, 0.00000000f, 0.00000000f,
		0.11587982f, -7.0000010f, -1.0001000f, -1.0000000f,
		0.00000000f, 0.00000000f, -0.10001000f, 0.00000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixPerspectiveOffCenterRH( mat1, l, r, b, t, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixPerspectiveOffCenterRH( l, r, b, t, zn, zf );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixPerspectiveOffCenterRH( &mat3, l, r, b, t, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixPerspectiveOffCenterLH ) 
{
	float l = -10.3f;
	float r = 13.0f;
	float t = 2.4f;
	float b = 3.2f;
	float zn = 0.1f;
	float zf = 1000.0f;

	Matrix result(
		0.0085836910f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, -0.25000003f, 0.00000000f, 0.00000000f,
		-0.11587982f, 7.0000010f, 1.0001000f, 1.0000000f,
		0.00000000f, 0.00000000f, -0.10001000f, 0.00000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixPerspectiveOffCenterLH( mat1, l, r, b, t, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixPerspectiveOffCenterLH( l, r, b, t, zn, zf );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixPerspectiveOffCenterLH( &mat3, l, r, b, t, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixOrthoRH ) 
{
	float w = 3.3f;
	float h = 13.0f;
	float zn = 0.1f;
	float zf = 1000.0f;

	Matrix result(
		0.60606062f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.15384616f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.00000000f, -0.0010001000f, 0.00000000f,
		0.00000000f, 0.00000000f, -0.00010001001f, 1.0000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixOrthoRH( mat1, w, h, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixOrthoRH( w, h, zn, zf );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixOrthoRH( &mat3, w, h, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixOrthoLH ) 
{
	float w = 3.3f;
	float h = 13.0f;
	float zn = 0.1f;
	float zf = 1000.0f;

	Matrix result(
		0.60606062f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.15384616f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.00000000f, 0.0010001000f, 0.00000000f,
		0.00000000f, 0.00000000f, -0.00010001001f, 1.0000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixOrthoLH( mat1, w, h, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixOrthoLH( w, h, zn, zf );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixOrthoLH( &mat3, w, h, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixOrthoOffCenterRH ) 
{
	float l = -10.3f;
	float r = 13.0f;
	float t = 2.4f;
	float b = 3.2f;
	float zn = 0.1f;
	float zf = 1000.0f;

	Matrix result(
		0.085836910f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, -2.5000002f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.00000000f, -0.0010001000f, 0.00000000f,
		-0.11587982f, 7.0000010f, -0.00010001001f, 1.0000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixOrthoOffCenterRH( mat1, l, r, b, t, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixOrthoOffCenterRH( l, r, b, t, zn, zf );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixOrthoOffCenterRH( &mat3, l, r, b, t, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixOrthoOffCenterLH ) 
{
	float l = -10.3f;
	float r = 13.0f;
	float t = 2.4f;
	float b = 3.2f;
	float zn = 0.1f;
	float zf = 1000.0f;

	Matrix result(
		0.085836910f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, -2.5000002f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.00000000f, 0.0010001000f, 0.00000000f,
		-0.11587982f, 7.0000010f, -0.00010001001f, 1.0000000f );

	Matrix mat1, mat2, mat3;
	EXPECT_EQ( &mat1, &CcpMath::MatrixOrthoOffCenterLH( mat1, l, r, b, t, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat1 );

	mat2 = CcpMath::MatrixOrthoOffCenterLH( l, r, b, t, zn, zf );
	EXPECT_MATRIX_EQ( result, mat2 );

	EXPECT_EQ( &mat3, D3DXMatrixOrthoOffCenterLH( &mat3, l, r, b, t, zn, zf ) );
	EXPECT_MATRIX_EQ( result, mat3 );
}

TEST( Matrix, MatrixDecompose ) 
{
	Matrix id = CcpMath::MatrixIdentity();
	Vector3 scale1, translation1;
	Quaternion rotation1;
	CcpMath::MatrixDecompose( scale1, rotation1, translation1, id );
	EXPECT_TRUE( scale1 == Vector3( 1.0f, 1.0f, 1.0f ) );
	EXPECT_TRUE( translation1 == Vector3( 0.0f, 0.0f, 0.0f ) );
	EXPECT_TRUE( rotation1 == Quaternion( 0.0f, 0.0f, 0.0f, 1.0f ) );

	Vector3 scale2, translation2;
	Quaternion rotation2;
	D3DXMatrixDecompose( &scale2, &rotation2, &translation2, &id );
	EXPECT_TRUE( scale2 == Vector3( 1.0f, 1.0f, 1.0f ) );
	EXPECT_TRUE( translation2 == Vector3( 0.0f, 0.0f, 0.0f ) );
	EXPECT_TRUE( rotation2 == Quaternion( 0.0f, 0.0f, 0.0f, 1.0f ) );
}

TEST( Matrix, MatrixReflect ) 
{
	Plane plane( -3.0f, -1.0f, 4.0f, 7.0f );
	Matrix expected;
    expected.m[0][0] = 0.3076923f; expected.m[0][1] = -0.2307692f; expected.m[0][2] = 0.923077f; expected.m[0][3] = 0.0f;
    expected.m[1][0] = -0.2307692f; expected.m[1][1] = 0.923077f; expected.m[1][2] = 0.3076923f; expected.m[1][3] = 0.0f;
    expected.m[2][0] = 0.923077f; expected.m[2][1] = 0.3076923f; expected.m[2][2] = -0.2307692f; expected.m[2][3] = 0.0f;
    expected.m[3][0] = 1.615385f; expected.m[3][1] = 0.5384615f; expected.m[3][2] = -2.153846f; expected.m[3][3] = 1.0f;

	Matrix out;
    EXPECT_EQ( &out, D3DXMatrixReflect( &out, &plane ) );
    EXPECT_MATRIX_EQ( expected, out );
}

TEST( Matrix, MatrixShadow ) 
{
	Plane plane( -3.0f, -1.0f, 4.0f, 7.0f );
	Vector4 light( 9.6f, 8.5f, 7.4f, 6.3f );
	Matrix expected;
    expected.m[0][0] = 12.786773f; expected.m[0][1] = 5.000961f; expected.m[0][2] = 4.353778f; expected.m[0][3] = 3.706595f;
    expected.m[1][0] = 1.882715f;  expected.m[1][1] = 8.805615f; expected.m[1][2] = 1.451259f; expected.m[1][3] = 1.235532f;
    expected.m[2][0] = -7.530860f; expected.m[2][1] = -6.667949f; expected.m[2][2] = 1.333590f; expected.m[2][3] = -4.942127f;
    expected.m[3][0] = -13.179006f; expected.m[3][1] = -11.668910f; expected.m[3][2] = -10.158816f; expected.m[3][3] = -1.510094f;

	Matrix out;
    EXPECT_EQ( &out, D3DXMatrixShadow( &out, &light, &plane ) );
    EXPECT_MATRIX_EQ( expected, out );
}
