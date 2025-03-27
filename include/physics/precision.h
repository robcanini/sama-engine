#pragma once

#include <corecrt_math.h>

/** Defines the precision of the square root operator. */
#define real_sqrt sqrtf

/** Defines the precision of the power operator. */
#define real_pow powf

namespace physics {

	/** Defines a real number precision. By default single precision is provided. */
	typedef float real;
}