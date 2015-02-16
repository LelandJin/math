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
#include "include/Vector4.h"
#include "include/Matrix.h"

Vector4::Vector4( const Vector3& xyz, float aw )
	:x( xyz.x ),
	y( xyz.y ),
	z( xyz.z ),
	w( aw )
{
}

float& Vector4::operator[]( uint32_t index )
{
	return ( &x )[index];
}

const float& Vector4::operator[]( uint32_t index ) const
{
	return ( &x )[index];
}

Vector4 Vector4::operator*( const Matrix& m )
{
	return CcpMath::Vec4Transform( *this, m );
}

const Vector4 operator*( float f, const Vector4& other )
{
	return Vector4( f * other.x, f * other.y, f * other.z, f * other.w );
}

float CcpMath::Vec4Dot( const Vector4& v1, const Vector4& v2 )
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

Vector4& CcpMath::Vec4Add( Vector4& out, const Vector4& v1, const Vector4& v2)
{
	out.x = v1.x + v2.x;
	out.y = v1.y + v2.y;
	out.z = v1.z + v2.z;
	out.w = v1.w + v2.w;
	return out;
}

Vector4 CcpMath::Vec4Add( const Vector4& v1, const Vector4& v2)
{
	Vector4 out;
	return Vec4Add( out, v1, v2 );
}

Vector4& CcpMath::Vec4Scale( Vector4& out, const Vector4& v, float s)
{
	out.x = v.x * s;
	out.y = v.y * s;
	out.z = v.z * s;
	out.w = v.w * s;
	return out;
}

Vector4 CcpMath::Vec4Scale( const Vector4& v, float s)
{
	Vector4 out;
	return Vec4Scale( out, v, s );
}

Vector4& CcpMath::Vec4Transform( Vector4& out, const Vector4& vv, const Matrix& m )
{
	Vector4 v = vv;
	out.x = v.x * m._11 + v.y * m._21 + v.z * m._31 + v.w * m._41;
	out.y = v.x * m._12 + v.y * m._22 + v.z * m._32 + v.w * m._42;
	out.z = v.x * m._13 + v.y * m._23 + v.z * m._33 + v.w * m._43;
	out.w = v.x * m._14 + v.y * m._24 + v.z * m._34 + v.w * m._44;
	return out;
}

Vector4 CcpMath::Vec4Transform( const Vector4& v, const Matrix& m )
{
	Vector4 out;
	return Vec4Transform( out, v, m );
}




float D3DXVec4Dot( const Vector4 *pV1, const Vector4 *pV2 )
{
	return CcpMath::Vec4Dot( *pV1, *pV2 );
}

Vector4* D3DXVec4Add( Vector4 *pOut, const Vector4 *pV1, const Vector4 *pV2 )
{
	return &CcpMath::Vec4Add( *pOut, *pV1, *pV2 );
}

Vector4* D3DXVec4Scale( Vector4 *pOut, const Vector4 *pV, float s)
{
	return &CcpMath::Vec4Scale( *pOut, *pV, s );
}

Vector4* D3DXVec4Transform( Vector4 *pOut, const Vector4 *pV, const Matrix *pM )
{
	return &CcpMath::Vec4Transform( *pOut, *pV, *pM );
}

Vector4* D3DXVec4TransformArray( Vector4 *pOut, uint32_t OutStride, const Vector4 *pV, uint32_t VStride, const Matrix *pM, uint32_t n )
{
    Vector4* out = pOut;
    const Vector4* v = pV;
    for( uint32_t i = 0; i < n; ++i )
    {
        CcpMath::Vec4Transform( *out, *v, *pM );
        out = reinterpret_cast<Vector4*>( reinterpret_cast<uint8_t*>( out ) + OutStride );
        v = reinterpret_cast<const Vector4*>( reinterpret_cast<const uint8_t*>( v ) + VStride );
    }
    return pOut;
}

