#include "BoxCollider.h"
#include "../RenderEngine/RenderInfo.h"
#include "..\ShapeGenerator.h"
#include "..\RenderEngine\RenderEngine.h"
#include "..\SpatialComponent.h"
#include "QtGui/qevent.h"
#include <math.h>
#include "../Physics/RigidBody.h"
#include "../Physics/Vector3.h"
#include "SphereCollider.h"
class SphereCollider;

BoxCollider::~BoxCollider()
{

}

bool BoxCollider::Initialize()
{
	renderInfo = 0;
	collisionData = new Imgn::CollisionData;
	Imgn::ImgnProperties::Instance()->GetAllComponentData(collisionData);
	return true;
}

void BoxCollider::Update(float dt)
{
	Imgn::RigidBody* rigidBody = GetSiblingComponent<Imgn::RigidBody>();
	if (!rigidBody || rigidBody->IsKinematic())
	{
		return;
	}
	SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
	for (int iCurComponent = 0; iCurComponent < collisionData->numComponents; ++iCurComponent)
	{
		if (collisionData->componentNames[iCurComponent] == typeid(BoxCollider*).name())
		{
			//Detect Box Collision.
			for (int jCurCollider = 0; (jCurCollider < collisionData->numSameComponents[iCurComponent] && jCurCollider != GetComponentTypeNum()); ++jCurCollider)
			{
				BoxCollider* collider = reinterpret_cast<BoxCollider*>(collisionData->components[iCurComponent][jCurCollider]);
				if (collider->IsDisabled())
				{
					continue;
				}
				SpatialComponent* colliderSpatial = collider->GetSiblingComponent<SpatialComponent>();

				glm::vec3 colliderCenter = collider->center + colliderSpatial->GetPosition();
				glm::vec3 colliderSize = collider->GetHalfSize();
				glm::vec3 myCenter = center + spatial->GetPosition();
				glm::vec3 mySize = GetHalfSize();

				if (std::abs(myCenter.y - colliderCenter.y) < mySize.y + colliderSize.y)
				{
					if (std::abs(myCenter.x - colliderCenter.x) < mySize.x + colliderSize.x)
					{
						if (std::abs(myCenter.z - colliderCenter.z) < mySize.z + colliderSize.z)
						{
							Imgn::RigidBody* v = this->GetSiblingComponent<Imgn::RigidBody>();
							if (v)
							{
								v->SetVelocity(Imgn::Vector3());
								v->AddForce(v->Gravity() * -1.0f);
							}
							m_owner->Collided(collider->GetOwner());
						}
					}
				}
			}
		}
		else if (collisionData->componentNames[iCurComponent] == typeid(SphereCollider*).name())
		{
			//Detect Sphere Collision.
			for (int jCurCollider = 0; (jCurCollider < collisionData->numSameComponents[iCurComponent] /*&& jCurCollider != GetComponentTypeNum()*/); ++jCurCollider)
			{
				SphereCollider* sphere = reinterpret_cast<SphereCollider*>(collisionData->components[iCurComponent][jCurCollider]);
				if (sphere->IsDisabled())
				{
					continue;
				}
				SpatialComponent* sphereSpatial = sphere->GetSiblingComponent<SpatialComponent>();

				glm::vec3 sphereCenter = sphere->GetCenter() + sphereSpatial->GetPosition();
				float radius = sphere->GetRadius();
				glm::vec3 myCenter = center + spatial->GetPosition();
				glm::vec3 mySize = GetHalfSize();

				float closestX = glm::clamp(sphereCenter.x, myCenter.x - mySize.x, myCenter.x + mySize.x);
				float closestY = glm::clamp(sphereCenter.y, myCenter.y - mySize.y, myCenter.y + mySize.y);
				float closestZ = glm::clamp(sphereCenter.z, myCenter.z - mySize.z, myCenter.z + mySize.z);

				// Calculate the distance between the circle's center and this closest point
				float distanceX = sphereCenter.x - closestX;
				float distanceY = sphereCenter.y - closestY;
				float distanceZ = sphereCenter.z - closestZ;

				// If the distance is less than the circle's radius, an intersection occurs
				float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY) + (distanceZ * distanceZ);
				if (distanceSquared < (radius * radius))
				{
					Imgn::RigidBody* v = sphere->GetSiblingComponent<Imgn::RigidBody>();
					if (isTrigger && isGround)
					{
					}
					else if (isTrigger)
					{
						glm::vec3 curVelocity = glm::vec3();
						if (abs(v->GetVelocity().x) > .25f || abs(v->GetVelocity().z) > .25f)
						{
							curVelocity = v->GetVelocity();
							v->SetVelocity(glm::vec3());
						}
						v->AddForce(rigidBody->GetVelocity() * 2 / dt + (-2.5f * curVelocity));
					}
					else if (isGround)
					{
						
						if (abs(v->GetVelocity().y) > 1.f)
							v->SetVelocity(v->GetVelocity() / 2.0f);
						else if (abs(v->GetVelocity().y) > 0.25f)
						{
							v->SetVelocity(glm::vec3());
							v->SetUseGravity(false);
						}
						if (v->UsingGravity())
						{
							v->SetVelocity(v->GetVelocity() * -1.2f);
						}
					}
					if(!isTrigger && !isGround)
					{
						Imgn::Vector3 vec = v->GetVelocity();
						v->AddForce(vec * -2.0f / dt);
					}

					m_owner->Collided(sphere->GetOwner());
					sphere->GetOwner()->Collided(this->m_owner);
				}

			}
		}
	}
}

void BoxCollider::Draw(float)
{
	
}

void BoxCollider::OnValueChange(std::string VariableName)
{
	if (VariableName == "Center" || VariableName == "Size")
	{
		DisplayCollider("Cube");
	}
}