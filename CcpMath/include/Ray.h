#pragma once

#include "Vector3.h"

namespace CcpMath
{

struct Ray
{
	Ray() = default;
	Ray( const Vector3& origin, const Vector3& direction );

	Vector3 origin;
	Vector3 direction;
};

}

#include "Ray_inline.h"