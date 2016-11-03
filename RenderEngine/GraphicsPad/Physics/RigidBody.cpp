#include "RigidBody.h"
#include "..\SpatialComponent.h"
#include "..\MeshComponent.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>

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
		acceleration = Vector3(0,-9.8f,0);
		spatial = GetSiblingComponent<SpatialComponent>();
		if (spatial)
		{
			position = spatial->position;
			rotation = glm::eulerAngles(spatial->GetRotate());
		}
		return true;
	}

	void RigidBody::Update(float dt)
	{
		Integrate(dt);
	}

	static inline void TransformInertiaTensor(Matrix3 &iitWorld, const Quaternion &q,
		const Matrix3 &iitBody, const Matrix4 &rotmat)
	{
		real t4 = rotmat.data[0] * iitBody.data[0] +
			rotmat.data[1] * iitBody.data[3] +
			rotmat.data[2] * iitBody.data[6];
		real t9 = rotmat.data[0] * iitBody.data[1] +
			rotmat.data[1] * iitBody.data[4] +
			rotmat.data[2] * iitBody.data[7];
		real t14 = rotmat.data[0] * iitBody.data[2] +
			rotmat.data[1] * iitBody.data[5] +
			rotmat.data[2] * iitBody.data[8];
		real t28 = rotmat.data[4] * iitBody.data[0] +
			rotmat.data[5] * iitBody.data[3] +
			rotmat.data[6] * iitBody.data[6];
		real t33 = rotmat.data[4] * iitBody.data[1] +
			rotmat.data[5] * iitBody.data[4] +
			rotmat.data[6] * iitBody.data[7];
		real t38 = rotmat.data[4] * iitBody.data[2] +
			rotmat.data[5] * iitBody.data[5] +
			rotmat.data[6] * iitBody.data[8];
		real t52 = rotmat.data[8] * iitBody.data[0] +
			rotmat.data[9] * iitBody.data[3] +
			rotmat.data[10] * iitBody.data[6];
		real t57 = rotmat.data[8] * iitBody.data[1] +
			rotmat.data[9] * iitBody.data[4] +
			rotmat.data[10] * iitBody.data[7];
		real t62 = rotmat.data[8] * iitBody.data[2] +
			rotmat.data[9] * iitBody.data[5] +
			rotmat.data[10] * iitBody.data[8];

		iitWorld.data[0] = t4*rotmat.data[0] +
			t9*rotmat.data[1] +
			t14*rotmat.data[2];
		iitWorld.data[1] = t4*rotmat.data[4] +
			t9*rotmat.data[5] +
			t14*rotmat.data[6];
		iitWorld.data[2] = t4*rotmat.data[8] +
			t9*rotmat.data[9] +
			t14*rotmat.data[10];
		iitWorld.data[3] = t28*rotmat.data[0] +
			t33*rotmat.data[1] +
			t38*rotmat.data[2];
		iitWorld.data[4] = t28*rotmat.data[4] +
			t33*rotmat.data[5] +
			t38*rotmat.data[6];
		iitWorld.data[5] = t28*rotmat.data[8] +
			t33*rotmat.data[9] +
			t38*rotmat.data[10];
		iitWorld.data[6] = t52*rotmat.data[0] +
			t57*rotmat.data[1] +
			t62*rotmat.data[2];
		iitWorld.data[7] = t52*rotmat.data[4] +
			t57*rotmat.data[5] +
			t62*rotmat.data[6];
		iitWorld.data[8] = t52*rotmat.data[8] +
			t57*rotmat.data[9] +
			t62*rotmat.data[10];
	}

	static inline void CalculateTransformMatrix(Matrix4 &transformMatrix,
		const Vector3 &position,
		const Quaternion &orientation)
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

	glm::mat4 RigidBody::GetGLTransform() const
	{
		return glm::mat4((float)transformMatrix.data[0], (float)transformMatrix.data[4], (float)transformMatrix.data[8], 0
			, (float)transformMatrix.data[1], (float)transformMatrix.data[5], transformMatrix.data[9], 0
			, (float)transformMatrix.data[2], (float)transformMatrix.data[6], (float)transformMatrix.data[10], 0
			, (float)transformMatrix.data[3], (float)transformMatrix.data[7], (float)transformMatrix.data[11], 1);
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
		Enable();
	}

	void RigidBody::addForceAtPoint(const Vector3 &force, const Vector3 &point)
	{
		Vector3 pt = point;
		pt -= position;

		forceAccum += force;
		torqueAccum += pt % force;

		Enable();
	}

	void RigidBody::addRotation(const Vector3 &deltaRotation)
	{
		rotation += deltaRotation;
	}

	void RigidBody::SetVelocity(class Vector3 vec)
	{
		velocity = vec;
	}

	void RigidBody::CalculateDerivedData()
	{
		spatial->SetPosition(position.toVec3());
		spatial->velocity = velocity.toVec3();
		
		orientation.normalise();
		MeshComponent* mesh = GetSiblingComponent<MeshComponent>();
		if (mesh)
		{
			TransformInfo* info = mesh->renderinfo.getTransformInfo();
			info->m_rotateTransform = glm::mat4_cast(orientation.toQuat());
		}
		// Calculate the transform matrix for the body.
		CalculateTransformMatrix(transformMatrix, position, orientation);

		// Calculate the inertiaTensor in world space.
		TransformInertiaTensor(inverseInertiaTensorWorld, orientation, 
			inverseInertiaTensor, transformMatrix);
	}

	float RigidBody::InverseMass()
	{
		return 1 / mass;
	}

}