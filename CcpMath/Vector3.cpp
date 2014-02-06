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
#include "include/Vector3.h"
#include "include/Vector4.h"
#include "include/Matrix.h"

Vector3::Vector3( float vx, float vy, float vz )
	:x( vx ),
	y( vy ),
	z( vz )
{
}

Vector3::Vector3( const Vector3& other )
	:x( other.x ),
	y( other.y ),
	z( other.z )
{
}

Vector3::Vector3( const float* f )
	:x( f[0] ),
	y( f[1] ),
	z( f[2] )
{
}

const Vector3 operator * ( float scale, const Vector3& vector )
{
	return vector * scale;
}


float CcpMath::Vec3Length( const Vector3& v )
{
	return sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}

float CcpMath::Vec3LengthSq( const Vector3& v )
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float CcpMath::Vec3Dot( const Vector3& v1, const Vector3& v2 )
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3& CcpMath::Vec3Cross( Vector3& out, const Vector3& v1, const Vector3& v2 )
{
	out.x = v1.y * v2.z - v1.z * v2.y;
	out.y = v1.z * v2.x - v1.x * v2.z;
	out.z = v1.x * v2.y - v1.y * v2.x;
	return out;
}

Vector3 CcpMath::Vec3Cross( const Vector3& v1, const Vector3& v2 )
{
	Vector3 out;
	Vec3Cross( out, v1, v2 );
	return out;
}

Vector3& CcpMath::Vec3Minimize( Vector3& out, const Vector3& v1, const Vector3& v2 )
{
	out.x = std::min( v1.x, v2.x );
	out.y = std::min( v1.y, v2.y );
	out.z = std::min( v1.z, v2.z );
	return out;
}

Vector3 CcpMath::Vec3Minimize( const Vector3& v1, const Vector3& v2 )
{
	Vector3 out;
	Vec3Minimize( out, v1, v2 );
	return out;
}

Vector3& CcpMath::Vec3Maximize( Vector3& out, const Vector3& v1, const Vector3& v2 )
{
	out.x = std::max( v1.x, v2.x );
	out.y = std::max( v1.y, v2.y );
	out.z = std::max( v1.z, v2.z );
	return out;
}

Vector3 CcpMath::Vec3Maximize( const Vector3& v1, const Vector3& v2 )
{
	Vector3 out;
	Vec3Maximize( out, v1, v2 );
	return out;
}

Vector3& CcpMath::Vec3Lerp( Vector3& out, const Vector3& v1, const Vector3& v2, float s )
{
	out.x = v1.x + s * ( v2.x - v1.x );
	out.y = v1.y + s * ( v2.y - v1.y );
	out.z = v1.z + s * ( v2.z - v1.z );
	return out;
}

Vector3 CcpMath::Vec3Lerp( const Vector3& v1, const Vector3& v2, float s )
{
	Vector3 out;
	Vec3Lerp( out, v1, v2, s );
	return out;
}

Vector3& CcpMath::Vec3Normalize( Vector3& out, const Vector3& v )
{
	float l = 1.f / Vec3Length( v );
	out.x = l * v.x;
	out.y = l * v.y;
	out.z = l * v.z;
	return out;
}

Vector3 CcpMath::Vec3Normalize( const Vector3& v )
{
	Vector3 out;
	Vec3Normalize( out, v );
	return out;
}

Vector3& CcpMath::Vec3Hermite( Vector3& out, const Vector3& v1, const Vector3& t1, const Vector3& v2, const Vector3& t2, float s )
{
	float k3 = 2.f * s * s * s - 3 * s * s + 1;
	float k2 = -2.f * s * s * s + 3 * s * s;
	float k1 = s * s * s - 2 * s * s + s;
	float k0 = s * s * s - s * s;

	out.x = k3 * v1.x + k2 * v2.x + k1 * t1.x + k0 * t2.x;
	out.y = k3 * v1.y + k2 * v2.y + k1 * t1.y + k0 * t2.y;
	out.z = k3 * v1.z + k2 * v2.z + k1 * t1.z + k0 * t2.z;
	return out;
}

Vector3 CcpMath::Vec3Hermite( const Vector3& v1, const Vector3& t1, const Vector3& v2, const Vector3& t2, float s )
{
	Vector3 out;
	Vec3Hermite( out, v1, t1, v2, t2, s );
	return out;
}

Vector3& CcpMath::Vec3CatmullRom( Vector3& out, const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, float s )
{
	float k0 = ( -s * s * s + 2 * s * s - s ) * 0.5f;
	float k1 = ( 3 * s * s * s - 5 * s * s + 2 ) * 0.5f;
	float k2 = ( -3 * s * s * s + 4 * s * s + s ) * 0.5f;
	float k3 = ( s * s * s - s * s ) * 0.5f;

	out.x = k0 * v0.x + k1 * v1.x + k2 * v2.x + k3 * v3.x;
	out.y = k0 * v0.y + k1 * v1.y + k2 * v2.y + k3 * v3.y;
	out.z = k0 * v0.z + k1 * v1.z + k2 * v2.z + k3 * v3.z;
	return out;
}

Vector3 CcpMath::Vec3CatmullRom( const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, float s )
{
	Vector3 out;
	Vec3CatmullRom( out, v0, v1, v2, v3, s );
	return out;
}

Vector4& CcpMath::Vec3Transform( Vector4& out, const Vector3& vv, const Matrix& m )
{
	Vector3 v = vv;
	out.x = v.x * m._11 + v.y * m._21 + v.z * m._31 + m._41;
	out.y = v.x * m._12 + v.y * m._22 + v.z * m._32 + m._42;
	out.z = v.x * m._13 + v.y * m._23 + v.z * m._33 + m._43;
	out.w = m._14 + m._24 + m._34 + m._44;
	return out;
}

Vector4 CcpMath::Vec3Transform( const Vector3& v, const Matrix& m )
{
	Vector4 out;
	return Vec3Transform( out, v, m );
}

Vector3& CcpMath::Vec3TransformCoord( Vector3& out, const Vector3& vv, const Matrix& m )
{
	Vector3 v = vv;
	float norm = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3];
	if( norm != 0 )
	{
		out.x = ( v.x * m._11 + v.y * m._21 + v.z * m._31 + m._41 ) / norm;
		out.y = ( v.x * m._12 + v.y * m._22 + v.z * m._32 + m._42 ) / norm;
		out.z = ( v.x * m._13 + v.y * m._23 + v.z * m._33 + m._43 ) / norm;
	}
	else
	{
		out.x = 0.0f;
		out.y = 0.0f;
		out.z = 0.0f;
	}
	return out;
}

Vector3 CcpMath::Vec3TransformCoord( const Vector3& v, const Matrix& m )
{
	Vector3 out;
	return Vec3TransformCoord( out, v, m );
}

Vector3& CcpMath::Vec3TransformNormal( Vector3& out, const Vector3& vv, const Matrix& m )
{
	Vector3 v = vv;
	out.x = v.x * m._11 + v.y * m._21 + v.z * m._31;
	out.y = v.x * m._12 + v.y * m._22 + v.z * m._32;
	out.z = v.x * m._13 + v.y * m._23 + v.z * m._33;
	return out;
}

Vector3 CcpMath::Vec3TransformNormal( const Vector3& v, const Matrix& m )
{
	Vector3 out;
	return Vec3TransformNormal( out, v, m );
}

void CcpMath::Vec3TransformCoordArray( 
	Vector3* out, 
	uint32_t outStride, 
	const Vector3* in, 
	uint32_t inStride, 
	const Matrix& m, 
	uint32_t count )
{
	for( uint32_t i = 0; i < count; ++i )
	{
		Vec3TransformCoord( *out, *in, m );
		out = reinterpret_cast<Vector3*>( reinterpret_cast<uint8_t*>( out ) + outStride );
		in = reinterpret_cast<const Vector3*>( reinterpret_cast<const uint8_t*>( in ) + inStride );
	}
}

bool CcpMath::SphereBoundProbe(
	const Vector3& center,
	float radius,
	const Vector3& rayPosition,
	const Vector3& rayDirection )
{
	Vector3 difference = rayPosition - center;
	float a = Vec3LengthSq( rayDirection );
	float b = Vec3Dot( difference, rayDirection );
	float c = Vec3LengthSq( difference ) - radius * radius;
	float d = b * b - a * c;
	return !( ( d <= 0.0f ) || ( 2.0f * sqrt( d ) <= b ) );
}

void CcpMath::ComputeBoundingSphere(
    const Vector3* firstPosition,
    uint32_t numVertices, 
    uint32_t stride,
    Vector3& center, 
    float& radius )
{
	Vector3 temp( 0.0f, 0.0f, 0.0f );
	radius = 0.0f;
	if( numVertices == 0 )
	{
		center = temp;
		return;
	}

	const uint8_t* data = reinterpret_cast<const uint8_t*>( firstPosition );

	for( uint32_t i = 0; i < numVertices; i++ )
	{
		temp += *reinterpret_cast<const Vector3*>( data );
		data += stride;
	}

	center = temp / float( numVertices );
	data = reinterpret_cast<const uint8_t*>( firstPosition );

	for( uint32_t i = 0; i < numVertices; i++ )
	{
		float d = Vec3LengthSq( center - *reinterpret_cast<const Vector3*>( data ) );
		data += stride;
		if ( d > radius )
		{
			radius = d;
		}
	}
	radius = sqrt( radius );
}





float D3DXVec3Length( const Vector3 *pV )
{
	return CcpMath::Vec3Length( *pV );
}

float D3DXVec3LengthSq( const Vector3 *pV )
{
	return CcpMath::Vec3LengthSq( *pV );
}

float D3DXVec3Dot( const Vector3 *pV1, const Vector3 *pV2 )
{
	return CcpMath::Vec3Dot( *pV1, *pV2 );
}

Vector3* D3DXVec3Cross( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2 )
{
	CcpMath::Vec3Cross( *pOut, *pV1, *pV2 );
	return pOut;
}

Vector3* D3DXVec3Add( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2 )
{
	*pOut = *pV1 + *pV2;
	return pOut;
}

Vector3* D3DXVec3Subtract( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2 )
{
	*pOut = *pV1 - *pV2;
	return pOut;
}

Vector3* D3DXVec3Minimize( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2 )
{
	CcpMath::Vec3Minimize( *pOut, *pV1, *pV2 );
	return pOut;
}

Vector3* D3DXVec3Maximize( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2 )
{
	CcpMath::Vec3Maximize( *pOut, *pV1, *pV2 );
	return pOut;
}

Vector3* D3DXVec3Scale( Vector3 *pOut, const Vector3 *pV, float s)
{
	*pOut = *pV * s;
	return pOut;
}

Vector3* D3DXVec3Lerp( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2, float s )
{
	CcpMath::Vec3Lerp( *pOut, *pV1, *pV2, s );
	return pOut;
}

Vector3* D3DXVec3Normalize( Vector3 *pOut, const Vector3 *pV )
{
	CcpMath::Vec3Normalize( *pOut, *pV );
	return pOut;
}

Vector3* D3DXVec3Hermite( Vector3 *pOut, const Vector3 *pV1, const Vector3 *pT1, const Vector3 *pV2, const Vector3 *pT2, float s )
{
	CcpMath::Vec3Hermite( *pOut, *pV1, *pT1, *pV2, *pT2, s );
	return pOut;
}

Vector3* D3DXVec3CatmullRom( Vector3 *pOut, const Vector3 *pV0, const Vector3 *pV1,	const Vector3 *pV2, const Vector3 *pV3, float s )
{
	CcpMath::Vec3CatmullRom( *pOut, *pV0, *pV1, *pV2, *pV3, s );
	return pOut;
}

Vector4* D3DXVec3Transform( Vector4 *pOut, const Vector3 *pV, const Matrix *pM )
{
	return &CcpMath::Vec3Transform( *pOut, *pV, *pM );
}

Vector3* D3DXVec3TransformCoord( Vector3 *pOut, const Vector3 *pV, const Matrix *pM )
{
	return &CcpMath::Vec3TransformCoord( *pOut, *pV, *pM );
}

Vector3* D3DXVec3TransformNormal( Vector3 *pOut, const Vector3 *pV, const Matrix *pM )
{
	return &CcpMath::Vec3TransformNormal( *pOut, *pV, *pM );
}

Vector3* D3DXVec3TransformCoordArray( 
	Vector3 *pOut, 
	uint32_t OutStride, 
	const Vector3 *pV, 
	uint32_t VStride, 
	const Matrix *pM, 
	uint32_t n )
{
	CcpMath::Vec3TransformCoordArray( pOut, OutStride, pV, VStride, *pM, n );
	return pOut;
}

bool D3DXSphereBoundProbe(
	const Vector3* pCenter,
	float Radius,
	const Vector3* pRayPosition,
	const Vector3* pRayDirection )
{
	return CcpMath::SphereBoundProbe( *pCenter, Radius, *pRayPosition, *pRayDirection );
}

void D3DXComputeBoundingSphere(
    const Vector3* pFirstPosition,
    uint32_t NumVertices, 
    uint32_t dwStride,
    Vector3* pCenter, 
    float* pRadius )
{
	CcpMath::ComputeBoundingSphere( pFirstPosition, NumVertices, dwStride, *pCenter, *pRadius );
}

bool D3DXIntersectTri( 
	const Vector3* p0, 
	const Vector3* p1, 
	const Vector3* p2, 
	const Vector3* rayPos, 
	const Vector3* rayDir, 
	float *u, 
	float *v, 
	float *dist )
{
    Matrix m;
    Vector4 vec;

    m.m[0][0] = p1->x - p0->x;
    m.m[1][0] = p2->x - p0->x;
    m.m[2][0] = -rayDir->x;
    m.m[3][0] = 0.0f;
    m.m[0][1] = p1->y - p0->z;
    m.m[1][1] = p2->y - p0->z;
    m.m[2][1] = -rayDir->y;
    m.m[3][1] = 0.0f;
    m.m[0][2] = p1->z - p0->z;
    m.m[1][2] = p2->z - p0->z;
    m.m[2][2] = -rayDir->z;
    m.m[3][2] = 0.0f;
    m.m[0][3] = 0.0f;
    m.m[1][3] = 0.0f;
    m.m[2][3] = 0.0f;
    m.m[3][3] = 1.0f;

    vec.x = rayPos->x - p0->x;
    vec.y = rayPos->y - p0->y;
    vec.z = rayPos->z - p0->z;
    vec.w = 0.0f;

    if( D3DXMatrixInverse( &m, NULL, &m ) )
    {
        D3DXVec4Transform( &vec, &vec, &m );
        if ( ( vec.x >= 0.0f ) && ( vec.y >= 0.0f ) && ( vec.x + vec.y <= 1.0f ) && ( vec.z >= 0.0f ) )
        {
            *u = vec.x;
            *v = vec.y;
            *dist = fabs( vec.z );
            return true;
        }
    }

    return false;
}