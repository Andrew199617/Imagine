#include "RigidBody.h"
#include "..\SpatialComponent.h"
#include "..\MeshComponent.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include "Matrix4.h"

namespace Imgn
{
	RigidBody::~RigidBody()
	{
	}

	void RigidBody::Awake()
	{
	}

	bool RigidBody::Initialize()
	{
		SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
		if (spatial)
		{
			position = spatial->position;
			rotation = glm::eulerAngles(spatial->GetRotate());
		}
		return true;
	}

	void RigidBody::Update(float dt)
	{
		SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
		if (spatial)
		{
			position = spatial->position;
			orientation = Imgn::Quaternion(spatial->GetRotate().w, spatial->GetRotate().x, spatial->GetRotate().y, spatial->GetRotate().z);
		}
		if (useGravity)
		{
			AddForce(Gravity());
		}
		Integrate(dt);
	}

	void RigidBody::Integrate(float duration)
	{
		// Calculate linear acceleration from force inputs.
		lastFrameAcceleration = acceleration;
		lastFrameAcceleration.addScaledVector(forceAccum, InverseMass());

		// Calculate angular acceleration from torque inputs.
		Vector3 angularAcceleration = inverseInertiaTensorWorld.transform(torqueAccum);

		// Adjust velocities
		// Update linear velocity from both acceleration and impulse.
		velocity.addScaledVector(lastFrameAcceleration, duration);

		// Update angular velocity from both acceleration and impulse.
		rotation.addScaledVector(angularAcceleration, duration);

		// Impose drag.
		velocity *= real_pow(linearDamping, duration);
		rotation *= real_pow(angularDamping, duration);

		// Adjust positions
		// Update linear position.
		position.addScaledVector(velocity, duration);

		// Update angular position.
		orientation.addScaledVector(rotation, duration);

		// Normalise the orientation, and update the matrices with the new
		// position and orientation
		CalculateDerivedData();

		// Clear accumulators.
		ClearAccumulators();

		// Update the kinetic energy store, and possibly put the body to
		// sleep.
		/*if (canSleep) {
			real currentMotion = velocity.scalarProduct(velocity) +
				rotation.scalarProduct(rotation);

			real bias = real_pow(0.5, duration);
			motion = bias*motion + (1 - bias)*currentMotion;

			if (motion < sleepEpsilon) Component::Disable();
			else if (motion > 10 * sleepEpsilon) motion = 10 * sleepEpsilon;
		}*/
	}

	bool RigidBody::HasFiniteMass()
	{
		return InverseMass() >= 0.0f;
	}

	void RigidBody::SetInertiaTensor(const Matrix3 InertiaTensor)
	{
		inverseInertiaTensor.setInverse(InertiaTensor);
		//_checkInverseInertiaTensor(inverseInertiaTensor);
	}

	void RigidBody::SetOrientation(const real r, const real i, const real j, const real k)
	{
		orientation.r = r;
		orientation.i = i;
		orientation.j = j;
		orientation.k = k;
		orientation.normalise();
	}

	void RigidBody::AddVelocity(const Vector3 &deltaVelocity)
	{
		velocity += deltaVelocity;
	}

	void RigidBody::ClearAccumulators()
	{
		forceAccum.clear();
		torqueAccum.clear();
	}

	void RigidBody::AddForce(const Vector3 &force)
	{
		forceAccum += force;
		//Enable();
	}

	void RigidBody::addForceAtPoint(const Vector3 &force, const Vector3 &point)
	{
		Vector3 pt = point;
		pt -= position;

		forceAccum += force;
		torqueAccum += pt % force;

		//Enable();
	}

	void RigidBody::addRotation(const Vector3 &deltaRotation)
	{
		rotation += deltaRotation;
	}

	void RigidBody::SetVelocity(class Vector3 vec)
	{
		velocity = vec;
	}

	Vector3 RigidBody::GetVelocity()
	{
		return velocity;
	}

	static void CalculateTransformMatrix(Matrix4 &transformMatrix, const Vector3 &position, const Quaternion &orientation)
	{
		transformMatrix.data[0] = 1 - 2 * orientation.j*orientation.j -
			2 * orientation.k*orientation.k;
		transformMatrix.data[1] = 2 * orientation.i*orientation.j -
			2 * orientation.r*orientation.k;
		transformMatrix.data[2] = 2 * orientation.i*orientation.k +
			2 * orientation.r*orientation.j;
		transformMatrix.data[3] = position.x;

		transformMatrix.data[4] = 2 * orientation.i*orientation.j +
			2 * orientation.r*orientation.k;
		transformMatrix.data[5] = 1 - 2 * orientation.i*orientation.i -
			2 * orientation.k*orientation.k;
		transformMatrix.data[6] = 2 * orientation.j*orientation.k -
			2 * orientation.r*orientation.i;
		transformMatrix.data[7] = position.y;

		transformMatrix.data[8] = 2 * orientation.i*orientation.k -
			2 * orientation.r*orientation.j;
		transformMatrix.data[9] = 2 * orientation.j*orientation.k +
			2 * orientation.r*orientation.i;
		transformMatrix.data[10] = 1 - 2 * orientation.i*orientation.i -
			2 * orientation.j*orientation.j;
		transformMatrix.data[11] = position.z;
	}

	void RigidBody::CalculateDerivedData()
	{
		SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
		if (spatial)
		{
			spatial->SetPosition(position.toVec3());
			spatial->velocity = velocity.toVec3();
		}
		
		orientation.normalise();
		MeshComponent* mesh = GetSiblingComponent<MeshComponent>();
		if (mesh)
		{
			TransformInfo* info = mesh->renderinfo.getTransformInfo();
			info->m_rotateTransform = glm::mat4_cast(orientation.toQuat());
			// Calculate the transform matrix for the body.
			//CalculateTransformMatrix(transformMatrix, position, orientation);
		}

		// Calculate the inertiaTensor in world space.
		//TransformInertiaTensor(inverseInertiaTensorWorld, orientation, 
		//	inverseInertiaTensor, transformMatrix);
	}

	float RigidBody::InverseMass()
	{
		return 1 / GetMass();
	}

	

}