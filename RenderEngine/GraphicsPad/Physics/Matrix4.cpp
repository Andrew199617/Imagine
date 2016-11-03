#include "Matrix4.h"


namespace Imgn
{

	void Matrix4::setDiagonal(real a, real b, real c)
	{
		data[0] = a;
		data[5] = b;
		data[10] = c;
	}

	Imgn::Vector3 Matrix4::operator*(const Vector3 &vector) const
	{
		return Vector3(
			vector.x * data[0] +
			vector.y * data[1] +
			vector.z * data[2] + data[3],

			vector.x * data[4] +
			vector.y * data[5] +
			vector.z * data[6] + data[7],

			vector.x * data[8] +
			vector.y * data[9] +
			vector.z * data[10] + data[11]
			);
	}

	Imgn::Matrix4 Matrix4::operator*(const Matrix4 &o) const
	{
		Matrix4 result;
		result.data[0] = (o.data[0] * data[0]) + (o.data[4] * data[1]) + (o.data[8] * data[2]);
		result.data[4] = (o.data[0] * data[4]) + (o.data[4] * data[5]) + (o.data[8] * data[6]);
		result.data[8] = (o.data[0] * data[8]) + (o.data[4] * data[9]) + (o.data[8] * data[10]);

		result.data[1] = (o.data[1] * data[0]) + (o.data[5] * data[1]) + (o.data[9] * data[2]);
		result.data[5] = (o.data[1] * data[4]) + (o.data[5] * data[5]) + (o.data[9] * data[6]);
		result.data[9] = (o.data[1] * data[8]) + (o.data[5] * data[9]) + (o.data[9] * data[10]);

		result.data[2] = (o.data[2] * data[0]) + (o.data[6] * data[1]) + (o.data[10] * data[2]);
		result.data[6] = (o.data[2] * data[4]) + (o.data[6] * data[5]) + (o.data[10] * data[6]);
		result.data[10] = (o.data[2] * data[8]) + (o.data[6] * data[9]) + (o.data[10] * data[10]);

		result.data[3] = (o.data[3] * data[0]) + (o.data[7] * data[1]) + (o.data[11] * data[2]) + data[3];
		result.data[7] = (o.data[3] * data[4]) + (o.data[7] * data[5]) + (o.data[11] * data[6]) + data[7];
		result.data[11] = (o.data[3] * data[8]) + (o.data[7] * data[9]) + (o.data[11] * data[10]) + data[11];

		return result;
	}

	Imgn::Vector3 Matrix4::transform(const Vector3 &vector) const
	{
		return (*this) * vector;
	}

	real Matrix4::getDeterminant() const
	{
		return -data[8] * data[5] * data[2] +
			data[4] * data[9] * data[2] +
			data[8] * data[1] * data[6] -
			data[0] * data[9] * data[6] -
			data[4] * data[1] * data[10] +
			data[0] * data[5] * data[10];
	}

	void Matrix4::setInverse(const Matrix4 &m)
	{
		// Make sure the determinant is non-zero.
		real det = getDeterminant();
		if (det == 0) return;
		det = ((real)1.0) / det;

		data[0] = (-m.data[9] * m.data[6] + m.data[5] * m.data[10])*det;
		data[4] = (m.data[8] * m.data[6] - m.data[4] * m.data[10])*det;
		data[8] = (-m.data[8] * m.data[5] + m.data[4] * m.data[9])*det;

		data[1] = (m.data[9] * m.data[2] - m.data[1] * m.data[10])*det;
		data[5] = (-m.data[8] * m.data[2] + m.data[0] * m.data[10])*det;
		data[9] = (m.data[8] * m.data[1] - m.data[0] * m.data[9])*det;

		data[2] = (-m.data[5] * m.data[2] + m.data[1] * m.data[6])*det;
		data[6] = (+m.data[4] * m.data[2] - m.data[0] * m.data[6])*det;
		data[10] = (-m.data[4] * m.data[1] + m.data[0] * m.data[5])*det;

		data[3] = (m.data[9] * m.data[6] * m.data[3]
			- m.data[5] * m.data[10] * m.data[3]
			- m.data[9] * m.data[2] * m.data[7]
			+ m.data[1] * m.data[10] * m.data[7]
			+ m.data[5] * m.data[2] * m.data[11]
			- m.data[1] * m.data[6] * m.data[11])*det;
		data[7] = (-m.data[8] * m.data[6] * m.data[3]
			+ m.data[4] * m.data[10] * m.data[3]
			+ m.data[8] * m.data[2] * m.data[7]
			- m.data[0] * m.data[10] * m.data[7]
			- m.data[4] * m.data[2] * m.data[11]
			+ m.data[0] * m.data[6] * m.data[11])*det;
		data[11] = (m.data[8] * m.data[5] * m.data[3]
			- m.data[4] * m.data[9] * m.data[3]
			- m.data[8] * m.data[1] * m.data[7]
			+ m.data[0] * m.data[9] * m.data[7]
			+ m.data[4] * m.data[1] * m.data[11]
			- m.data[0] * m.data[5] * m.data[11])*det;
	}

	Imgn::Matrix4 Matrix4::inverse() const
	{
		Matrix4 result;
		result.setInverse(*this);
		return result;
	}

	void Matrix4::invert()
	{
		setInverse(*this);
	}

	Imgn::Vector3 Matrix4::transformDirection(const Vector3 &vector) const
	{
		return Vector3(
			vector.x * data[0] +
			vector.y * data[1] +
			vector.z * data[2],

			vector.x * data[4] +
			vector.y * data[5] +
			vector.z * data[6],

			vector.x * data[8] +
			vector.y * data[9] +
			vector.z * data[10]
			);
	}

	Imgn::Vector3 Matrix4::transformInverseDirection(const Vector3 &vector) const
	{
		return Vector3(
			vector.x * data[0] +
			vector.y * data[4] +
			vector.z * data[8],

			vector.x * data[1] +
			vector.y * data[5] +
			vector.z * data[9],

			vector.x * data[2] +
			vector.y * data[6] +
			vector.z * data[10]
			);
	}

	Imgn::Vector3 Matrix4::transformInverse(const Vector3 &vector) const
	{
		Vector3 tmp = vector;
		tmp.x -= data[3];
		tmp.y -= data[7];
		tmp.z -= data[11];
		return Vector3(
			tmp.x * data[0] +
			tmp.y * data[4] +
			tmp.z * data[8],

			tmp.x * data[1] +
			tmp.y * data[5] +
			tmp.z * data[9],

			tmp.x * data[2] +
			tmp.y * data[6] +
			tmp.z * data[10]
			);
	}

	Imgn::Vector3 Matrix4::getAxisVector(int i) const
	{
		return Vector3(data[i], data[i + 4], data[i + 8]);
	}

	void Matrix4::setOrientationAndPos(const Quaternion &q, const Vector3 &pos)
	{
		data[0] = 1 - (2 * q.j*q.j + 2 * q.k*q.k);
		data[1] = 2 * q.i*q.j + 2 * q.k*q.r;
		data[2] = 2 * q.i*q.k - 2 * q.j*q.r;
		data[3] = pos.x;

		data[4] = 2 * q.i*q.j - 2 * q.k*q.r;
		data[5] = 1 - (2 * q.i*q.i + 2 * q.k*q.k);
		data[6] = 2 * q.j*q.k + 2 * q.i*q.r;
		data[7] = pos.y;

		data[8] = 2 * q.i*q.k + 2 * q.j*q.r;
		data[9] = 2 * q.j*q.k - 2 * q.i*q.r;
		data[10] = 1 - (2 * q.i*q.i + 2 * q.j*q.j);
		data[11] = pos.z;
	}

	void Matrix4::fillGLArray(float array[16]) const
	{
		array[0] = (float)data[0];
		array[1] = (float)data[4];
		array[2] = (float)data[8];
		array[3] = (float)0;

		array[4] = (float)data[1];
		array[5] = (float)data[5];
		array[6] = (float)data[9];
		array[7] = (float)0;

		array[8] = (float)data[2];
		array[9] = (float)data[6];
		array[10] = (float)data[10];
		array[11] = (float)0;

		array[12] = (float)data[3];
		array[13] = (float)data[7];
		array[14] = (float)data[11];
		array[15] = (float)1;
	}

}
