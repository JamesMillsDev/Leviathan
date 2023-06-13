#include <Leviathan/Physics/Collider.h>

#include <Leviathan/Core/Application.h>

#include <Leviathan/GameObjects/GameObject.h>

#include <Leviathan/Physics/Rigidbody.h>
#include <Leviathan/Physics/PhysicsManager.h>

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

namespace Leviathan
{
	Collider::Collider(GameObject* _owner)
		: Component(_owner), m_center(vec2(0.f)), m_shape(nullptr),
		m_fixtureDef(nullptr), m_fixture(nullptr), m_isTrigger(false)
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

	void Collider::AttachTo(b2Body* _body, const Rigidbody* _rb)
	{
		int w = 0, h = 0;
		Application::GetWindowSize(w, h);

		m_fixtureDef = new b2FixtureDef();
		m_fixtureDef->shape = m_shape;
		m_fixtureDef->density = _rb->GetMass() / GetVolume();
		m_fixtureDef->friction = _rb->GetFriction();
		m_fixtureDef->isSensor = m_isTrigger;

		m_fixture = _body->CreateFixture(m_fixtureDef);
		PhysicsManager::ObserveCollider(this);
	}

	void Collider::DetachFrom(b2Body* _body, Rigidbody* _rb)
	{
		PhysicsManager::StopObservingCollider(this);
		_body->DestroyFixture(m_fixture);
		m_fixture = nullptr;
	}

	void Collider::SetCenter(const vec2& _center)
	{
		m_center = _center;
	}

	const vec2& Collider::GetCenter() const
	{
		return m_center;
	}

	void Collider::Load()
	{
		m_shape = BuildShape();
	}

	void Collider::SetIsTrigger(bool _isTrigger)
	{
		m_isTrigger = _isTrigger;
		if (m_fixture != nullptr)
		{
			m_fixture->SetSensor(m_isTrigger);
		}
	}

	const bool Collider::IsTrigger() const
	{
		return m_isTrigger;
	}
}