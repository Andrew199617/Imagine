#include "Vector3.h"
#include <sstream>

namespace Imgn
{

	void Vector3::invert()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	real Vector3::magnitude() const
	{
		return real_sqrt(x*x + y*y + z*z);
	}

	real Vector3::squareMagnitude() const
	{
		return x*x + y*y + z*z;
	}

	void Vector3::normalize()
	{
		real l = magnitude();
		if (l > 0)
		{
			(*this) *= ((real)1) / l;
		}
	}

	void Vector3::operator=(const glm::vec3 vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	bool Vector3::operator==(const Vector3 value)
	{
		return (x == value.x) && (y == value.y) && (z == value.z);
	}

	void Vector3::operator*=(const real value)
	{
		x *= value;
		y *= value;
		z *= value;
	}

	Vector3 Vector3::operator*(const real value) const
	{
		return Vector3(x*value, y*value, z*value);
	}

	real Vector3::operator*(const Vector3 & vector) const
	{
		return x*vector.x + y*vector.y + z*vector.z;
	}

	void Vector3::operator+=(const Vector3 & v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	Vector3 Vector3::operator+(const Vector3 & v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	void Vector3::operator-=(const Vector3 & v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	Vector3 Vector3::operator-(const Vector3 & v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	bool Vector3::operator!=(const Vector3 & v) const
	{
		if (x != v.x && y != v.y && z != v.z)
		{
			return true;
		}
		return false;
	}

	bool Vector3::operator==(const Vector3 & v) const
	{
		if (x == v.x && y == v.y && z == v.z)
		{
			return true;
		}
		return false;
	}

	Imgn::Vector3 Vector3::operator%(const Vector3 &vector) const
	{
		return Vector3(y*vector.z - z*vector.y,
			z*vector.x - x*vector.z,
			x*vector.y - y*vector.x);
	}

	void Vector3::addScaledVector(const Vector3 & vector, real scale)
	{
		x += vector.x * scale;
		y += vector.y * scale;
		z += vector.z * scale;
	}

	glm::vec3 Vector3::toVec3()
	{
		return glm::vec3(x, y, z);
	}

	void Vector3::clear()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	std::string Vector3::toString()
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);

		ss << x;
		ss << " ";
		ss << y;
		ss << " ";
		ss << z;
		ss << " ";

		std::string test = ss.str();
		return test;
	}


	Imgn::Vector3 Vector3::componentProduct(const Vector3 &vector) const
	{
		return Vector3(x * vector.x, y * vector.y, z * vector.z);
	}

	void Vector3::componentProductUpdate(const Vector3 &vector)
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
	}

	Imgn::Vector3 Vector3::vectorProduct(const Vector3 &vector) const
	{
		return Vector3(y*vector.z - z*vector.y,
			z*vector.x - x*vector.z,
			x*vector.y - y*vector.x);
	}

}