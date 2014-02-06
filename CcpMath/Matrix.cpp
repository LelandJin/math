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
#include "include/Matrix.h"
#include "include/Quaternion.h"
#include "include/Vector2.h"
#include "include/Vector4.h"
#include "include/Plane.h"

Matrix::Matrix( const float *elements )
	:_11( elements[0] ),
	_12( elements[1] ),
	_13( elements[2] ),
	_14( elements[3] ),
	_21( elements[4] ),
	_22( elements[5] ),
	_23( elements[6] ),
	_24( elements[7] ),
	_31( elements[8] ),
	_32( elements[9] ),
	_33( elements[10] ),
	_34( elements[11] ),
	_41( elements[12] ),
	_42( elements[13] ),
	_43( elements[14] ),
	_44( elements[15] )
{
}
	
Matrix::Matrix( 
	float v11, float v12, float v13, float v14,
	float v21, float v22, float v23, float v24,
	float v31, float v32, float v33, float v34,
	float v41, float v42, float v43, float v44 )
	:_11( v11 ),
	_12( v12 ),
	_13( v13 ),
	_14( v14 ),
	_21( v21 ),
	_22( v22 ),
	_23( v23 ),
	_24( v24 ),
	_31( v31 ),
	_32( v32 ),
	_33( v33 ),
	_34( v34 ),
	_41( v41 ),
	_42( v42 ),
	_43( v43 ),
	_44( v44 )
{
}

float& Matrix::operator () ( uint32_t Row, uint32_t Col )
{
	return m[Row][Col];
}

float Matrix::operator () ( uint32_t Row, uint32_t Col ) const
{
	return m[Row][Col];
}

const Matrix operator*( float f, const Matrix& other )
{
	return Matrix( other ) * f;
}

// ----------------------------------------------------------------------------------
// Description
//   Multiplication-assignment operator
// Arguments:
//   other - The Matrix by which to multiply this Matrix
// Return Value:
//   This Matrix, after multiplying by the other Matrix
// ----------------------------------------------------------------------------------
Matrix& Matrix::operator*=( const Matrix& other )
{
	return CcpMath::MatrixMultiply( *this, *this, other );
}


Matrix& CcpMath::MatrixIdentity( Matrix& out )
{
	out._11 = 1.f; out._12 = 0.f; out._13 = 0.f; out._14 = 0.f;
	out._21 = 0.f; out._22 = 1.f; out._23 = 0.f; out._24 = 0.f;
	out._31 = 0.f; out._32 = 0.f; out._33 = 1.f; out._34 = 0.f;
	out._41 = 0.f; out._42 = 0.f; out._43 = 0.f; out._44 = 1.f;
	return out;
}

Matrix CcpMath::MatrixIdentity()
{
	Matrix out;
	return MatrixIdentity( out );
}

bool CcpMath::MatrixIsIdentity( const Matrix& m )
{
	return 
		m._11 == 1.f && m._12 == 0.f && m._13 == 0.f && m._14 == 0.f &&
		m._21 == 0.f && m._22 == 1.f && m._23 == 0.f && m._24 == 0.f &&
		m._31 == 0.f && m._32 == 0.f && m._33 == 1.f && m._34 == 0.f &&
		m._41 == 0.f && m._42 == 0.f && m._43 == 0.f && m._44 == 1.f;
}

float CcpMath::MatrixDeterminant( const Matrix& m )
{
    float a0 = m._11 * m._22 - m._12 * m._21;
    float a1 = m._11 * m._23 - m._13 * m._21;
    float a2 = m._11 * m._24 - m._14 * m._21;
    float a3 = m._12 * m._23 - m._13 * m._22;
    float a4 = m._12 * m._24 - m._14 * m._22;
    float a5 = m._13 * m._24 - m._14 * m._23;
    float b0 = m._31 * m._42 - m._32 * m._41;
    float b1 = m._31 * m._43 - m._33 * m._41;
    float b2 = m._31 * m._44 - m._34 * m._41;
    float b3 = m._32 * m._43 - m._33 * m._42;
    float b4 = m._32 * m._44 - m._34 * m._42;
    float b5 = m._33 * m._44 - m._34 * m._43;
    return a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
}

Matrix& CcpMath::MatrixTranspose( Matrix& out, const Matrix& m )
{
	if( &out != &m )
	{
		out._11 = m._11; out._12 = m._21; out._13 = m._31; out._14 = m._41;
		out._21 = m._12; out._22 = m._22; out._23 = m._32; out._24 = m._42;
		out._31 = m._13; out._32 = m._23; out._33 = m._33; out._34 = m._43;
		out._41 = m._14; out._42 = m._24; out._43 = m._34; out._44 = m._44;
	}
	else
	{
		out = MatrixTranspose( m );
	}
	return out;
}

Matrix CcpMath::MatrixTranspose( const Matrix& m )
{
	Matrix out;
	return MatrixTranspose( out, m );
}

Matrix& CcpMath::MatrixMultiply( Matrix& out, const Matrix& m1, const Matrix& m2 )
{
	if( &out != &m1 && &out != &m2 )
	{
		for( int i = 0; i < 4; ++i )
		{
			for( int j = 0; j < 4; ++j )
			{
				out.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] + m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
			}
		}
	}
	else
	{
		out = MatrixMultiply( m1, m2 );
	}
	return out;
}

Matrix CcpMath::MatrixMultiply( const Matrix& m1, const Matrix& m2 )
{
	Matrix out;
	return MatrixMultiply( out, m1, m2 );
}

inline void Vec4Cross( Vector4& out, const Vector4& v1, const Vector4& v2, const Vector4& v3 )
{
    out.x = v1.y * ( v2.z * v3.w - v3.z * v2.w ) - v1.z * ( v2.y * v3.w - v3.y * v2.w ) + v1.w * ( v2.y * v3.z - v2.z *v3.y );
    out.y = -( v1.x * ( v2.z * v3.w - v3.z * v2.w ) - v1.z * ( v2.x * v3.w - v3.x * v2.w ) + v1.w * ( v2.x * v3.z - v3.x * v2.z ) );
    out.z = v1.x * ( v2.y * v3.w - v3.y * v2.w ) - v1.y * ( v2.x *v3.w - v3.x * v2.w ) + v1.w * ( v2.x * v3.y - v3.x * v2.y );
    out.w = -( v1.x * ( v2.y * v3.z - v3.y * v2.z ) - v1.y * ( v2.x * v3.z - v3.x *v2.z ) + v1.z * ( v2.x * v3.y - v3.x * v2.y ) );
}

Matrix& CcpMath::MatrixInverse( Matrix& out, float& determinant, const Matrix& m )
{
	if( &out == &m )
	{
		out = MatrixInverse( determinant, m );
		return out;
	}
	Vector4 v, vec[3];
	float det;

	det = MatrixDeterminant( m );
	if ( !det ) 
	{
		out = m;
		return out;
	}
	determinant = det;
	for( int i = 0; i < 4; i++ )
	{
		float signedDet = ( i & 1 ) ? -1.f : 1.f;
		signedDet /= det;
		for( int j = 0; j < 4; j++ )
		{
			if (j != i )
			{
				int a = j;
				if( j > i ) 
				{
					a = a - 1;
				}
				vec[a].x = m.m[j][0];
				vec[a].y = m.m[j][1];
				vec[a].z = m.m[j][2];
				vec[a].w = m.m[j][3];
			}
		}
		Vec4Cross( v, vec[0], vec[1], vec[2] );
		out.m[0][i] = signedDet * v.x;
		out.m[1][i] = signedDet * v.y;
		out.m[2][i] = signedDet * v.z;
		out.m[3][i] = signedDet * v.w;
	}
	return out;
}

Matrix& CcpMath::MatrixInverse( Matrix& out, const Matrix& m )
{
	float determinant;
	return MatrixInverse( out, determinant, m );
}

Matrix CcpMath::MatrixInverse( float& determinant, const Matrix& m )
{
	Matrix out;
	return MatrixInverse( out, determinant, m );
}

Matrix CcpMath::MatrixInverse( const Matrix& m )
{
	Matrix out;
	float determinant;
	return MatrixInverse( out, determinant, m );
}

Matrix& CcpMath::MatrixScaling( Matrix& out, float sx, float sy, float sz )
{
	out._11 = sx; out._12 = 0.f; out._13 = 0.f; out._14 = 0.f;
	out._21 = 0.f; out._22 = sy; out._23 = 0.f; out._24 = 0.f;
	out._31 = 0.f; out._32 = 0.f; out._33 = sz; out._34 = 0.f;
	out._41 = 0.f; out._42 = 0.f; out._43 = 0.f; out._44 = 1.f;
	return out;
}

Matrix CcpMath::MatrixScaling( float sx, float sy, float sz )
{
	Matrix out;
	return MatrixScaling( out, sx, sy, sz );
}

Matrix& CcpMath::MatrixTranslation( Matrix& out, float x, float y, float z )
{
	out._11 = 1.f; out._12 = 0.f; out._13 = 0.f; out._14 = 0.f;
	out._21 = 0.f; out._22 = 1.f; out._23 = 0.f; out._24 = 0.f;
	out._31 = 0.f; out._32 = 0.f; out._33 = 1.f; out._34 = 0.f;
	out._41 = x; out._42 = y; out._43 = z; out._44 = 1.f;
	return out;
}

Matrix CcpMath::MatrixTranslation( float x, float y, float z )
{
	Matrix out;
	return MatrixTranslation( out, x, y, z );
}

Matrix& CcpMath::MatrixRotationX( Matrix& out, float angle )
{
	float sinAngle = sin( angle );
	float cosAngle = cos( angle );

	out.m[0][0] = 1.0f;
	out.m[0][1] = 0.0f;
	out.m[0][2] = 0.0f;
	out.m[0][3] = 0.0f;
	out.m[1][0] = 0.0f;
	out.m[1][1] = cosAngle;
	out.m[1][2] = sinAngle;
	out.m[1][3] = 0.0f;
	out.m[2][0] = 0.0f;
	out.m[2][1] = -sinAngle;
	out.m[2][2] = cosAngle;
	out.m[2][3] = 0.0f;
	out.m[3][0] = 0.0f;
	out.m[3][1] = 0.0f;
	out.m[3][2] = 0.0f;
	out.m[3][3] = 1.0f;
	return out;
}

Matrix CcpMath::MatrixRotationX( float angle )
{
	Matrix out;
	return MatrixRotationX( out, angle );
}

Matrix& CcpMath::MatrixRotationY( Matrix& out, float angle )
{
	float sinAngle = sin( angle );
	float cosAngle = cos( angle );

	out.m[0][0] = cosAngle;
	out.m[0][1] = 0.0f;
	out.m[0][2] = -sinAngle;
	out.m[0][3] = 0.0f;
	out.m[1][0] = 0.0f;
	out.m[1][1] = 1.0f;
	out.m[1][2] = 0.0f;
	out.m[1][3] = 0.0f;
	out.m[2][0] = sinAngle;
	out.m[2][1] = 0.0f;
	out.m[2][2] = cosAngle;
	out.m[2][3] = 0.0f;
	out.m[3][0] = 0.0f;
	out.m[3][1] = 0.0f;
	out.m[3][2] = 0.0f;
	out.m[3][3] = 1.0f;
	return out;
}

Matrix CcpMath::MatrixRotationY( float angle )
{
	Matrix out;
	return MatrixRotationY( out, angle );
}

Matrix& CcpMath::MatrixRotationZ( Matrix& out, float angle )
{
	float sinAngle = sin( angle );
	float cosAngle = cos( angle );

	out.m[0][0] = cosAngle;
	out.m[0][1] = sinAngle;
	out.m[0][2] = 0.0f;
	out.m[0][3] = 0.0f;
	out.m[1][0] = -sinAngle;
	out.m[1][1] = cosAngle;
	out.m[1][2] = 0.0f;
	out.m[1][3] = 0.0f;
	out.m[2][0] = 0.0f;
	out.m[2][1] = 0.0f;
	out.m[2][2] = 1.0f;
	out.m[2][3] = 0.0f;
	out.m[3][0] = 0.0f;
	out.m[3][1] = 0.0f;
	out.m[3][2] = 0.0f;
	out.m[3][3] = 1.0f;
	return out;
}

Matrix CcpMath::MatrixRotationZ( float angle )
{
	Matrix out;
	return MatrixRotationZ( out, angle );
}

Matrix& CcpMath::MatrixRotationAxis( Matrix& out, const Vector3& v, float angle )
{
	Vector3 normal;
	Vec3Normalize( normal, v );

	float sinAngle = sin( angle );
	float cosAngle = cos( angle );

	out.m[0][0] = ( 1.0f - cosAngle ) * normal.x * normal.x + cosAngle;
	out.m[1][0] = ( 1.0f - cosAngle ) * normal.x * normal.y - sinAngle * normal.z;
	out.m[2][0] = ( 1.0f - cosAngle ) * normal.x * normal.z + sinAngle * normal.y;
	out.m[3][0] = 0.f;
	out.m[0][1] = ( 1.0f - cosAngle ) * normal.y * normal.x + sinAngle * normal.z;
	out.m[1][1] = ( 1.0f - cosAngle ) * normal.y * normal.y + cosAngle;
	out.m[2][1] = ( 1.0f - cosAngle ) * normal.y * normal.z - sinAngle * normal.x;
	out.m[3][1] = 0.f;
	out.m[0][2] = ( 1.0f - cosAngle ) * normal.z * normal.x - sinAngle * normal.y;
	out.m[1][2] = ( 1.0f - cosAngle ) * normal.z * normal.y + sinAngle * normal.x;
	out.m[2][2] = ( 1.0f - cosAngle ) * normal.z * normal.z + cosAngle;
	out.m[3][2] = 0.f;
	out.m[0][3] = 0.f;
	out.m[1][3] = 0.f;
	out.m[2][3] = 0.f;
	out.m[3][3] = 1.f;
	return out;
}

Matrix CcpMath::MatrixRotationAxis( const Vector3& v, float angle )
{
	Matrix out;
	return MatrixRotationAxis( out, v, angle );
}

Matrix& CcpMath::MatrixRotationQuaternion( Matrix& out, const Quaternion& q )
{
	out.m[0][0] = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
	out.m[0][1] = 2.0f * (q.x *q.y + q.z * q.w);
	out.m[0][2] = 2.0f * (q.x * q.z - q.y * q.w);
	out.m[0][3] = 0.0f;
	out.m[1][0] = 2.0f * (q.x * q.y - q.z * q.w);
	out.m[1][1] = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
	out.m[1][2] = 2.0f * (q.y *q.z + q.x *q.w);
	out.m[1][3] = 0.0f;
	out.m[2][0] = 2.0f * (q.x * q.z + q.y * q.w);
	out.m[2][1] = 2.0f * (q.y *q.z - q.x *q.w);
	out.m[2][2] = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
	out.m[2][3] = 0.0f;
	out.m[3][0] = 0.0f;
	out.m[3][1] = 0.0f;
	out.m[3][2] = 0.0f;
	out.m[3][3] = 1.0f;
	return out;
}

Matrix CcpMath::MatrixRotationQuaternion( const Quaternion& q )
{
	Matrix out;
	return MatrixRotationQuaternion( out, q );
}

Matrix& CcpMath::MatrixRotationYawPitchRoll( Matrix& out, float yaw, float pitch, float roll )
{
	Quaternion q;
	return MatrixRotationQuaternion( out, QuaternionRotationYawPitchRoll( q, yaw, pitch, roll ) );
}

Matrix CcpMath::MatrixRotationYawPitchRoll( float yaw, float pitch, float roll )
{
	Matrix out;
	return MatrixRotationYawPitchRoll( out, yaw, pitch, roll );
}

Matrix& CcpMath::MatrixTransformation( 
	Matrix& out, 
	const Vector3* scalingCenter,
	const Quaternion* scalingRotation, 
	const Vector3* scaling,
	const Vector3* rotationCenter, 
	const Quaternion *rotation,
	const Vector3* translation )
{
	Matrix m1, m2, m3, m4, m5, m6, m7, p1, p2, p3, p4, p5;
	Quaternion prc;
	Vector3 psc, pt;

	if( !scalingCenter )
	{
		psc.x = 0.0f;
		psc.y = 0.0f;
		psc.z = 0.0f;
	}
	else
	{
		psc.x = scalingCenter->x;
		psc.y = scalingCenter->y;
		psc.z = scalingCenter->z;
	}
	if ( !rotationCenter )
	{
		prc.x = 0.0f;
		prc.y = 0.0f;
		prc.z = 0.0f;
	}
	else
	{
		prc.x = rotationCenter->x;
		prc.y = rotationCenter->y;
		prc.z = rotationCenter->z;
	}
	if ( !translation )
	{
		pt.x = 0.0f;
		pt.y = 0.0f;
		pt.z = 0.0f;
	}
	else
	{
		pt.x = translation->x;
		pt.y = translation->y;
		pt.z = translation->z;
	}
	MatrixTranslation( m1, -psc.x, -psc.y, -psc.z );
	if ( !scalingRotation )
	{
		MatrixIdentity( m2 );
		MatrixIdentity( m4 );
	}
	else
	{
		MatrixRotationQuaternion( m4, *scalingRotation );
		MatrixInverse( m2, m4 );
	}
	if ( !scaling )
	{
		MatrixIdentity( m3 );
	}
	else
	{
		MatrixScaling( m3, scaling->x, scaling->y, scaling->z );
	}
	if ( !rotation )
	{
		MatrixIdentity( m6 );
	}
	else
	{
		MatrixRotationQuaternion( m6, *rotation );
	}
	MatrixTranslation( m5, psc.x - prc.x,  psc.y - prc.y,  psc.z - prc.z);
	MatrixTranslation( m7, prc.x + pt.x, prc.y + pt.y, prc.z + pt.z);
	MatrixMultiply( p1, m1, m2 );
	MatrixMultiply( p2, p1, m3 );
	MatrixMultiply( p3, p2, m4 );
	MatrixMultiply( p4, p3, m5 );
	MatrixMultiply( p5, p4, m6 );
	MatrixMultiply( out, p5, m7 );
	return out;
}

Matrix CcpMath::MatrixTransformation( 
	const Vector3* scalingCenter,
	const Quaternion* scalingRotation, 
	const Vector3* scaling,
	const Vector3* rotationCenter, 
	const Quaternion *rotation,
	const Vector3* translation )
{
	Matrix out;
	return MatrixTransformation( out, scalingCenter, scalingRotation, scaling, rotationCenter, rotation, translation );
}

Matrix& CcpMath::MatrixTransformation2D( 
	Matrix& out, 
	const Vector2* scalingCenter, 
	float scalingRotation, 
	const Vector2* scaling, 
	const Vector2* rotationCenter, 
	float rotation, 
	const Vector2* translation )
{
	Matrix m1, m2, m3, m4, m5, m6, m7, p1, p2, p3, p4, p5;
	Quaternion prc;
	Vector3 psc, pt;

	if( !scalingCenter )
	{
		psc.x = 0.0f;
		psc.y = 0.0f;
	}
	else
	{
		psc.x = scalingCenter->x;
		psc.y = scalingCenter->y;
	}
	psc.z = 0.0f;
	if ( !rotationCenter )
	{
		prc.x = 0.0f;
		prc.y = 0.0f;
	}
	else
	{
		prc.x = rotationCenter->x;
		prc.y = rotationCenter->y;
	}
	prc.z = 0.0f;
	if ( !translation )
	{
		pt.x = 0.0f;
		pt.y = 0.0f;
	}
	else
	{
		pt.x = translation->x;
		pt.y = translation->y;
	}
	pt.z = 0.0f;
	MatrixTranslation( m1, -psc.x, -psc.y, -psc.z );
	if ( !scalingRotation )
	{
		MatrixIdentity( m2 );
		MatrixIdentity( m4 );
	}
	else
	{
		MatrixRotationZ( m4, scalingRotation );
		MatrixInverse( m2, m4 );
	}
	if ( !scaling )
	{
		MatrixIdentity( m3 );
	}
	else
	{
		MatrixScaling( m3, scaling->x, scaling->y, 1.0f );
	}
	if ( !rotation )
	{
		MatrixIdentity( m6 );
	}
	else
	{
		MatrixRotationZ( m6, rotation );
	}
	MatrixTranslation( m5, psc.x - prc.x,  psc.y - prc.y,  psc.z - prc.z);
	MatrixTranslation( m7, prc.x + pt.x, prc.y + pt.y, prc.z + pt.z);
	MatrixMultiply( p1, m1, m2 );
	MatrixMultiply( p2, p1, m3 );
	MatrixMultiply( p3, p2, m4 );
	MatrixMultiply( p4, p3, m5 );
	MatrixMultiply( p5, p4, m6 );
	MatrixMultiply( out, p5, m7 );
	return out;
}

Matrix CcpMath::MatrixTransformation2D( 
	const Vector2* scalingCenter, 
	float scalingRotation, 
	const Vector2* scaling, 
	const Vector2* rotationCenter, 
	float rotation, 
	const Vector2* translation )
{
	Matrix out;
	return MatrixTransformation2D( out, scalingCenter, scalingRotation, scaling, rotationCenter, rotation, translation );
}

Matrix& CcpMath::MatrixAffineTransformation( 
	Matrix& out, 
	float scaling, 
	const Vector3 *rotationCenter,
	const Quaternion *rotation, 
	const Vector3 *translation )
{
	Matrix s, rc, r, t;
	Vector3 ft;
	MatrixScaling( s, scaling, scaling, scaling );
	if( rotationCenter )
	{
		MatrixTranslation( rc, -rotationCenter->x, -rotationCenter->y, -rotationCenter->z );
		ft = *rotationCenter;
	}
	else
	{
		MatrixIdentity( rc );
		ft = Vector3( 0.0f, 0.0f, 0.0f );
	}
	if( rotation )
	{
		MatrixRotationQuaternion( r, *rotation );
	}
	else
	{
		MatrixIdentity( r );
	}
	if( translation )
	{
		ft += *translation;
	}
	MatrixTranslation( t, ft.x, ft.y, ft.z );

	Matrix tmp1, tmp2;
	MatrixMultiply( tmp1, s, rc );
	MatrixMultiply( tmp2, tmp1, r );
	MatrixMultiply( out, tmp2, t );

	return out;
}

Matrix CcpMath::MatrixAffineTransformation( 
	float scaling, 
	const Vector3 *rotationCenter,
	const Quaternion *rotation, 
	const Vector3 *translation )
{
	Matrix out;
	return MatrixAffineTransformation( out, scaling, rotationCenter, rotation, translation );
}

Matrix& CcpMath::MatrixLookAtRH( 
	Matrix& out, 
	const Vector3& peye, 
	const Vector3& pat,
	const Vector3& pup )
{
	Vector3 right, rightn, up, upn, vec, vec2;
	vec2 = pat - peye;
	Vec3Normalize( vec, vec2 );
	Vec3Cross( right, pup, vec );
	Vec3Cross( up, vec, right );
	Vec3Normalize( rightn, right );
	Vec3Normalize( upn, up );
	out.m[0][0] = -rightn.x;
	out.m[1][0] = -rightn.y;
	out.m[2][0] = -rightn.z;
	out.m[3][0] = Vec3Dot( rightn, peye );
	out.m[0][1] = upn.x;
	out.m[1][1] = upn.y;
	out.m[2][1] = upn.z;
	out.m[3][1] = -Vec3Dot( upn, peye );
	out.m[0][2] = -vec.x;
	out.m[1][2] = -vec.y;
	out.m[2][2] = -vec.z;
	out.m[3][2] = Vec3Dot( vec, peye );
	out.m[0][3] = 0.0f;
	out.m[1][3] = 0.0f;
	out.m[2][3] = 0.0f;
	out.m[3][3] = 1.0f;
	return out;
}

Matrix CcpMath::MatrixLookAtRH( 
	const Vector3& eye, 
	const Vector3& at,
	const Vector3& up )
{
	Matrix out;
	return MatrixLookAtRH( out, eye, at, up );
}

Matrix& CcpMath::MatrixLookAtLH( 
	Matrix& out, 
	const Vector3& peye, 
	const Vector3& pat,
	const Vector3& pup )
{
	Vector3 right, rightn, up, upn, vec, vec2;
	
	vec2 = pat - peye;
	Vec3Normalize( vec, vec2 );
	Vec3Cross( right, pup, vec );
	Vec3Cross( up, vec, right );
	Vec3Normalize( rightn, right );
	Vec3Normalize( upn, up );

	out.m[0][0] = rightn.x;
	out.m[1][0] = rightn.y;
	out.m[2][0] = rightn.z;
	out.m[3][0] = -Vec3Dot( rightn, peye );
	out.m[0][1] = upn.x;
	out.m[1][1] = upn.y;
	out.m[2][1] = upn.z;
	out.m[3][1] = -Vec3Dot( upn, peye );
	out.m[0][2] = vec.x;
	out.m[1][2] = vec.y;
	out.m[2][2] = vec.z;
	out.m[3][2] = -Vec3Dot( vec, peye );
	out.m[0][3] = 0.0f;
	out.m[1][3] = 0.0f;
	out.m[2][3] = 0.0f;
	out.m[3][3] = 1.0f;
	return out;
}

Matrix CcpMath::MatrixLookAtLH( 
	const Vector3& eye, 
	const Vector3& at,
	const Vector3& up )
{
	Matrix out;
	return MatrixLookAtLH( out, eye, at, up );
}

Matrix& CcpMath::MatrixPerspectiveRH( Matrix& out, float w, float h, float zn, float zf )
{
	MatrixIdentity( out );
	out.m[0][0] = 2.0f * zn / w;
	out.m[1][1] = 2.0f * zn / h;
	out.m[2][2] = zf / (zn - zf);
	out.m[3][2] = (zn * zf) / (zn - zf);
	out.m[2][3] = -1.0f;
	out.m[3][3] = 0.0f;
	return out;
}

Matrix CcpMath::MatrixPerspectiveRH( float w, float h, float zn, float zf )
{
	Matrix out;
	return MatrixPerspectiveRH( out, w, h, zn, zf );
}

Matrix& CcpMath::MatrixPerspectiveLH( Matrix& out, float w, float h, float zn, float zf )
{
	MatrixIdentity( out );
	out.m[0][0] = 2.0f * zn / w;
	out.m[1][1] = 2.0f * zn / h;
	out.m[2][2] = zf / (zf - zn);
	out.m[3][2] = (zn * zf) / (zn - zf);
	out.m[2][3] = 1.0f;
	out.m[3][3] = 0.0f;
	return out;
}

Matrix CcpMath::MatrixPerspectiveLH( float w, float h, float zn, float zf )
{
	Matrix out;
	return MatrixPerspectiveLH( out, w, h, zn, zf );
}

Matrix& CcpMath::MatrixPerspectiveFovRH( Matrix& out, float fovy, float aspect, float zn, float zf )
{
	MatrixIdentity( out );
	out.m[0][0] = 1.0f / ( aspect * tan( fovy / 2.0f ) );
	out.m[1][1] = 1.0f / tan( fovy / 2.0f );
	out.m[2][2] = zf / ( zn - zf );
	out.m[2][3] = -1.0f;
	out.m[3][2] = ( zf * zn ) / ( zn - zf );
	out.m[3][3] = 0.0f;
	return out;
}

Matrix CcpMath::MatrixPerspectiveFovRH( float fovy, float aspect, float zn, float zf )
{
	Matrix out;
	return MatrixPerspectiveFovRH( out, fovy, aspect, zn, zf );
}

Matrix& CcpMath::MatrixPerspectiveFovLH( Matrix& out, float fovy, float aspect, float zn, float zf )
{
	MatrixIdentity( out );
	out.m[0][0] = 1.0f / ( aspect * tan( fovy / 2.0f ) );
	out.m[1][1] = 1.0f / tan( fovy / 2.0f );
	out.m[2][2] = zf / ( zf - zn );
	out.m[2][3] = 1.0f;
	out.m[3][2] = ( zf * zn ) / ( zn - zf );
	out.m[3][3] = 0.0f;
	return out;
}

Matrix CcpMath::MatrixPerspectiveFovLH( float fovy, float aspect, float zn, float zf )
{
	Matrix out;
	return MatrixPerspectiveFovLH( out, fovy, aspect, zn, zf );
}

Matrix& CcpMath::MatrixPerspectiveOffCenterRH( 
	Matrix& out, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn, 
	float zf )
{
	MatrixIdentity( out );
	out.m[0][0] = 2.0f * zn / (r - l);
	out.m[1][1] = -2.0f * zn / (b - t);
	out.m[2][0] = 1.0f + 2.0f * l / (r - l);
	out.m[2][1] = -1.0f -2.0f * t / (b - t);
	out.m[2][2] = zf / (zn - zf);
	out.m[3][2] = (zn * zf) / (zn -zf);
	out.m[2][3] = -1.0f;
	out.m[3][3] = 0.0f;
	return out;
}

Matrix CcpMath::MatrixPerspectiveOffCenterRH( 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn, 
	float zf )
{
	Matrix out;
	return MatrixPerspectiveOffCenterRH( out, l, r, b, t, zn, zf );
}

Matrix& CcpMath::MatrixPerspectiveOffCenterLH( 
	Matrix& out, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn, 
	float zf )
{
	MatrixIdentity( out );
	out.m[0][0] = 2.0f * zn / (r - l);
	out.m[1][1] = -2.0f * zn / (b - t);
	out.m[2][0] = -1.0f - 2.0f * l / (r - l);
	out.m[2][1] = 1.0f + 2.0f * t / (b - t);
	out.m[2][2] = - zf / (zn - zf);
	out.m[3][2] = (zn * zf) / (zn -zf);
	out.m[2][3] = 1.0f;
	out.m[3][3] = 0.0f;
	return out;
}

Matrix CcpMath::MatrixPerspectiveOffCenterLH( 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn, 
	float zf )
{
	Matrix out;
	return MatrixPerspectiveOffCenterLH( out, l, r, b, t, zn, zf );
}

Matrix& CcpMath::MatrixOrthoRH( Matrix& out, float w, float h, float zn, float zf )
{
	MatrixIdentity( out );
	out.m[0][0] = 2.0f / w;
	out.m[1][1] = 2.0f / h;
	out.m[2][2] = 1.0f / (zn - zf);
	out.m[3][2] = zn / (zn - zf);
	return out;
}

Matrix CcpMath::MatrixOrthoRH( float w, float h, float zn, float zf )
{
	Matrix out;
	return MatrixOrthoRH( out, w, h, zn, zf );
}

Matrix& CcpMath::MatrixOrthoLH( Matrix& out, float w, float h, float zn, float zf )
{
	MatrixIdentity( out );
	out.m[0][0] = 2.0f / w;
	out.m[1][1] = 2.0f / h;
	out.m[2][2] = 1.0f / (zf - zn);
	out.m[3][2] = zn / (zn - zf);
	return out;
}

Matrix CcpMath::MatrixOrthoLH( float w, float h, float zn, float zf )
{
	Matrix out;
	return MatrixOrthoLH( out, w, h, zn, zf );
}

Matrix& CcpMath::MatrixOrthoOffCenterRH( 
	Matrix& out, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf )
{
	MatrixIdentity( out );
	out.m[0][0] = 2.0f / (r - l);
	out.m[1][1] = 2.0f / (t - b);
	out.m[2][2] = 1.0f / (zn -zf);
	out.m[3][0] = -1.0f -2.0f *l / (r - l);
	out.m[3][1] = 1.0f + 2.0f * t / (b - t);
	out.m[3][2] = zn / (zn -zf);
	return out;
}

Matrix CcpMath::MatrixOrthoOffCenterRH( 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf )
{
	Matrix out;
	return MatrixOrthoOffCenterRH( out, l, r, b, t, zn, zf );
}

Matrix& CcpMath::MatrixOrthoOffCenterLH( 
	Matrix& out, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf )
{
	MatrixIdentity( out );
	out.m[0][0] = 2.0f / (r - l);
	out.m[1][1] = 2.0f / (t - b);
	out.m[2][2] = 1.0f / (zf -zn);
	out.m[3][0] = -1.0f -2.0f *l / (r - l);
	out.m[3][1] = 1.0f + 2.0f * t / (b - t);
	out.m[3][2] = zn / (zn -zf);
	return out;
}

Matrix CcpMath::MatrixOrthoOffCenterLH( 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf )
{
	Matrix out;
	return MatrixOrthoOffCenterLH( out, l, r, b, t, zn, zf );
}

void CcpMath::MatrixDecompose( 
	Vector3& scale, 
	Quaternion& rotation, 
	Vector3& translation, 
	const Matrix& m )
{
	Matrix normalized;
	Vector3 vec;

	/*Compute the scaling part.*/
	vec.x = m.m[0][0];
	vec.y = m.m[0][1];
	vec.z = m.m[0][2];
	scale.x = Vec3Length( vec );

	vec.x = m.m[1][0];
	vec.y = m.m[1][1];
	vec.z = m.m[1][2];
	scale.y=Vec3Length( vec );

	vec.x = m.m[2][0];
	vec.y = m.m[2][1];
	vec.z = m.m[2][2];
	scale.z = Vec3Length( vec );

	/*Compute the translation part.*/
	translation.x = m.m[3][0];
	translation.y = m.m[3][1];
	translation.z = m.m[3][2];

	/*Let's calculate the rotation now*/
	if( ( scale.x == 0.0f ) || ( scale.y == 0.0f ) || ( scale.z == 0.0f ) )
	{
		rotation = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
	}
	else
	{
		normalized.m[0][0] = m.m[0][0] / scale.x;
		normalized.m[0][1] = m.m[0][1] / scale.x;
		normalized.m[0][2] = m.m[0][2] / scale.x;
		normalized.m[1][0] = m.m[1][0] / scale.y;
		normalized.m[1][1] = m.m[1][1] / scale.y;
		normalized.m[1][2] = m.m[1][2] / scale.y;
		normalized.m[2][0] = m.m[2][0] / scale.z;
		normalized.m[2][1] = m.m[2][1] / scale.z;
		normalized.m[2][2] = m.m[2][2] / scale.z;

		QuaternionRotationMatrix( rotation, normalized );
	}
}








Matrix* D3DXMatrixIdentity( Matrix *pOut )
{
	return &CcpMath::MatrixIdentity( *pOut );
}

bool D3DXMatrixIsIdentity( const Matrix *pM )
{
	return CcpMath::MatrixIsIdentity( *pM );
}

float D3DXMatrixDeterminant( const Matrix *pM )
{
	return CcpMath::MatrixDeterminant( *pM );
}

Matrix* D3DXMatrixTranspose( Matrix *pOut, const Matrix *pM )
{
	return &CcpMath::MatrixTranspose( *pOut, *pM );
}

Matrix* D3DXMatrixMultiply( Matrix *pOut, const Matrix *pM1, const Matrix *pM2 )
{
	return &CcpMath::MatrixMultiply( *pOut, *pM1, *pM2 );
}

Matrix* D3DXMatrixInverse( Matrix *pOut, float *pDeterminant, const Matrix *pM )
{
	if( pDeterminant )
	{
		return &CcpMath::MatrixInverse( *pOut, *pDeterminant, *pM );
	}
	else
	{
		return &CcpMath::MatrixInverse( *pOut, *pM );
	}
}

Matrix* D3DXMatrixScaling( Matrix *pOut, float sx, float sy, float sz )
{
	return &CcpMath::MatrixScaling( *pOut, sx, sy, sz );
}

Matrix* D3DXMatrixTranslation( Matrix *pOut, float x, float y, float z )
{
	return &CcpMath::MatrixTranslation( *pOut, x, y, z );
}

Matrix* D3DXMatrixRotationX( Matrix *pOut, float Angle )
{
	return &CcpMath::MatrixRotationX( *pOut, Angle );
}

Matrix* D3DXMatrixRotationY( Matrix *pOut, float Angle )
{
	return &CcpMath::MatrixRotationY( *pOut, Angle );
}

Matrix* D3DXMatrixRotationZ( Matrix *pOut, float Angle )
{
	return &CcpMath::MatrixRotationZ( *pOut, Angle );
}

Matrix* D3DXMatrixRotationAxis( Matrix *pOut, const Vector3 *pV, float Angle )
{
	return &CcpMath::MatrixRotationAxis( *pOut, *pV, Angle );
}

Matrix* D3DXMatrixRotationQuaternion( Matrix *pOut, const Quaternion *pQ )
{
	return &CcpMath::MatrixRotationQuaternion( *pOut, *pQ );
}

Matrix* D3DXMatrixRotationYawPitchRoll( Matrix *pOut, float Yaw, float Pitch, float Roll )
{
	return &CcpMath::MatrixRotationYawPitchRoll( *pOut, Yaw, Pitch, Roll );
}

Matrix* D3DXMatrixTransformation( 
	Matrix *pOut, 
	const Vector3 *pScalingCenter,
	const Quaternion *pScalingRotation, 
	const Vector3 *pScaling,
	const Vector3 *pRotationCenter, 
	const Quaternion *pRotation,
	const Vector3 *pTranslation )
{
	return &CcpMath::MatrixTransformation( *pOut, pScalingCenter, pScalingRotation, pScaling, pRotationCenter, pRotation, pTranslation );
}

Matrix* D3DXMatrixTransformation2D( 
	Matrix *pOut, 
	const Vector2* pScalingCenter, 
	float ScalingRotation, 
	const Vector2* pScaling, 
	const Vector2* pRotationCenter, 
	float Rotation, 
	const Vector2* pTranslation )
{
	return &CcpMath::MatrixTransformation2D( *pOut, pScalingCenter, ScalingRotation, pScaling, pRotationCenter, Rotation, pTranslation );
}

Matrix* D3DXMatrixAffineTransformation( 
	Matrix *pOut, 
	float Scaling, 
	const Vector3 *pRotationCenter,
	const Quaternion *pRotation, 
	const Vector3 *pTranslation )
{
	return &CcpMath::MatrixAffineTransformation( *pOut, Scaling, pRotationCenter, pRotation, pTranslation );
}

Matrix* D3DXMatrixLookAtRH( 
	Matrix *pOut, 
	const Vector3 *pEye, 
	const Vector3 *pAt,
	const Vector3 *pUp )
{
	return &CcpMath::MatrixLookAtRH( *pOut, *pEye, *pAt, *pUp );
}

Matrix* D3DXMatrixLookAtLH( 
	Matrix *pOut, 
	const Vector3 *pEye, 
	const Vector3 *pAt,
	const Vector3 *pUp )
{
	return &CcpMath::MatrixLookAtLH( *pOut, *pEye, *pAt, *pUp );
}

Matrix* D3DXMatrixPerspectiveRH( Matrix *pOut, float w, float h, float zn, float zf )
{
	return &CcpMath::MatrixPerspectiveRH( *pOut, w, h, zn, zf );
}

Matrix* D3DXMatrixPerspectiveLH( Matrix *pOut, float w, float h, float zn, float zf )
{
	return &CcpMath::MatrixPerspectiveLH( *pOut, w, h, zn, zf );
}

Matrix* D3DXMatrixPerspectiveFovRH( Matrix *pOut, float fovy, float Aspect, float zn, float zf )
{
	return &CcpMath::MatrixPerspectiveFovRH( *pOut, fovy, Aspect, zn, zf );
}

Matrix* D3DXMatrixPerspectiveFovLH( Matrix *pOut, float fovy, float Aspect, float zn, float zf )
{
	return &CcpMath::MatrixPerspectiveFovLH( *pOut, fovy, Aspect, zn, zf );
}

Matrix* D3DXMatrixPerspectiveOffCenterRH( 
	Matrix *pOut, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf )
{
	return &CcpMath::MatrixPerspectiveOffCenterRH( *pOut, l, r, b, t, zn, zf );
}

Matrix* D3DXMatrixPerspectiveOffCenterLH( 
	Matrix *pOut, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf )
{
	return &CcpMath::MatrixPerspectiveOffCenterLH( *pOut, l, r, b, t, zn, zf );
}

Matrix* D3DXMatrixOrthoRH( Matrix *pOut, float w, float h, float zn, float zf )
{
	return &CcpMath::MatrixOrthoRH( *pOut, w, h, zn, zf );
}

Matrix* D3DXMatrixOrthoLH( Matrix *pOut, float w, float h, float zn, float zf )
{
	return &CcpMath::MatrixOrthoLH( *pOut, w, h, zn, zf );
}

Matrix* D3DXMatrixOrthoOffCenterRH( 
	Matrix *pOut, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf )
{
	return &CcpMath::MatrixOrthoOffCenterRH( *pOut, l, r, b, t, zn, zf );
}

Matrix* D3DXMatrixOrthoOffCenterLH( 
	Matrix *pOut, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf )
{
	return &CcpMath::MatrixOrthoOffCenterLH( *pOut, l, r, b, t, zn, zf );
}

void D3DXMatrixDecompose( 
	Vector3* pOutScale, 
	Quaternion* pOutRotation, 
	Vector3* pOutTranslation, 
	const Matrix* pM )
{
	CcpMath::MatrixDecompose( *pOutScale, *pOutRotation, *pOutTranslation, *pM );
}

Matrix* D3DXMatrixReflect( Matrix* out, const Plane* plane )
{
    Plane normalizedPlane;
    D3DXPlaneNormalize( &normalizedPlane, plane );

    D3DXMatrixIdentity( out );
    out->m[0][0] = 1.0f - 2.0f * normalizedPlane.a * normalizedPlane.a;
    out->m[0][1] = -2.0f * normalizedPlane.a * normalizedPlane.b;
    out->m[0][2] = -2.0f * normalizedPlane.a * normalizedPlane.c;
    out->m[1][0] = -2.0f * normalizedPlane.a * normalizedPlane.b;
    out->m[1][1] = 1.0f - 2.0f * normalizedPlane.b * normalizedPlane.b;
    out->m[1][2] = -2.0f * normalizedPlane.b * normalizedPlane.c;
    out->m[2][0] = -2.0f * normalizedPlane.c * normalizedPlane.a;
    out->m[2][1] = -2.0f * normalizedPlane.c * normalizedPlane.b;
    out->m[2][2] = 1.0f - 2.0f * normalizedPlane.c * normalizedPlane.c;
    out->m[3][0] = -2.0f * normalizedPlane.d * normalizedPlane.a;
    out->m[3][1] = -2.0f * normalizedPlane.d * normalizedPlane.b;
    out->m[3][2] = -2.0f * normalizedPlane.d * normalizedPlane.c;
    return out;
}

Matrix* D3DXMatrixShadow( Matrix* out, const Vector4* light, const Plane* plane )
{
    Plane normalizedPlane;
    D3DXPlaneNormalize( &normalizedPlane, plane );
    float dot = D3DXPlaneDot( &normalizedPlane, light );

    out->m[0][0] = dot - normalizedPlane.a * light->x;
    out->m[0][1] = -normalizedPlane.a * light->y;
    out->m[0][2] = -normalizedPlane.a * light->z;
    out->m[0][3] = -normalizedPlane.a * light->w;
    out->m[1][0] = -normalizedPlane.b * light->x;
    out->m[1][1] = dot - normalizedPlane.b * light->y;
    out->m[1][2] = -normalizedPlane.b * light->z;
    out->m[1][3] = -normalizedPlane.b * light->w;
    out->m[2][0] = -normalizedPlane.c * light->x;
    out->m[2][1] = -normalizedPlane.c * light->y;
    out->m[2][2] = dot - normalizedPlane.c * light->z;
    out->m[2][3] = -normalizedPlane.c * light->w;
    out->m[3][0] = -normalizedPlane.d * light->x;
    out->m[3][1] = -normalizedPlane.d * light->y;
    out->m[3][2] = -normalizedPlane.d * light->z;
    out->m[3][3] = dot - normalizedPlane.d * light->w;
    return out;
}