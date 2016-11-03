#include "Matrix3.h"

namespace Imgn
{

	void Matrix3::operator+=(const Matrix3 &o)
	{
		data[0] += o.data[0]; data[1] += o.data[1]; data[2] += o.data[2];
		data[3] += o.data[3]; data[4] += o.data[4]; data[5] += o.data[5];
		data[6] += o.data[6]; data[7] += o.data[7]; data[8] += o.data[8];
	}

	Imgn::Vector3 Matrix3::transformTranspose(const Vector3 &vector) const
	{
		return Vector3(
			vector.x * data[0] + vector.y * data[3] + vector.z * data[6],
			vector.x * data[1] + vector.y * data[4] + vector.z * data[7],
			vector.x * data[2] + vector.y * data[5] + vector.z * data[8]
			);
	}

	Imgn::Vector3 Matrix3::getRowVector(int i) const
	{
		return Vector3(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
	}

	Imgn::Vector3 Matrix3::getAxisVector(int i) const
	{
		return Vector3(data[i], data[i + 3], data[i + 6]);
	}

	void Matrix3::setInverse(const Matrix3 &m)
	{
		real t4 = m.data[0] * m.data[4];
		real t6 = m.data[0] * m.data[5];
		real t8 = m.data[1] * m.data[3];
		real t10 = m.data[2] * m.data[3];
		real t12 = m.data[1] * m.data[6];
		real t14 = m.data[2] * m.data[6];

		// Calculate the determinant
		real t16 = (t4*m.data[8] - t6*m.data[7] - t8*m.data[8] +
			t10*m.data[7] + t12*m.data[5] - t14*m.data[4]);

		// Make sure the determinant is non-zero.
		if (t16 == (real)0.0f) return;
		real t17 = 1 / t16;

		data[0] = (m.data[4] * m.data[8] - m.data[5] * m.data[7])*t17;
		data[1] = -(m.data[1] * m.data[8] - m.data[2] * m.data[7])*t17;
		data[2] = (m.data[1] * m.data[5] - m.data[2] * m.data[4])*t17;
		data[3] = -(m.data[3] * m.data[8] - m.data[5] * m.data[6])*t17;
		data[4] = (m.data[0] * m.data[8] - t14)*t17;
		data[5] = -(t6 - t10)*t17;
		data[6] = (m.data[3] * m.data[7] - m.data[4] * m.data[6])*t17;
		data[7] = -(m.data[0] * m.data[7] - t12)*t17;
		data[8] = (t4 - t8)*t17;
	}

	Imgn::Matrix3 Matrix3::inverse() const
	{
		Matrix3 result;
		result.setInverse(*this);
		return result;
	}

	void Matrix3::invert()
	{
		setInverse(*this);
	}

	void Matrix3::setTranspose(const Matrix3 &m)
	{
		data[0] = m.data[0];
		data[1] = m.data[3];
		data[2] = m.data[6];
		data[3] = m.data[1];
		data[4] = m.data[4];
		data[5] = m.data[7];
		data[6] = m.data[2];
		data[7] = m.data[5];
		data[8] = m.data[8];
	}

	Imgn::Matrix3 Matrix3::transpose() const
	{
		Matrix3 result;
		result.setTranspose(*this);
		return result;
	}

	void Matrix3::setDiagonal(real a, real b, real c)
	{
		setInertiaTensorCoeffs(a, b, c);
	}

	void Matrix3::setInertiaTensorCoeffs(real ix, real iy, real iz, real ixy /*= 0*/, real ixz /*= 0*/, real iyz /*= 0*/)
	{
		data[0] = ix;
		data[1] = data[3] = -ixy;
		data[2] = data[6] = -ixz;
		data[4] = iy;
		data[5] = data[7] = -iyz;
		data[8] = iz;
	}

	void Matrix3::setBlockInertiaTensor(const Vector3 &halfSizes, real mass)
	{
		Vector3 squares = halfSizes.componentProduct(halfSizes);
		setInertiaTensorCoeffs(0.3f*mass*(squares.y + squares.z),
			0.3f*mass*(squares.x + squares.z),
			0.3f*mass*(squares.x + squares.y));
	}

	void Matrix3::setSkewSymmetric(const Vector3 vector)
	{
		data[0] = data[4] = data[8] = 0;
		data[1] = -vector.z;
		data[2] = vector.y;
		data[3] = vector.z;
		data[5] = -vector.x;
		data[6] = -vector.y;
		data[7] = vector.x;
	}

	void Matrix3::setComponents(const Vector3 &compOne, const Vector3 &compTwo, const Vector3 &compThree)
	{
		data[0] = compOne.x;
		data[1] = compTwo.x;
		data[2] = compThree.x;
		data[3] = compOne.y;
		data[4] = compTwo.y;
		data[5] = compThree.y;
		data[6] = compOne.z;
		data[7] = compTwo.z;
		data[8] = compThree.z;
	}

	void Matrix3::operator*=(const real scalar)
	{
		data[0] *= scalar; data[1] *= scalar; data[2] *= scalar;
		data[3] *= scalar; data[4] *= scalar; data[5] *= scalar;
		data[6] *= scalar; data[7] *= scalar; data[8] *= scalar;
	}

	void Matrix3::operator*=(const Matrix3 &o)
	{
		real t1;
		real t2;
		real t3;

		t1 = data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6];
		t2 = data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7];
		t3 = data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8];
		data[0] = t1;
		data[1] = t2;
		data[2] = t3;

		t1 = data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6];
		t2 = data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7];
		t3 = data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8];
		data[3] = t1;
		data[4] = t2;
		data[5] = t3;

		t1 = data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6];
		t2 = data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7];
		t3 = data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8];
		data[6] = t1;
		data[7] = t2;
		data[8] = t3;
	}

	Imgn::Matrix3 Matrix3::operator*(const Matrix3 &o) const
	{
		return Matrix3(
			data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6],
			data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7],
			data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8],

			data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6],
			data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7],
			data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8],

			data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6],
			data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7],
			data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8]
			);
	}

	Imgn::Vector3 Matrix3::operator*(const Vector3 &vector) const
	{
		return Vector3(
			vector.x * data[0] + vector.y * data[1] + vector.z * data[2],
			vector.x * data[3] + vector.y * data[4] + vector.z * data[5],
			vector.x * data[6] + vector.y * data[7] + vector.z * data[8]
			);
	}

	Imgn::Vector3 Matrix3::transform(const Vector3 &vector) const
	{
		return (*this) * vector;
	}

	void Matrix3::setOrientation(const Quaternion &q)
	{
		data[0] = 1 - (2 * q.j*q.j + 2 * q.k*q.k);
		data[1] = 2 * q.i*q.j + 2 * q.k*q.r;
		data[2] = 2 * q.i*q.k - 2 * q.j*q.r;
		data[3] = 2 * q.i*q.j - 2 * q.k*q.r;
		data[4] = 1 - (2 * q.i*q.i + 2 * q.k*q.k);
		data[5] = 2 * q.j*q.k + 2 * q.i*q.r;
		data[6] = 2 * q.i*q.k + 2 * q.j*q.r;
		data[7] = 2 * q.j*q.k - 2 * q.i*q.r;
		data[8] = 1 - (2 * q.i*q.i + 2 * q.j*q.j);
	}

	Matrix3 Matrix3::linearInterpolate(const Matrix3& a, const Matrix3& b, real prop)
	{
		Matrix3 result;
		for (unsigned i = 0; i < 9; i++) {
			result.data[i] = a.data[i] * (1 - prop) + b.data[i] * prop;
		}
		return result;
	}
}
