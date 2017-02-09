#pragma once
#include <math.h>
#include <string>
#include <glm.hpp>
#include "PhysicsTypeDefs.hpp"

namespace Imgn
{
	class Vector3 : public glm::vec3 
	{
	public:
		Vector3() : glm::vec3() {}
		Vector3(real x, real y, real z) : glm::vec3(x,y,z) {}
		Vector3(glm::vec3 vec) : glm::vec3(vec) {}
		/*public:
			real x;
			real y;
			real z;

		private:
			real pad;*/

	public:
		void invert();
		real magnitude() const;
		real squareMagnitude() const;
		void normalize();
		void operator=(const glm::vec3);
		bool operator==(const Vector3 value);
		void operator*=(const real value);
		Vector3 operator*(const real value) const;
		real operator*(const Vector3 &vector) const;
		void operator+=(const Vector3& v);
		Vector3 operator+(const Vector3& v);
		void operator-=(const Vector3& v);
		Vector3 operator-(const Vector3& v) const;
		bool operator!=(const Vector3& v) const;
		bool operator==(const Vector3& v) const;
		Vector3 operator%(const Vector3 &vector) const;
		void addScaledVector(const Vector3& vector, real scale);
		real scalarProduct(const Vector3 &vector) const
		{
			return x*vector.x + y*vector.y + z*vector.z;
		}
		glm::vec3 toVec3();
		void clear();
		std::string toString();
		
		Vector3 componentProduct(const Vector3 &vector) const;
		void componentProductUpdate(const Vector3 &vector);
		Vector3 vectorProduct(const Vector3 &vector) const;
	};

}

