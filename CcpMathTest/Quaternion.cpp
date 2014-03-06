#include "CcpFloat.h"
#include "gtest/gtest.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <cstdint>
#include <cfloat>
#include "CcpMath/include/Quaternion.h"
#include "CcpMath/include/Vector3.h"
#include "CcpMath/include/Matrix.h"

#define EXPECT_QUATERNION_EQ( expected, actual )			\
	{														\
		EXPECT_FLOAT_EQ( ( expected ).x, ( actual ).x );	\
		EXPECT_FLOAT_EQ( ( expected ).y, ( actual ).y );	\
		EXPECT_FLOAT_EQ( ( expected ).z, ( actual ).z );	\
		EXPECT_FLOAT_EQ( ( expected ).w, ( actual ).w );	\
	}

TEST( Quaternion, Constructors ) 
{
	Quaternion q1( 1.f, 2.f, 3.f, 4.f );
	EXPECT_EQ( 1.f, q1.x );
	EXPECT_EQ( 2.f, q1.y );
	EXPECT_EQ( 3.f, q1.z );
	EXPECT_EQ( 4.f, q1.w );

	Quaternion q2( q1 );
	EXPECT_EQ( 1.f, q2.x );
	EXPECT_EQ( 2.f, q2.y );
	EXPECT_EQ( 3.f, q2.z );
	EXPECT_EQ( 4.f, q2.w );

	float args[] = { 1.f, 2.f, 3.f, 4.f };
	Quaternion q3( args );
	EXPECT_EQ( 1.f, q3.x );
	EXPECT_EQ( 2.f, q3.y );
	EXPECT_EQ( 3.f, q3.z );
	EXPECT_EQ( 4.f, q3.w );
}

TEST( Quaternion, CastToFloatArray ) 
{
	const Quaternion q1( 1.f, 2.f, 3.f, 4.f );
	const float* array1( q1 );
	EXPECT_EQ( 1.f, array1[0] );
	EXPECT_EQ( 2.f, array1[1] );
	EXPECT_EQ( 3.f, array1[2] );
	EXPECT_EQ( 4.f, array1[3] );

	Quaternion q2( 1.f, 2.f, 3.f, 4.f );
	float* array2( q2 );
	EXPECT_EQ( 1.f, array2[0] );
	EXPECT_EQ( 2.f, array2[1] );
	EXPECT_EQ( 3.f, array2[2] );
	EXPECT_EQ( 4.f, array2[3] );
}

TEST( Quaternion, Additions ) 
{
	Quaternion a( 1.f, 2.f, 3.f, 4.f );
	Quaternion b( 4.f, 5.f, 6.f, 7.f );

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

	Quaternion c = a + b;
	EXPECT_EQ( 14.f, c.x );
	EXPECT_EQ( 19.f, c.y );
	EXPECT_EQ( 24.f, c.z );
	EXPECT_EQ( 29.f, c.w );
}

TEST( Quaternion, Subtractions ) 
{
	Quaternion a( 12.f, 23.f, 4.f, 45.f );
	Quaternion b( 4.f, 5.f, 6.f, 7.f );

	a -= b;
	EXPECT_EQ( 8.f, a.x );
	EXPECT_EQ( 18.f, a.y );
	EXPECT_EQ( -2.f, a.z );
	EXPECT_EQ( 38.f, a.w );

	Quaternion c = a - b;
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

TEST( Quaternion, Scaling ) 
{
	Quaternion a( 1.f, 2.f, 3.f, 4.f );

	a *= 0.5f;
	EXPECT_EQ( 0.5f, a.x );
	EXPECT_EQ( 1.f, a.y );
	EXPECT_EQ( 1.5f, a.z );
	EXPECT_EQ( 2.f, a.w );

	Quaternion b = a * -10.f;
	EXPECT_EQ( -5.f, b.x );
	EXPECT_EQ( -10.f, b.y );
	EXPECT_EQ( -15.f, b.z );
	EXPECT_EQ( -20.f, b.w );

	b /= -2.f;
	EXPECT_EQ( 2.5f, b.x );
	EXPECT_EQ( 5.f, b.y );
	EXPECT_EQ( 7.5f, b.z );
	EXPECT_EQ( 10.f, b.w );

	Quaternion c = b / 0.1f;
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

	Quaternion d( 3.f * a );
	EXPECT_EQ( 1.5f, d.x );
	EXPECT_EQ( 3.f, d.y );
	EXPECT_EQ( 4.5f, d.z );
	EXPECT_EQ( 6.f, d.w );
}

TEST( Quaternion, Signs ) 
{
	Quaternion a( 1.f, 2.f, 3.f, 4.f );

	Quaternion b( +a );
	EXPECT_EQ( 1.f, b.x );
	EXPECT_EQ( 2.f, b.y );
	EXPECT_EQ( 3.f, b.z );
	EXPECT_EQ( 4.f, b.w );

	Quaternion c( -a );
	EXPECT_EQ( -1.f, c.x );
	EXPECT_EQ( -2.f, c.y );
	EXPECT_EQ( -3.f, c.z );
	EXPECT_EQ( -4.f, c.w );
}

TEST( Quaternion, Comparisons ) 
{
	EXPECT_TRUE( Quaternion( 1.f, 2.f, 3.f, 4.f ) == Quaternion( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_FALSE( Quaternion( 1.f, 2.f, 3.f, 4.f ) == Quaternion( 3.f, 2.f, 3.f, 4.f ) );
	EXPECT_FALSE( Quaternion( 1.f, 2.f, 3.f, 4.f ) == Quaternion( 1.f, 0.f, 3.f, 4.f ) );
	EXPECT_FALSE( Quaternion( 1.f, 2.f, 3.f, 4.f ) == Quaternion( 1.f, 2.f, 0.f, 4.f ) );
	EXPECT_FALSE( Quaternion( 1.f, 0.f, 3.f, 4.f ) == Quaternion( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_FALSE( Quaternion( 1.f, 0.f, 3.f, 4.f ) == Quaternion( 1.f, 2.f, 3.f, 5.f ) );

	EXPECT_FALSE( Quaternion( 1.f, 2.f, 3.f, 4.f ) != Quaternion( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_TRUE( Quaternion( 1.f, 2.f, 3.f, 4.f ) != Quaternion( 3.f, 2.f, 3.f, 4.f ) );
	EXPECT_TRUE( Quaternion( 1.f, 2.f, 3.f, 4.f ) != Quaternion( 1.f, 0.f, 3.f, 4.f ) );
	EXPECT_TRUE( Quaternion( 1.f, 2.f, 3.f, 4.f ) != Quaternion( 1.f, 2.f, 0.f, 4.f ) );
	EXPECT_TRUE( Quaternion( 1.f, 0.f, 3.f, 4.f ) != Quaternion( 1.f, 2.f, 3.f, 4.f ) );
	EXPECT_TRUE( Quaternion( 1.f, 0.f, 3.f, 4.f ) != Quaternion( 1.f, 2.f, 3.f, 5.f ) );
}

TEST( Quaternion, Multiplication ) 
{
	Quaternion q1( 1.f, 2.f, 3.f, 4.f );
	Quaternion q2( 2.4f, 7.1f, -3.1f, 0.2f );
	Quaternion result(37.2999992f, 18.4999981f, -14.0999994f, -6.50000095f);

	Quaternion q3;
	EXPECT_EQ( &q3, &CcpMath::QuaternionMultiply( q3, q1, q2 ) );
	EXPECT_TRUE( q3 == result );

	Quaternion q4 = CcpMath::QuaternionMultiply( q1, q2 );
	EXPECT_TRUE( q4 == result );

	Quaternion q5 = q1 * q2;
	EXPECT_TRUE( q5 == result );

	Quaternion q6 = q1;
	q6 *= q2;
	EXPECT_TRUE( q6 == result );

	Quaternion q7;
	EXPECT_EQ( &q7, D3DXQuaternionMultiply( &q7, &q1, &q2 ) );
	EXPECT_TRUE( q7 == result );
}

TEST( Quaternion, QuaternionLength ) 
{
	Quaternion q1( 1.f, 2.f, 3.f, 4.f );
	EXPECT_EQ( 5.477225575051661f, CcpMath::QuaternionLength( q1 ) );
	EXPECT_EQ( 5.477225575051661f, D3DXQuaternionLength( &q1 ) );

	Quaternion q2( 0.f, 0.f, 0.f, 0.f );
	EXPECT_EQ( 0.0f, CcpMath::QuaternionLength( q2 ) );
	EXPECT_EQ( 0.0f, D3DXQuaternionLength( &q2 ) );
}

TEST( Quaternion, QuaternionDot ) 
{
	Quaternion q1( 1.f, 2.f, 3.f, 4.f );
	Quaternion q2( 2.4f, 7.1f, -3.1f, 0.2f );
	EXPECT_FLOAT_EQ( 8.100000381469727f, CcpMath::QuaternionDot( q1, q2 ) );
	EXPECT_FLOAT_EQ( 8.100000381469727f, D3DXQuaternionDot( &q1, &q2 ) );

	Quaternion q3( 0.f, 0.f, 0.f, 0.f );
	EXPECT_EQ( 0.0f, CcpMath::QuaternionDot( q2, q3 ) );
	EXPECT_EQ( 0.0f, D3DXQuaternionDot( &q3, &q2 ) );
}

TEST( Quaternion, QuaternionIdentity ) 
{
	Quaternion q1;
	EXPECT_EQ( &q1, &CcpMath::QuaternionIdentity( q1 ) );
	EXPECT_TRUE( q1 == Quaternion( 0.0f, 0.0f, 0.0f, 1.0f ) );

	EXPECT_TRUE( CcpMath::QuaternionIdentity() == Quaternion( 0.0f, 0.0f, 0.0f, 1.0f ) );

	Quaternion q2;
	EXPECT_EQ( &q2, D3DXQuaternionIdentity( &q2 ) );
	EXPECT_TRUE( q2 == Quaternion( 0.0f, 0.0f, 0.0f, 1.0f ) );
}

TEST( Quaternion, QuaternionIsIdentity ) 
{
	Quaternion q1( 0.0f, 0.0f, 0.0f, 1.0f );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q1 ) );
	EXPECT_TRUE( D3DXQuaternionIsIdentity( &q1 ) );

	Quaternion q2( 1.0f, 1.0f, 1.0f, 1.0f );
	EXPECT_FALSE( CcpMath::QuaternionIsIdentity( q2 ) );
	EXPECT_FALSE( D3DXQuaternionIsIdentity( &q2 ) );

	Quaternion q3( 0.0f, 0.0f, 0.0f, 1.00001f );
	EXPECT_FALSE( CcpMath::QuaternionIsIdentity( q3 ) );
	EXPECT_FALSE( D3DXQuaternionIsIdentity( &q3 ) );
}

TEST( Quaternion, QuaternionConjugate ) 
{
	Quaternion q1( 1.0f, -2.0f, 3.0f, 4.0f );
	Quaternion result( -1.0f, 2.0f, -3.0f, 4.0f );

	Quaternion q2;
	EXPECT_EQ( &q2, &CcpMath::QuaternionConjugate( q2, q1 ) );
	EXPECT_TRUE( q2 == result );

	Quaternion q3 = CcpMath::QuaternionConjugate( q1 );
	EXPECT_TRUE( q3 == result );

	Quaternion q4;
	EXPECT_EQ( &q4, D3DXQuaternionConjugate( &q4, &q1 ) );
	EXPECT_TRUE( q4 == result );
}

TEST( Quaternion, QuaternionToAxisAngle ) 
{
	Quaternion q1( 0.18257418274879456f, 0.3651483654975891f, 0.5477225184440613f, 0.7302967309951782f );
	Vector3 axis( 0.18257418274879456f, 0.3651483654975891f, 0.5477225184440613f );
	float angle( 0.7520401072636285f );

	Vector3 v1;
	float a1;
	CcpMath::QuaternionToAxisAngle( q1, v1, a1 );
	EXPECT_TRUE( v1 == axis );
	EXPECT_EQ( angle, a1 );

	Vector3 v2;
	float a2;
	D3DXQuaternionToAxisAngle( &q1, &v2, &a2 );
	EXPECT_TRUE( v2 == axis );
	EXPECT_EQ( angle, a2 );
}

TEST( Quaternion, QuaternionRotationMatrix ) 
{
	Matrix id = CcpMath::MatrixIdentity();

	Quaternion q1;
	EXPECT_EQ( &q1, &CcpMath::QuaternionRotationMatrix( q1, id ) );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q1 ) );

	Quaternion q2 = CcpMath::QuaternionRotationMatrix( id );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q2 ) );

	Quaternion q3;
	EXPECT_EQ( &q3, D3DXQuaternionRotationMatrix( &q3, &id ) );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q3 ) );

	Matrix m = CcpMath::MatrixRotationX( 0.5f );
	Quaternion result( 0.24740396f, 0.00000000f, 0.00000000f, 0.96891242f );

	EXPECT_EQ( &q1, &CcpMath::QuaternionRotationMatrix( q1, m ) );
	EXPECT_TRUE( result == q1 );

	q2 = CcpMath::QuaternionRotationMatrix( m );
	EXPECT_TRUE( result == q2 );

	EXPECT_EQ( &q3, D3DXQuaternionRotationMatrix( &q3, &m ) );
	EXPECT_TRUE( result == q3 );
}

TEST( Quaternion, QuaternionRotationAxis ) 
{
	Vector3 axis( 1.f, 2.f, 3.f );

	Quaternion q1;
	EXPECT_EQ( &q1, &CcpMath::QuaternionRotationAxis( q1, axis, 0.0f ) );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q1 ) );

	Quaternion q2 = CcpMath::QuaternionRotationAxis( axis, 0.0f );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q2 ) );

	Quaternion q3;
	EXPECT_EQ( &q3, D3DXQuaternionRotationAxis( &q3, &axis, 0.0f ) );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q3 ) );

	float angle = 0.5f;
	Quaternion result( 0.066121489f, 0.13224298f, 0.19836447f, 0.96891242f );

	EXPECT_EQ( &q1, &CcpMath::QuaternionRotationAxis( q1, axis, angle ) );
	EXPECT_QUATERNION_EQ( result, q1 );

	q2 = CcpMath::QuaternionRotationAxis( axis, angle );
	EXPECT_QUATERNION_EQ( result, q2 );

	EXPECT_EQ( &q3, D3DXQuaternionRotationAxis( &q3, &axis, angle ) );
	EXPECT_QUATERNION_EQ( result, q3 );
}

TEST( Quaternion, QuaternionRotationYawPitchRoll ) 
{
	Quaternion q1;
	EXPECT_EQ( &q1, &CcpMath::QuaternionRotationYawPitchRoll( q1, 0.0f, 0.0f, 0.0f ) );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q1 ) );

	Quaternion q2 = CcpMath::QuaternionRotationYawPitchRoll( 0.0f, 0.0f, 0.0f );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q2 ) );

	Quaternion q3;
	EXPECT_EQ( &q3, D3DXQuaternionRotationYawPitchRoll( &q3, 0.0f, 0.0f, 0.0f ) );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q3 ) );

	float yaw = 0.5f;
	float pitch = 0.6f;
	float roll = 0.7f;
	Quaternion result( 0.350018859f, 0.123841502f, 0.248718783f, 0.894588768f );

	EXPECT_EQ( &q1, &CcpMath::QuaternionRotationYawPitchRoll( q1, yaw, pitch, roll ) );
	EXPECT_TRUE( result == q1 );

	q2 = CcpMath::QuaternionRotationYawPitchRoll( yaw, pitch, roll );
	EXPECT_TRUE( result == q2 );

	EXPECT_EQ( &q3, D3DXQuaternionRotationYawPitchRoll( &q3, yaw, pitch, roll ) );
	EXPECT_TRUE( result == q3 );
}

TEST( Quaternion, QuaternionNormalize ) 
{
	Quaternion q( 1.f, 2.f, 3.f, 4.f );
	Quaternion result( 0.18257418f, 0.36514837f, 0.54772258f, 0.73029673f );

	Quaternion q1;
	EXPECT_EQ( &q1, &CcpMath::QuaternionNormalize( q1, q ) );
	EXPECT_TRUE( result == q1 );

	Quaternion q2 = CcpMath::QuaternionNormalize( q );
	EXPECT_TRUE( result == q2 );

	Quaternion q3;
	EXPECT_EQ( &q3, D3DXQuaternionNormalize( &q3, &q ) );
	EXPECT_TRUE( result == q3 );
}

TEST( Quaternion, QuaternionInverse ) 
{
	Quaternion id = CcpMath::QuaternionIdentity();

	Quaternion q1;
	EXPECT_EQ( &q1, &CcpMath::QuaternionInverse( q1, id ) );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q1 ) );

	Quaternion q2 = CcpMath::QuaternionInverse( id );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q2 ) );

	Quaternion q3;
	EXPECT_EQ( &q3, D3DXQuaternionInverse( &q3, &id ) );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q3 ) );

	Quaternion q( 1.f, 2.f, 3.f, 4.f );
	Quaternion result( -0.033333331f, -0.066666663f, -0.099999994f, 0.13333333f );

	EXPECT_EQ( &q1, &CcpMath::QuaternionInverse( q1, q ) );
	EXPECT_QUATERNION_EQ( result, q1 );

	q2 = CcpMath::QuaternionInverse( q );
	EXPECT_QUATERNION_EQ( result, q2 );

	EXPECT_EQ( &q3, D3DXQuaternionInverse( &q3, &q ) );
	EXPECT_QUATERNION_EQ( result, q3 );
}

TEST( Quaternion, QuaternionLn ) 
{
	Quaternion id = CcpMath::QuaternionIdentity();
	Quaternion zero( 0.0f, 0.0f, 0.0f, 0.0f );

	Quaternion q1;
	EXPECT_EQ( &q1, &CcpMath::QuaternionLn( q1, id ) );
	EXPECT_TRUE( zero == q1 );

	Quaternion q2 = CcpMath::QuaternionLn( id );
	EXPECT_TRUE( zero == q2 );

	Quaternion q3;
	EXPECT_EQ( &q3, D3DXQuaternionLn( &q3, &id ) );
	EXPECT_TRUE( zero == q3 );

	Quaternion normalized( 0.18257417f, 0.36514834f, 0.54772252f, 0.73029667f );
	Quaternion normalizedLn( 0.20099114f, 0.40198228f, 0.60297346f, 0.0f );

	EXPECT_EQ( &q1, &CcpMath::QuaternionLn( q1, normalized ) );
	EXPECT_QUATERNION_EQ( normalizedLn, q1 );

	q2 = CcpMath::QuaternionLn( normalized );
	EXPECT_QUATERNION_EQ( normalizedLn, q2 );

	EXPECT_EQ( &q3, D3DXQuaternionLn( &q3, &normalized ) );
	EXPECT_QUATERNION_EQ( normalizedLn, q3 );

	Quaternion greaterThanOne( 1.f, 2.f, 3.f, 4.f );
	Quaternion greaterThanOneLn( 1.f, 2.f, 3.f, 0.0f );

	EXPECT_EQ( &q1, &CcpMath::QuaternionLn( q1, greaterThanOne ) );
	EXPECT_QUATERNION_EQ( greaterThanOneLn, q1 );

	q2 = CcpMath::QuaternionLn( greaterThanOne );
	EXPECT_QUATERNION_EQ( greaterThanOneLn, q2 );

	EXPECT_EQ( &q3, D3DXQuaternionLn( &q3, &greaterThanOne ) );
	EXPECT_QUATERNION_EQ( greaterThanOneLn, q3 );

	// We don't test for quaternions of length less than one as D3DX has some
	// magical behavior there.
}

TEST( Quaternion, QuaternionExp ) 
{
	Quaternion zero( 0.0f, 0.0f, 0.0f, 0.0f );

	Quaternion q1;
	EXPECT_EQ( &q1, &CcpMath::QuaternionExp( q1, zero ) );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q1 ) );

	Quaternion q2 = CcpMath::QuaternionExp( zero );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q2 ) );

	Quaternion q3;
	EXPECT_EQ( &q3, D3DXQuaternionExp( &q3, &zero ) );
	EXPECT_TRUE( CcpMath::QuaternionIsIdentity( q3 ) );

	Quaternion example( 1.f, 2.f, 3.f, 0.0f );
	Quaternion exampleExp( -0.15092136f, -0.30184272f, -0.45276409f, -0.82529902f );

	EXPECT_EQ( &q1, &CcpMath::QuaternionExp( q1, example ) );
	EXPECT_QUATERNION_EQ( exampleExp, q1 );

	q2 = CcpMath::QuaternionExp( example );
	EXPECT_QUATERNION_EQ( exampleExp, q2 );

	EXPECT_EQ( &q3, D3DXQuaternionExp( &q3, &example ) );
	EXPECT_QUATERNION_EQ( exampleExp, q3 );
}

TEST( Quaternion, D3DXQuaternionSlerp ) 
{
	Quaternion a = CcpMath::QuaternionNormalize( Quaternion( 1.0f, 2.0f, 3.0f, 4.0f ) );
	Quaternion b = CcpMath::QuaternionNormalize( Quaternion( 0.4f, -0.3f, 0.2f, 0.1f ) );

	Quaternion q1, q2, q3;

	EXPECT_EQ( &q1, &CcpMath::QuaternionSlerp( q1, a, b, 0.0f ) );
	EXPECT_QUATERNION_EQ( a, q1 );

	q2 = CcpMath::QuaternionSlerp( a, b, 0.0f );
	EXPECT_QUATERNION_EQ( q2, a );
	
	EXPECT_EQ( &q3, D3DXQuaternionSlerp( &q3, &a, &b, 0.0f ) );
	EXPECT_QUATERNION_EQ( a, q3 );

	EXPECT_EQ( &q1, &CcpMath::QuaternionSlerp( q1, a, b, 1.0f ) );
	EXPECT_QUATERNION_EQ( b, q1 );

	q2 = CcpMath::QuaternionSlerp( a, b, 1.0f );
	EXPECT_QUATERNION_EQ( b, q2 );
	
	EXPECT_EQ( &q3, D3DXQuaternionSlerp( &q3, &a, &b, 1.0f ) );
	EXPECT_QUATERNION_EQ( b, q3 );

	Quaternion half( 0.57353938f, -0.11470790f, 0.57353932f, 0.57353932f );

	EXPECT_EQ( &q1, &CcpMath::QuaternionSlerp( q1, a, b, 0.5f ) );
	EXPECT_QUATERNION_EQ( half, q1 );

	q2 = CcpMath::QuaternionSlerp( a, b, 0.5f );
	EXPECT_QUATERNION_EQ( half, q2 );
	
	EXPECT_EQ( &q3, D3DXQuaternionSlerp( &q3, &a, &b, 0.5f ) );
	EXPECT_QUATERNION_EQ( half, q3 );
}

TEST( Quaternion, QuaternionSquad ) 
{
	Quaternion a = CcpMath::QuaternionNormalize( Quaternion( 1.0f, 2.0f, 3.0f, 4.0f ) );
	Quaternion b = CcpMath::QuaternionNormalize( Quaternion( 0.4f, -0.3f, 0.2f, 0.1f ) );
	Quaternion c = CcpMath::QuaternionNormalize( Quaternion( 10.4f, 1.3f, -4.2f, 0.3f ) );
	Quaternion d = CcpMath::QuaternionNormalize( Quaternion( 1.4f, 0.7f, 1.2f, -0.7f ) );

	Quaternion q1, q2, q3;

	EXPECT_EQ( &q1, &CcpMath::QuaternionSquad( q1, a, b, c, d, 0.0f ) );
	EXPECT_QUATERNION_EQ( a, q1 );

	q2 = CcpMath::QuaternionSquad( a, b, c, d, 0.0f );
	EXPECT_QUATERNION_EQ( a, q2 );
	
	EXPECT_EQ( &q3, D3DXQuaternionSquad( &q3, &a, &b, &c, &d, 0.0f ) );
	EXPECT_QUATERNION_EQ( a, q3 );

	EXPECT_EQ( &q1, &CcpMath::QuaternionSquad( q1, a, b, c, d, 1.0f ) );
	EXPECT_QUATERNION_EQ( d, q1 );

	q2 = CcpMath::QuaternionSquad( a, b, c, d, 1.0f );
	EXPECT_QUATERNION_EQ( d, q2 );
	
	EXPECT_EQ( &q3, D3DXQuaternionSquad( &q3, &a, &b, &c, &d, 1.0f ) );
	EXPECT_QUATERNION_EQ( d, q3 );
}

TEST( Quaternion, QuaternionSquadSetup ) 
{
	Quaternion a = CcpMath::QuaternionNormalize( Quaternion( 1.0f, 2.0f, 3.0f, 4.0f ) );
	Quaternion b = CcpMath::QuaternionNormalize( Quaternion( 0.4f, -0.3f, 0.2f, 0.1f ) );
	Quaternion c = CcpMath::QuaternionNormalize( Quaternion( 10.4f, 1.3f, -4.2f, 0.3f ) );
	Quaternion d = CcpMath::QuaternionNormalize( Quaternion( 1.4f, 0.7f, 1.2f, -0.7f ) );

	Quaternion result1( 0.50800782f, -0.78553301f, 0.35136759f, -0.03750813f );
	Quaternion result2( 0.66406322f, 0.19605064f, -0.71727610f, 0.078097314f );
	Quaternion result3( 0.92075068f, 0.11509383f, -0.37184161f, 0.026560118f );

	Quaternion q1, q2, q3;

	CcpMath::QuaternionSquadSetup( q1, q2, q3, a, b, c, d );
	EXPECT_QUATERNION_EQ( result1, q1 );
	EXPECT_QUATERNION_EQ( result2, q2 );
	EXPECT_QUATERNION_EQ( result3, q3 );
}
