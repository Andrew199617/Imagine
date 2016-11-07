#pragma once
#include "..\ImgnComponent.h"
#include "..\ImgnProperties.h"
#include "Matrix3.h"
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
			IMGN_PROPERTY(gravity, glm::vec3(0.0,9.8f,0.0f))
			IMGN_PROPERTY(useGravity, true)
			IMGN_PROPERTY(isKinematic, false)
			IMGN_END(RigidBody)
	public:
		virtual void Awake() override;
		virtual bool Initialize() override;
		virtual void Update(float dt) override;

		void Integrate(float duration);
		bool HasFiniteMass();
		void SetInertiaTensor(const Matrix3 InertiaTensor);
		void SetOrientation(const real r, const real i,
			const real j, const real k);

		/**
		* Applies the given change in velocity.
		*/
		void AddVelocity(const Vector3 &deltaVelocity);
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
		Vector3 GetVelocity();
		float InverseMass();
		bool IsKinematic() const { return isKinematic; }
		void SetIsKinematic(bool val) { isKinematic = val; }
		/************************************************************************/
		/* Is the RigidBody using Gravity.
		/************************************************************************/
		bool UsingGravity() const { return useGravity; }
		/************************************************************************/
		/* Will the RigidBody use Gravity.
		/************************************************************************/
		void SetUseGravity(bool val) { useGravity = val; }
		double GetMass() const { return mass; }
		void SetMass(double val) { mass = val; }
		/************************************************************************/
		/* Get the value the RigidBody is using for Gravity.
		/************************************************************************/
		Vector3 Gravity() { return Vector3(gravity.x, gravity.y, gravity.z); }
		/************************************************************************/
		/* Set the value the RigidBody will use for Gravity.
		/************************************************************************/
		void SetGravity(Imgn::Vector3 val) { gravity = val.toVec3(); }

		Imgn::Vector3 GetForceAccum() const { return forceAccum; }
		void SetForceAccum(Imgn::Vector3 val) { forceAccum = val; }
	private:
		void ClearAccumulators();
		void CalculateDerivedData();

	private:
		double mass;
		bool useGravity;
		bool isKinematic;
		Vector3 position;
		Vector3 velocity;
		Vector3 rotation;
		glm::vec3 gravity;
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
