////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Filipp Pavlov
// Created:		June 2013
// Copyright:	CCP 2013
//

#include "include/Float16.h"
#include <cmath>
#include <cfloat>
#include <limits>

#ifdef _MSC_VER

inline bool isinf( double num ) 
{ 
	return !_finite( num ) && !_isnan( num );
}

inline bool isnan( double num ) 
{ 
	return !!_isnan( num ); 
}

inline bool signbit( double num ) 
{ 
	return _copysign( 1.0, num ) < 0; 
}

#elif defined( __ANDROID__ )

inline bool isinf( double num )
{
	return std::isinf( num );
}

inline bool signbit( double num )
{
	return std::signbit( num );
}

#elif !defined( __APPLE__) && !defined(__ORBIS__)

inline bool signbit( double num ) 
{ 
    return std::signbit( num );
}

#endif

static inline uint16_t Float32To16( float in )
{
    int exp = 0, origexp;
    float tmp = fabs( in );
    int sign = signbit( in );
    uint32_t mantissa;
    uint16_t ret;

    /* Deal with special numbers */
    if( isinf( in ) )
	{
		return ( sign ? 0xffff : 0x7fff );
	}
    if( isnan( in ) ) 
	{
		return ( sign ? 0xffff : 0x7fff );
	}
    if( in == 0.0f ) 
	{
		return ( sign ? 0x8000 : 0x0000 );
	}

    if( tmp < powf( 2, 10 ) )
    {
        do
        {
            tmp *= 2.0f;
            exp--;
        } while( tmp < powf( 2, 10 ) );
    }
    else if( tmp >= powf( 2, 11 ) )
    {
        do
        {
            tmp /= 2.0f;
            exp++;
        } while( tmp >= powf( 2, 11 ) );
    }

    exp += 10;  /* Normalize the mantissa */
    exp += 15;  /* Exponent is encoded with excess 15 */

    origexp = exp;

    mantissa = (uint32_t) tmp;
    if( ( tmp - mantissa == 0.5f && mantissa % 2 == 1 ) || /* round half to even */
        ( tmp - mantissa > 0.5f ) )
    {
        mantissa++; /* round to nearest, away from zero */
    }
    if( mantissa == 2048 )
    {
        mantissa = 1024;
        exp++;
    }

    if( exp > 31 )
    {
        /* too big */
        ret = 0x7fff; /* INF */
    }
    else if( exp <= 0 )
    {
        uint32_t rounding = 0;

        /* Denormalized half float */

        /* return 0x0000 (=0.0) for numbers too small to represent in half floats */
        if( exp < -11 )
		{
            return (sign ? 0x8000 : 0x0000);
		}
        exp = origexp;

        /* the 13 extra bits from single precision are used for rounding */
        mantissa = (uint32_t)( tmp * powf( 2, 13 ) );
        mantissa >>= 1 - exp; /* denormalize */

        mantissa -= ~( mantissa >> 13 ) & 1; /* round half to even */
        /* remove 13 least significant bits to get half float precision */
        mantissa >>= 12;
        rounding = mantissa & 1;
        mantissa >>= 1;

        ret = mantissa + rounding;
    }
    else
    {
        ret = ( exp << 10 ) | ( mantissa & 0x3ff );
    }

    ret |= ( ( sign ? 1 : 0 ) << 15 ); /* Add the sign */
    return ret;
}

static inline float Float16To32( const uint16_t in )
{
	
	const uint16_t s = ( in & 0x8000 );
    const uint16_t e = ( in & 0x7C00 ) >> 10;
    const uint16_t m = in & 0x3FF;
    const float sgn = (s ? -1.0f : 1.0f);

    if( ( in & ~0x8000 ) == 0x7fff )
	{
		return s ? -std::numeric_limits<float>::quiet_NaN() : std::numeric_limits<float>::quiet_NaN();
	}

    if( e == 0 )
    {
        if( m == 0 ) 
		{
			return sgn * 0.0f; /* +0.0 or -0.0 */
		}
        else 
		{
			return sgn * powf( 2, -14.0f ) * ( m / 1024.0f );
		}
    }
    else
    {
        return sgn * powf( 2, e - 15.0f ) * ( 1.0f + ( m / 1024.0f ) );
    }
}


CcpMath::Float16::Float16( float value )
	:m_value( Float32To16( value ) )
{
}

uint16_t CcpMath::Float16::GetUint16Value() const
{
	return m_value;
}

CcpMath::Float16::operator float () const
{
	return Float16To32( m_value );
}

bool CcpMath::Float16::operator == ( const Float16& other ) const
{
	return m_value == other.m_value;
}

bool CcpMath::Float16::operator != ( const Float16& other ) const
{
	return m_value != other.m_value;
}

float* CcpMath::Float16To32Array( float* output, const Float16* input, size_t count )
{
	for( size_t i = 0; i < count; ++i )
	{
		output[i] = input[i];
	}
	return output;
}

CcpMath::Float16* CcpMath::Float32To16Array( Float16* output, const float* input, size_t count )
{
	for( size_t i = 0; i < count; ++i )
	{
		output[i] = input[i];
	}
	return output;
}

float* D3DXFloat16To32Array( float* pOut, const D3DXFLOAT16 *pIn, uint32_t n )
{
	return CcpMath::Float16To32Array( pOut, pIn, n );
}

D3DXFLOAT16* D3DXFloat32To16Array( D3DXFLOAT16* pOut, const float *pIn, uint32_t n )
{
	return CcpMath::Float32To16Array( pOut, pIn, n );
}
