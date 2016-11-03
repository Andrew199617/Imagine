#pragma once
#include "Quaternion.h"

namespace Imgn
{
	class Matrix4
	{
	public:
		/**
		* Holds the transform matrix data in array form.
		*/
		real data[12];

		// ... Other Matrix4 code as before ...


		/**
		* Creates an identity matrix.
		*/
		Matrix4()
		{
			data[1] = data[2] = data[3] = data[4] = data[6] =
				data[7] = data[8] = data[9] = data[11] = 0;
			data[0] = data[5] = data[10] = 1;
		}

		/**
		* Sets the matrix to be a diagonal matrix with the given coefficients.
		*/
		void setDiagonal(real a, real b, real c);

		/**
		* Returns a matrix which is this matrix multiplied by the given
		* other matrix.
		*/
		Matrix4 operator*(const Matrix4 &o) const;

		/**
		* Transform the given vector by this matrix.
		*
		* @param vector The vector to transform.
		*/
		Vector3 operator*(const Vector3 &vector) const;

		/**
		* Transform the given vector by this matrix.
		*
		* @param vector The vector to transform.
		*/
		Vector3 transform(const Vector3 &vector) const;

		/**
		* Returns the determinant of the matrix.
		*/
		real getDeterminant() const;

		/**
		* Sets the matrix to be the inverse of the given matrix.
		*
		* @param m The matrix to invert and use to set this.
		*/
		void setInverse(const Matrix4 &m);

		/** Returns a new matrix containing the inverse of this matrix. */
		Matrix4 inverse() const;

		/**
		* Inverts the matrix.
		*/
		void invert();

		/**
		* Transform the given direction vector by this matrix.
		*
		* @note When a direction is converted between frames of
		* reference, there is no translation required.
		*
		* @param vector The vector to transform.
		*/
		Vector3 transformDirection(const Vector3 &vector) const;

		/**
		* Transform the given direction vector by the
		* transformational inverse of this matrix.
		*
		* @note This function relies on the fact that the inverse of
		* a pure rotation matrix is its transpose. It separates the
		* translational and rotation components, transposes the
		* rotation, and multiplies out. If the matrix is not a
		* scale and shear free transform matrix, then this function
		* will not give correct results.
		*
		* @note When a direction is converted between frames of
		* reference, there is no translation required.
		*
		* @param vector The vector to transform.
		*/
		Vector3 transformInverseDirection(const Vector3 &vector) const;

		/**
		* Transform the given vector by the transformational inverse
		* of this matrix.
		*
		* @note This function relies on the fact that the inverse of
		* a pure rotation matrix is its transpose. It separates the
		* translational and rotation components, transposes the
		* rotation, and multiplies out. If the matrix is not a
		* scale and shear free transform matrix, then this function
		* will not give correct results.
		*
		* @param vector The vector to transform.
		*/
		Vector3 transformInverse(const Vector3 &vector) const;

		/**
		* Gets a vector representing one axis (i.e. one column) in the matrix.
		*
		* @param i The row to return. Row 3 corresponds to the position
		* of the transform matrix.
		*
		* @return The vector.
		*/
		Vector3 getAxisVector(int i) const;

		/**
		* Sets this matrix to be the rotation matrix corresponding to
		* the given quaternion.
		*/
		void setOrientationAndPos(const Quaternion &q, const Vector3 &pos);

		/**
		* Fills the given array with this transform matrix, so it is
		* usable as an open-gl transform matrix. OpenGL uses a column
		* major format, so that the values are transposed as they are
		* written.
		*/
		void fillGLArray(float array[16]) const;
	};
}


