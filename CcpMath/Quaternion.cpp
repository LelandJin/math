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
#include "include/Quaternion.h"
#include "include/Vector3.h"
#include "include/Matrix.h"

Quaternion::Quaternion() 
{
}

Quaternion::Quaternion( const float* f )
	:x( f[0] ),
	y( f[1] ),
	z( f[2] ),
	w( f[3] )
{
}

Quaternion::Quaternion( float vx, float vy, float vz, float vw )
	:x( vx ),
	y( vy ),
	z( vz ),
	w( vw )
{
}

Quaternion::Quaternion( const Quaternion& other )
	:x( other.x ),
	y( other.y ),
	z( other.z ),
	w( other.w )
{
}

const Quaternion operator*( float f, const Quaternion& other )
{
	return other * f;
}

Quaternion& Quaternion::operator*=( const Quaternion& other )
{
	CcpMath::QuaternionMultiply( *this, *this, other );
	return *this;
}



float CcpMath::QuaternionLength( const Quaternion& q )
{
	return sqrt( QuaternionLengthSq( q ) );
}

float CcpMath::QuaternionLengthSq( const Quaternion& q )
{
	return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

float CcpMath::QuaternionDot( const Quaternion& q1, const Quaternion& q2 )
{
	return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

Quaternion& CcpMath::QuaternionIdentity( Quaternion& out )
{
	out = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
	return out;
}

const Quaternion& CcpMath::QuaternionIdentity()
{
	static const Quaternion id( 0.0f, 0.0f, 0.0f, 1.0f );
	return id;
}

bool CcpMath::QuaternionIsIdentity( const Quaternion& q )
{
	return q == Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
}

Quaternion& CcpMath::QuaternionConjugate( Quaternion& out, const Quaternion& q )
{
	out.x = -q.x;
	out.y = -q.y;
	out.z = -q.z;
	out.w = q.w;
	return out;
}

void CcpMath::QuaternionToAxisAngle( const Quaternion& q, Vector3& axis, float& angle )
{
	axis = Vector3( q.x, q.y, q.z );
	angle = acos( q.w );
}

Quaternion CcpMath::QuaternionConjugate( const Quaternion& q )
{
	Quaternion out;
	return QuaternionConjugate( out, q );
}

Quaternion& CcpMath::QuaternionRotationMatrix( Quaternion& out, const Matrix& m )
{
	int i, maxi;
	float maxdiag, S, trace;
 
	trace = m.m[0][0] + m.m[1][1] + m.m[2][2] + 1.0f;
	if ( trace > 1.0f)
	{
		out.x = ( m.m[1][2] - m.m[2][1] ) / ( 2.0f * sqrt( trace ) );
		out.y = ( m.m[2][0] - m.m[0][2] ) / ( 2.0f * sqrt( trace ) );
		out.z = ( m.m[0][1] - m.m[1][0] ) / ( 2.0f * sqrt( trace ) );
		out.w = sqrt(trace) / 2.0f;
		return out;
	}
	maxi = 0;
	maxdiag = m.m[0][0];
	for (i=1; i<3; i++)
	{
		if ( m.m[i][i] > maxdiag )
		{
			maxi = i;
			maxdiag = m.m[i][i];
		}
	}
	switch( maxi )
	{
	case 0:
		S = 2.0f * sqrt( 1.0f + m.m[0][0] - m.m[1][1] - m.m[2][2] );
		out.x = 0.25f * S;
		out.y = ( m.m[0][1] + m.m[1][0] ) / S;
		out.z = ( m.m[0][2] + m.m[2][0] ) / S;
		out.w = ( m.m[1][2] - m.m[2][1] ) / S;
		break;
	case 1:
		S = 2.0f * sqrt( 1.0f + m.m[1][1] - m.m[0][0] - m.m[2][2] );
		out.x = ( m.m[0][1] + m.m[1][0] ) / S;
		out.y = 0.25f * S;
		out.z = ( m.m[1][2] + m.m[2][1] ) / S;
		out.w = ( m.m[2][0] - m.m[0][2] ) / S;
		break;
	case 2:
		S = 2.0f * sqrt( 1.0f + m.m[2][2] - m.m[0][0] - m.m[1][1] );
		out.x = ( m.m[0][2] + m.m[2][0] ) / S;
		out.y = ( m.m[1][2] + m.m[2][1] ) / S;
		out.z = 0.25f * S;
		out.w = ( m.m[0][1] - m.m[1][0] ) / S;
		break;
	}
	return out;
}

Quaternion CcpMath::QuaternionRotationMatrix( const Matrix& m )
{
	Quaternion out;
	return QuaternionRotationMatrix( out, m );
}

Quaternion& CcpMath::QuaternionRotationAxis( Quaternion& out, const Vector3& axis, float angle )
{
	Vector3 temp = Vec3Normalize( axis );
	out.x = sin( angle / 2.0f ) * temp.x;
	out.y = sin( angle / 2.0f ) * temp.y;
	out.z = sin( angle / 2.0f ) * temp.z;
	out.w = cos( angle / 2.0f );
	return out;
}

Quaternion CcpMath::QuaternionRotationAxis( const Vector3& axis, float angle )
{
	Quaternion out;
	return QuaternionRotationAxis( out, axis, angle );
}

Quaternion& CcpMath::QuaternionRotationYawPitchRoll( Quaternion& out, float yaw, float pitch, float roll )
{
	float sinYaw = sin( yaw / 2.0f );
	float cosYaw = cos( yaw / 2.0f );
	float sinPitch = sin( pitch / 2.0f );
	float cosPitch = cos( pitch / 2.0f );
	float sinRoll = sin( roll / 2.0f );
	float cosRoll = cos( roll / 2.0f );

    out.x = sinYaw * cosPitch * sinRoll + cosYaw * sinPitch * cosRoll;
    out.y = sinYaw * cosPitch * cosRoll - cosYaw * sinPitch * sinRoll;
    out.z = cosYaw * cosPitch * sinRoll - sinYaw * sinPitch * cosRoll;
    out.w = cosYaw * cosPitch * cosRoll + sinYaw * sinPitch * sinRoll;
    return out;
}

Quaternion CcpMath::QuaternionRotationYawPitchRoll( float yaw, float pitch, float roll )
{
	Quaternion out;
	return QuaternionRotationYawPitchRoll( out, yaw, pitch, roll );
}

Quaternion& CcpMath::QuaternionMultiply( Quaternion& out, const Quaternion& q1, const Quaternion& q2 )
{
	out = QuaternionMultiply( q1, q2 );
	return out;
}

Quaternion CcpMath::QuaternionMultiply( const Quaternion& q1, const Quaternion& q2 )
{
	Quaternion result;
	result.x = q2.w * q1.x + q2.x * q1.w + q2.y * q1.z - q2.z * q1.y;
	result.y = q2.w * q1.y - q2.x * q1.z + q2.y * q1.w + q2.z * q1.x;
	result.z = q2.w * q1.z + q2.x * q1.y - q2.y * q1.x + q2.z * q1.w;
	result.w = q2.w * q1.w - q2.x * q1.x - q2.y * q1.y - q2.z * q1.z;
	return result;
}

Quaternion& CcpMath::QuaternionNormalize( Quaternion& out, const Quaternion& q )
{
	float l = 1.0f / QuaternionLength( q );
	out = q * l;
	return out;
}

Quaternion CcpMath::QuaternionNormalize( const Quaternion& q )
{
	return q / QuaternionLength( q );
}

Quaternion& CcpMath::QuaternionInverse( Quaternion& out, const Quaternion& q )
{
	float l = 1.0f / QuaternionLengthSq( q );
	out.x = -q.x * l;
	out.y = -q.y * l;
	out.z = -q.z * l;
	out.w = q.w * l;
	return out;
}

Quaternion CcpMath::QuaternionInverse( const Quaternion& q )
{
	Quaternion out;
	return QuaternionInverse( out, q );
}

Quaternion& CcpMath::QuaternionLn( Quaternion& out, const Quaternion& q )
{
	float norm = QuaternionLengthSq( q );
	if ( norm > 1.0001f || norm < 0.99999f )
	{
		out.x = q.x;
		out.y = q.y;
		out.z = q.z;
		out.w = 0.0f;
	}
	else
	{
		float normvec = sqrt( q.x * q.x + q.y * q.y + q.z * q.z );
		if( normvec == 0.0f )
		{
			out.x = 0.0f;
			out.y = 0.0f;
			out.z = 0.0f;
			out.w = 0.0f;
		}
		else
		{
			float theta = atan2( normvec, q.w ) / normvec;
			out.x = theta * q.x;
			out.y = theta * q.y;
			out.z = theta * q.z;
			out.w = 0.0f;
		}
	}
	return out;
}

Quaternion CcpMath::QuaternionLn( const Quaternion& q )
{
	Quaternion out;
	return QuaternionLn( out, q );
}

Quaternion& CcpMath::QuaternionExp( Quaternion& out, const Quaternion& q )
{
	float norm = sqrt( q.x * q.x + q.y * q.y + q.z * q.z );
	if( norm )
	{
		out.x = sin( norm ) * q.x / norm;
		out.y = sin( norm ) * q.y / norm;
		out.z = sin( norm ) * q.z / norm;
		out.w = cos( norm );
	}
	else
	{
		out.x = 0.0f;
		out.y = 0.0f;
		out.z = 0.0f;
		out.w = 1.0f;
	}
	return out;


}

Quaternion CcpMath::QuaternionExp( const Quaternion& q )
{
	Quaternion out;
	return QuaternionExp( out, q );
}

Quaternion& CcpMath::QuaternionSlerp( 
	Quaternion& out, 
	const Quaternion& q1,
	const Quaternion& q2, 
	float t )
{
	float epsilon = 1.0f;
	float temp = 1.0f - t;
	float u = t;
	float dot = QuaternionDot( q1, q2 );
	if( dot < 0.0f )
	{
		epsilon = -1.0f;
		dot = -dot;
	}
	if( 1.0f - dot > 0.001f )
	{
		float theta = acos( dot );
		temp  = sin( theta * temp ) / sin( theta );
		u = sin( theta * u ) / sin( theta );
	}
	out.x = temp * q1.x + epsilon * u * q2.x;
	out.y = temp * q1.y + epsilon * u * q2.y;
	out.z = temp * q1.z + epsilon * u * q2.z;
	out.w = temp * q1.w + epsilon * u * q2.w;
	return out;
}

Quaternion CcpMath::QuaternionSlerp( 
	const Quaternion& q1,
	const Quaternion& q2, 
	float t )
{
	Quaternion out;
	return QuaternionSlerp( out, q1, q2, t );
}

Quaternion& CcpMath::QuaternionSquad( 
	Quaternion& out, 
	const Quaternion& q1,
	const Quaternion& q2, 
	const Quaternion& q3,
	const Quaternion& q4, 
	float t )
{
	QuaternionSlerp( out, QuaternionSlerp( q1, q4, t ), QuaternionSlerp( q2, q3, t ), 2.0f * t * ( 1.0f - t ) );
	return out;
}

Quaternion CcpMath::QuaternionSquad( 
	const Quaternion& q1,
	const Quaternion& q2, 
	const Quaternion& q3,
	const Quaternion& q4, 
	float t )
{
	Quaternion out;
	return QuaternionSquad( out, q1, q2, q3, q4, t );
}

void CcpMath::QuaternionSquadSetup( 
	Quaternion& a, 
	Quaternion& b, 
	Quaternion& c,
	const Quaternion& q0, 
	const Quaternion& q1, 
	const Quaternion& q2, 
	const Quaternion& q3 )
{
	float ls01 = QuaternionLengthSq( q0 + q1 );
	float ld01 = QuaternionLengthSq( q0 - q1 );
	Quaternion sq0;
	if( ls01 < ld01 )
	{
		sq0 = -q0;
	}
	else
	{
		sq0 = q0;
	}

	float ls12 = QuaternionLengthSq( q1 + q2 );
	float ld12 = QuaternionLengthSq( q1 - q2 );
	Quaternion sq2;
	if( ls12 < ld12 )
	{
		sq2 = -q2;
	}
	else
	{
		sq2 = q2;
	}

	float ls23 = QuaternionLengthSq( q2 + q3 );
	float ld23 = QuaternionLengthSq( q2 - q3 );
	Quaternion sq3;
	if( ls01 < ld01 )
	{
		sq3 = -q3;
	}
	else
	{
		sq3 = q3;
	}

	Quaternion invQ1 = QuaternionInverse( q1 );
	Quaternion invQ2 = QuaternionInverse( sq2 );

	Quaternion lnQ0 = QuaternionLn( invQ1 * sq0 );
	Quaternion lnQ1 = QuaternionLn( invQ2 * q1 );
	Quaternion lnQ2 = QuaternionLn( invQ1 * sq2 );
	Quaternion lnQ3 = QuaternionLn( invQ2 * sq3 );

	Quaternion expQ02 = QuaternionExp( ( lnQ0 + lnQ2 ) * -0.25f );
	Quaternion expQ13 = QuaternionExp( ( lnQ1 + lnQ3 ) * -0.25f );

	a = q1 * expQ02;
	b = sq2 * expQ13;
	c = sq2;
}









float D3DXQuaternionLength( const Quaternion *pQ )
{
	return CcpMath::QuaternionLength( *pQ );
}

float D3DXQuaternionLengthSq( const Quaternion *pQ )
{
	return CcpMath::QuaternionLengthSq( *pQ );
}

float D3DXQuaternionDot( const Quaternion *pQ1, const Quaternion *pQ2 )
{
	return CcpMath::QuaternionDot( *pQ1, *pQ2 );
}

Quaternion* D3DXQuaternionMultiply( Quaternion *pOut, const Quaternion *pQ1, const Quaternion *pQ2 )
{
	return &CcpMath::QuaternionMultiply( *pOut, *pQ1, *pQ2 );
}

Quaternion* D3DXQuaternionIdentity( Quaternion *pOut )
{
	return &CcpMath::QuaternionIdentity( *pOut );
}

bool D3DXQuaternionIsIdentity( const Quaternion *pQ )
{
	return CcpMath::QuaternionIsIdentity( *pQ );
}

Quaternion* D3DXQuaternionConjugate( Quaternion *pOut, const Quaternion *pQ )
{
	return &CcpMath::QuaternionConjugate( *pOut, *pQ );
}

void D3DXQuaternionToAxisAngle( const Quaternion *pQ, Vector3 *pAxis, float *pAngle )
{
	CcpMath::QuaternionToAxisAngle( *pQ, *pAxis, *pAngle );
}

Quaternion* D3DXQuaternionRotationMatrix( Quaternion *pOut, const Matrix *pM)
{
	return &CcpMath::QuaternionRotationMatrix( *pOut, *pM );
}

Quaternion* D3DXQuaternionRotationAxis( Quaternion *pOut, const Vector3 *pV, float Angle )
{
	return &CcpMath::QuaternionRotationAxis( *pOut, *pV, Angle );
}

Quaternion* D3DXQuaternionRotationYawPitchRoll( Quaternion *pOut, float Yaw, float Pitch, float Roll )
{
	return &CcpMath::QuaternionRotationYawPitchRoll( *pOut, Yaw, Pitch, Roll );
}

Quaternion* D3DXQuaternionNormalize( Quaternion *pOut, const Quaternion *pQ )
{
	return &CcpMath::QuaternionNormalize( *pOut, *pQ );
}

Quaternion* D3DXQuaternionInverse( Quaternion *pOut, const Quaternion *pQ )
{
	return &CcpMath::QuaternionInverse( *pOut, *pQ );
}

Quaternion* D3DXQuaternionLn( Quaternion *pOut, const Quaternion *pQ )
{
	return &CcpMath::QuaternionLn( *pOut, *pQ );
}

Quaternion* D3DXQuaternionExp( Quaternion *pOut, const Quaternion *pQ )
{
	return &CcpMath::QuaternionExp( *pOut, *pQ );
}

Quaternion* D3DXQuaternionSlerp( Quaternion *pOut, const Quaternion *pQ1, const Quaternion *pQ2, float t )
{
	return &CcpMath::QuaternionSlerp( *pOut, *pQ1, *pQ2, t );
}

Quaternion* D3DXQuaternionSquad( 
	Quaternion *pOut, 
	const Quaternion *pQ1,
	const Quaternion *pA, 
	const Quaternion *pB,
	const Quaternion *pC, 
	float t )
{
	return &CcpMath::QuaternionSquad( *pOut, *pQ1, *pA, *pB, *pC, t );
}

void D3DXQuaternionSquadSetup( 
	Quaternion *pAOut, 
	Quaternion *pBOut, 
	Quaternion *pCOut,
	const Quaternion *pQ0, 
	const Quaternion *pQ1, 
	const Quaternion *pQ2, 
	const Quaternion *pQ3 )
{
	CcpMath::QuaternionSquadSetup( *pAOut, *pBOut, *pCOut, *pQ0, *pQ1, *pQ2, *pQ3 );
}
