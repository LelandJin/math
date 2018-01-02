#pragma once

#include "Requirements.h"
#if defined(_WIN32) && !defined(CCP_MATH_USE_OWN_XNA_MATH)
#include <xnamath.h>
#else
#include "xnamath.h"
#endif
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Plane.h"
#include "Color.h"
#include "Float16.h"