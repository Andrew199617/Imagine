#pragma once
#include "Quaternion.h"

namespace Imgn
{
	class Matrix3
	{
	public:
		/**
		* Holds the tensor matrix data in array form.
		*/
		real data[9];

		/**
		* Creates a new matrix.
		*/
		Matrix3()
		{
			data[0] = data[1] = data[2] = data[3] = data[4] = data[5] =
				data[6] = data[7] = data[8] = 0;
		}

		/**
		* Creates a new matrix with the given three vectors making
		* up its columns.
		*/
		Matrix3(const Vector3 &compOne, const Vector3 &compTwo,
			const Vector3 &compThree)
		{
			setComponents(compOne, compTwo, compThree);
		}

		/**
		* Creates a new matrix with explicit coefficients.
		*/
		Matrix3(real c0, real c1, real c2, real c3, real c4, real c5,
			real c6, real c7, real c8)
		{
			data[0] = c0; data[1] = c1; data[2] = c2;
			data[3] = c3; data[4] = c4; data[5] = c5;
			data[6] = c6; data[7] = c7; data[8] = c8;
		}

		/**
		* Sets the matrix to be a diagonal matrix with the given
		* values along the leading diagonal.
		*/
		void setDiagonal(real a, real b, real c);

		/**
		* Sets the value of the matrix from inertia tensor values.
		*/
		void setInertiaTensorCoeffs(real ix, real iy, real iz,
			real ixy = 0, real ixz = 0, real iyz = 0);

		/**
		* Sets the value of the matrix as an inertia tensor of
		* a rectangular block aligned with the body's coordinate
		* system with the given axis half-sizes and mass.
		*/
		void setBlockInertiaTensor(const Vector3 &halfSizes, real mass);

		/**
		* Sets the matrix to be a skew symmetric matrix based on
		* the given vector. The skew symmetric matrix is the equivalent
		* of the vector product. So if a,b are vectors. a x b = A_s b
		* where A_s is the skew symmetric form of a.
		*/
		void setSkewSymmetric(const Vector3 vector);

		/**
		* Sets the matrix values from the given three vector components.
		* These are arranged as the three columns of the vector.
		*/
		void setComponents(const Vector3 &compOne, const Vector3 &compTwo,
			const Vector3 &compThree);

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
		* Transform the given vector by the transpose of this matrix.
		*
		* @param vector The vector to transform.
		*/
		Vector3 transformTranspose(const Vector3 &vector) const;

		/**
		* Gets a vector representing one row in the matrix.
		*
		* @param i The row to return.
		*/
		Vector3 getRowVector(int i) const;

		/**
		* Gets a vector representing one axis (i.e. one column) in the matrix.
		*
		* @param i The row to return.
		*
		* @return The vector.
		*/
		Vector3 getAxisVector(int i) const;

		/**
		* Sets the matrix to be the inverse of the given matrix.
		*
		* @param m The matrix to invert and use to set this.
		*/
		void setInverse(const Matrix3 &m);

		/** Returns a new matrix containing the inverse of this matrix. */
		Matrix3 inverse() const;

		/**
		* Inverts the matrix.
		*/
		void invert();

		/**
		* Sets the matrix to be the transpose of the given matrix.
		*
		* @param m The matrix to transpose and use to set this.
		*/
		void setTranspose(const Matrix3 &m);

		/** Returns a new matrix containing the transpose of this matrix. */
		Matrix3 transpose() const;

		/**
		* Returns a matrix which is this matrix multiplied by the given
		* other matrix.
		*/
		Matrix3 operator*(const Matrix3 &o) const;

		/**
		* Multiplies this matrix in place by the given other matrix.
		*/
		void operator*=(const Matrix3 &o);

		/**
		* Multiplies this matrix in place by the given scalar.
		*/
		void operator*=(const real scalar);

		/**
		* Does a component-wise addition of this matrix and the given
		* matrix.
		*/
		void operator+=(const Matrix3 &o);

		/**
		* Sets this matrix to be the rotation matrix corresponding to
		* the given quaternion.
		*/
		void setOrientation(const Quaternion &q);

		/**
		* Interpolates a couple of matrices.
		*/
		static Matrix3 linearInterpolate(const Matrix3& a, const Matrix3& b, real prop);
	};
}


