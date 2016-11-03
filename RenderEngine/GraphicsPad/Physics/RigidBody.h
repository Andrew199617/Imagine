#pragma once
#include "..\ImgnComponent.h"
#include "..\ImgnProperties.h"
#include "Matrix3.h"
#include "Matrix4.h"
class SpatialComponent;

namespace Imgn
{
	class RigidBody :
		public ImgnComponent
	{
		IMGN_GENERATE(RigidBody)
			IMGN_PROPERTY(m_enabled, true)
			IMGN_PROPERTY(mass, 1)
			IMGN_PROPERTY(linearDamping, 0.05f)
			IMGN_PROPERTY(angularDamping, 0.05f)
			IMGN_PROPERTY(useGravity, true)
			IMGN_PROPERTY(isKinematic, false)
			IMGN_END(RigidBody)
	public:
		virtual void Awake() override;
		virtual bool Initialize() override;
		virtual void Update(float dt) override;

		/**
		* Integrates the rigid body forward in time by the given amount.
		* This function uses a Newton-Euler integration method, which is a
		* linear approximation to the correct integral. For this reason it
		* may be inaccurate in some cases.
		*/
		void Integrate(float duration);

		/**
		* Returns true if the mass of the body is not-infinite.
		*/
		bool HasFiniteMass();
		void SetInertiaTensor(const Matrix3 InertiaTensor);
		void SetOrientation(const real r, const real i,
			const real j, const real k);
		/**
		* Fills the given matrix data structure with a
		* transformation representing the rigid body's position and
		* orientation. The matrix is transposed from that returned
		* by getTransform. This call returns a matrix suitable
		* for applying as an OpenGL transform.
		*
		* @note Transforming a vector by this matrix turns it from
		* the body's local space to world space.
		*
		* @param matrix A pointer to the matrix to fill.
		*/
		glm::mat4 GetGLTransform() const;

		/**
		* Applies the given change in velocity.
		*/
		void AddVelocity(const Vector3 &deltaVelocity);
		/**
		* Clears the forces and torques in the accumulators. This will
		* be called automatically after each intergration step.
		*/
		void ClearAccumulators();

		/**
		* Adds the given force to centre of mass of the rigid body.
		* The force is expressed in world-coordinates.
		*
		* @param force The force to apply.
		*/
		void AddForce(const Vector3 &force);
		/**
		* Adds the given force to the given point on the rigid body.
		*
		* @param force The force to apply.
		*
		* @param point The location at which to apply the force, in
		* world-coordinates.
		*/
		void addForceAtPoint(const Vector3 &force, const Vector3 &point);

		/**
		* Applies the given change in rotation.
		*/
		void addRotation(const Vector3 &deltaRotation);
		void SetVelocity(class Vector3);
		float InverseMass();
	private:
		double mass;
		bool useGravity;
		bool isKinematic;

		void CalculateDerivedData();
	private:
		Vector3 position;
		Vector3 velocity;
		Vector3 rotation;
		Matrix4 transformMatrix;
		SpatialComponent* spatial;
		Matrix3 inverseInertiaTensor;
		Matrix3 inverseInertiaTensorWorld;

		/**
		* Holds the angular orientation of the rigid body in
		* world space.
		*/
		Quaternion orientation;

		/**
		* Holds the amount of damping applied to linear
		* motion.
		*/
		float linearDamping;

		/**
		* Holds the amount of damping applied to angular
		* motion.
		*/
		float angularDamping;

		/**
		* Holds the amount of motion of the body. This is a recency
		* weighted mean that can be used to put a body to sleap.
		*/
		float motion;

		/**
		* Holds the accumulated force to be applied at the next
		* integration step.
		*/
		Vector3 forceAccum;

		/**
		* Holds the accumulated torque to be applied at the next
		* integration step.
		*/
		Vector3 torqueAccum;

		/**
		* Holds the acceleration of the rigid body.  This value
		* can be used to set acceleration due to gravity (its primary
		* use), or any other constant acceleration.
		*/
		Vector3 acceleration;

		/**
		* Holds the linear acceleration of the rigid body, for the
		* previous frame.
		*/
		Vector3 lastFrameAcceleration;
	};
}
