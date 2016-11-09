#pragma once
#include "Vector3.h"
#include "PhysicsTypeDefs.hpp"
#include "gtc\quaternion.hpp"

namespace Imgn
{
	class Quaternion
	{
	public:
		union {
			struct {
				/**
				* Holds the real component of the quaternion.
				*/
				real r;
	
				/**
				* Holds the first complex component of the
				* quaternion.
				*/
				real i;
	
				/**
				* Holds the second complex component of the
				* quaternion.
				*/
				real j;
	
				/**
				* Holds the third complex component of the
				* quaternion.
				*/
				real k;
			};
	
			/**
			* Holds the quaternion data in array form.
			*/
			real data[4];
		};
	
		// ... other Quaternion code as before ...
	
		/**
		* The default constructor creates a quaternion representing
		* a zero rotation.
		*/
		Quaternion() : r(1), i(0), j(0), k(0) {}
	
		/**
		* The explicit constructor creates a quaternion with the given
		* components.
		*
		* @param r The real component of the rigid body's orientation
		* quaternion.
		*
		* @param i The first complex component of the rigid body's
		* orientation quaternion.
		*
		* @param j The second complex component of the rigid body's
		* orientation quaternion.
		*
		* @param k The third complex component of the rigid body's
		* orientation quaternion.
		*
		* @note The given orientation does not need to be normalised,
		* and can be zero. This function will not alter the given
		* values, or normalise the quaternion. To normalise the
		* quaternion (and make a zero quaternion a legal rotation),
		* use the normalise function.
		*
		* @see normalise
		*/
		Quaternion(const real r, const real i, const real j, const real k)
			: r(r), i(i), j(j), k(k)
		{
		}
	
		/**
		* Normalises the quaternion to unit length, making it a valid
		* orientation quaternion.
		*/
		void normalise()
		{
			real d = r*r + i*i + j*j + k*k;
	
			// Check for zero length quaternion, and use the no-rotation
			// quaternion in that case.
			if (d < real_epsilon) {
				r = 1;
				return;
			}
	
			d = ((real)1.0) / real_sqrt(d);
			r *= d;
			i *= d;
			j *= d;
			k *= d;
		}
	
		/**
		* Multiplies the quaternion by the given quaternion.
		*
		* @param multiplier The quaternion by which to multiply.
		*/
		void operator *=(const Quaternion &multiplier)
		{
			Quaternion q = *this;
			r = q.r*multiplier.r - q.i*multiplier.i -
				q.j*multiplier.j - q.k*multiplier.k;
			i = q.r*multiplier.i + q.i*multiplier.r +
				q.j*multiplier.k - q.k*multiplier.j;
			j = q.r*multiplier.j + q.j*multiplier.r +
				q.k*multiplier.i - q.i*multiplier.k;
			k = q.r*multiplier.k + q.k*multiplier.r +
				q.i*multiplier.j - q.j*multiplier.i;
		}

		void operator =(const glm::quat quat)
		{
			r = quat.w;
			i = quat.x;
			j = quat.y;
			k = quat.z;
		}
	
		/**
		* Adds the given vector to this, scaled by the given amount.
		* This is used to update the orientation quaternion by a rotation
		* and time.
		*
		* @param vector The vector to add.
		*
		* @param scale The amount of the vector to add.
		*/
		void addScaledVector(const Vector3& vector, real scale)
		{
			Quaternion q(0,
				vector.x * scale,
				vector.y * scale,
				vector.z * scale);
			q *= *this;
			r += q.r * ((real)0.5);
			i += q.i * ((real)0.5);
			j += q.j * ((real)0.5);
			k += q.k * ((real)0.5);
		}
	
		void rotateByVector(const Vector3& vector)
		{
			Quaternion q(0, vector.x, vector.y, vector.z);
			(*this) *= q;
		}

		glm::quat toQuat()
		{
			return glm::quat(r, i, j, k);
		}
	};
	
}
