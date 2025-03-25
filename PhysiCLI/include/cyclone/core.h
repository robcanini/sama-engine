#pragma once

namespace cyclone {

	/**
	 * Holds a vector in 3 dimensions. Four data members are allocated
	 * to ensure alignment in an array.
	 */
	class Vector3 {
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
		void addScaledVector(const Vector3& vector, real scale)
		{
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}

		/** Operators overloads. */

		void operator*=(const real value)
		{
			x *= value;
			y *= value;
			z *= value;
		}

		Vector3 operator*(const real value) const
		{
			return Vector3(x * value, y * value, z * value);
		}

		void operator +=(const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}

		Vector3 operator+(const Vector3& other)
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		void operator -=(const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		Vector3 operator-(const Vector3& other)
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}
	};
}