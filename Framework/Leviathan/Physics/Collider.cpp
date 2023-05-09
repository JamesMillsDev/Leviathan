#include <Leviathan/Physics/Collider.h>

#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/Physics/Rigidbody.h>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

void Collider::AttachTo(b2Body* _body, Rigidbody* _rb)
{
	m_fixtureDef = new b2FixtureDef();
	m_fixtureDef->shape = m_shape;
	m_fixtureDef->density = _rb->GetMass();
	m_fixtureDef->friction = _rb->GetFriction();

	m_fixture = _body->CreateFixture(m_fixtureDef);
}

void Collider::DetachFrom(b2Body* _body, Rigidbody* _rb)
{
	_body->DestroyFixture(m_fixture);
	m_fixture = nullptr;
}

Collider::Collider(GameObject* _owner)
	: Component(_owner), m_shape(nullptr), m_fixtureDef(nullptr), m_fixture(nullptr)
{

}

Collider::~Collider()
{
	if (m_shape != nullptr)
	{
		delete m_shape;
		m_shape = nullptr;
	}

	if (m_fixtureDef != nullptr)
	{
		delete m_fixtureDef;
		m_fixtureDef = nullptr;
	}
}

void Collider::Load()
{
	m_shape = BuildShape();
}
