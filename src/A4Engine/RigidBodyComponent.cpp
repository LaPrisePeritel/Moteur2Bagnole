#include <A4Engine/RigidBodyComponent.hpp>
#include <algorithm>

RigidBodyComponent::RigidBodyComponent(float mass, float width, float height)
{
	m_body = cpBodyNew(mass, cpMomentForBox(mass, width, height));
}

RigidBodyComponent::~RigidBodyComponent()
{
	cpBodyFree(m_body);
}

cpBody* RigidBodyComponent::GetBody()
{
	return m_body;
}

cpVect RigidBodyComponent::GetPosition()
{
	return cpBodyGetPosition(m_body);
}

float RigidBodyComponent::GetAngle()
{
	return cpBodyGetAngle(m_body);
}

void RigidBodyComponent::SetPosition(cpVect pos)
{
	cpBodySetPosition(m_body, pos);
}

void RigidBodyComponent::SetAngle(float angle)
{
	cpBodySetAngle(m_body, angle);
}

void RigidBodyComponent::AddShape(Shape* shape)
{
	shape->CreateShape(m_body);
	m_shapeBank.push_back(shape);
	SetMoment();
}

void RigidBodyComponent::RemoveShape(Shape* shape)
{
	m_shapeBank.erase(std::find(m_shapeBank.begin(), m_shapeBank.end(), shape));
}

void RigidBodyComponent::SetMoment()
{
	float tmp = 0;
	for (const auto& shape : m_shapeBank) {
		tmp += shape->GetMoment(cpBodyGetMass(m_body));
	}

	cpBodySetMoment(m_body, tmp);
}
