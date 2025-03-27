#pragma once

#include <physics/precision.h>

namespace physics {

	/**
	 * Holds a vector in 3 dimensions. Four data members are allocated
	 * to ensure alignment in an array.
	 */
	class Vector3
	{
	public:
		/** Holds the value along the x axis. */
		real x;

		/** Holds the value along the y axis. */
		real y;

		/** Holds the value along the z axis. */
		real z;

	private:
		/** Padding to ensure 4-word alignment. */
		real pad;

	public:
		Vector3() : x(0), y(0), z(0) {}
		Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}

		/** Flips all the components of the vector. */
		void invert()
		{
			x = -x;
			y = -y;
			z = -z;
		}

		/** Gets the magnitude of this vector. */
		real magnitude() const
		{
			return real_sqrt(x * x + y * y + z * z);
		}

		/** Gets the squared magnitude of this vector. */
		real squaredMagnitude() const
		{
			return x * x + y * y + z * z;
		}

		/** Turns a non-zero vector into a vector of unit length. */
		void normalize()
		{
			real l = magnitude();
			if (l > 0)
			{
				(*this) *= ((real)1) / l;
			}
		}

		/** Adds the given vector to this, scaled by the given amount. */
		void addScaledVector(const Vector3 &vector, real scale)
		{
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}

		/** 
		 * Calculates and returns a component-wise product of this
		 * vector with the given vector.
		 */
		Vector3 componentProduct(const Vector3 &vector) const
		{
			return Vector3(x * vector.x, y * vector.y, z * vector.z);
		}

		/**
		 * Performs a component-wise product with the given vector and
		 * sets this vector to its result.
		 */
		void componentProductUpdate(const Vector3 &vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}

		/**
		 * Calculates and returns the scalar product of this vector
		 * with the given vector.
		 */
		real scalarProduct(const Vector3& vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z;
		}

		/**
		 * Calculates and returns the vector product of this vector
		 * with the given vector.
		 */
		Vector3 vectorProduct(const Vector3& vector) const
		{
			return Vector3(
				y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x
			);
		}

		void clear()
		{
			x *= 0;
			y *= 0;
			z *= 0;
		}

		/** Operators overloads. */

		void operator*=(const real value)
		{
			x *= value;
			y *= value;
			z *= value;
		}

		Vector3 operator *(const real value) const
		{
			return Vector3(x * value, y * value, z * value);
		}

		real operator *(const Vector3& vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z;
		}

		void operator +=(const Vector3 &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}

		Vector3 operator +(const Vector3 &other)
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		void operator -=(const Vector3 &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		Vector3 operator -(const Vector3 &other)
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		/**
		 * Updates this vector to be the vector product of its current
		 * value and the given vector.
		 */
		void operator %=(const Vector3& vector)
		{
			*this = vectorProduct(vector);
		}

		Vector3 operator %(const Vector3& vector) const
		{
			return Vector3(
				y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x
			);
		}
	};
}