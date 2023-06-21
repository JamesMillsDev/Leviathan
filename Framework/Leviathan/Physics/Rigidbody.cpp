#include <Leviathan/Physics/Rigidbody.h>

#include <Leviathan/Physics/PhysicsManager.h>
#include <Leviathan/Physics/Collider.h>
#include <Leviathan/GameObjects/GameObject.h>

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

#include <functional>

#include <raylib/raylib.h>

namespace Leviathan
{
	const vec2& Rigidbody::GetVelocity() const
	{
		return m_velocity;
	}

	const float& Rigidbody::GetAngularVelocity() const
	{
		return m_angularVelocity;
	}

	const float& Rigidbody::GetGravityScale() const
	{
		return m_gravityScale;
	}

	const float& Rigidbody::GetMass() const
	{
		return m_mass;
	}

	const float& Rigidbody::GetFriction() const
	{
		return m_friction;
	}

	const bool& Rigidbody::IsKinematic() const
	{
		return m_isKinematic;
	}

	const bool& Rigidbody::IsStatic() const
	{
		return m_isStatic;
	}

	void Rigidbody::SetVelocity(vec2& _velocity)
	{
		if (m_body != nullptr)
			m_body->SetLinearVelocity({ _velocity.x, _velocity.y });
	}

	void Rigidbody::SetAngularVelocity(float _velocity)
	{
		if (m_body != nullptr)
			m_body->SetAngularVelocity(_velocity);
	}

	void Rigidbody::SetGravityScale(float _scale)
	{
		m_gravityScale = _scale;
		if (m_body != nullptr)
			m_body->SetGravityScale(_scale);
	}

	void Rigidbody::SetMass(float _mass)
	{
		m_mass = _mass;

		if (m_body != nullptr)
		{
			for (b2Fixture* fixture = m_body->GetFixtureList(); fixture; fixture->GetNext())
			{
				fixture->SetDensity(m_mass);
			}

			m_body->ResetMassData();
		}
	}

	void Rigidbody::SetFriction(float _friction)
	{
		m_friction = _friction;

		if (m_body != nullptr)
		{
			for (b2Fixture* fixture = m_body->GetFixtureList(); fixture; fixture->GetNext())
			{
				fixture->SetFriction(m_friction);
			}

			m_body->ResetMassData();
		}
	}

	void Rigidbody::ToggleConstraint(Constraints _constraints)
	{
		m_constraints =
			static_cast<Constraints>(static_cast<int>(m_constraints) ^ static_cast<int>(_constraints));

		if (m_body != nullptr)
		{
			m_body->SetFixedRotation(HasConstraint(Constraints::FreezeRotation));
			SetGravityScale(HasConstraint(Constraints::FreezeY) ? 0 : m_gravityScale);
		}
	}

	Constraints Rigidbody::GetConstraints() const
	{
		return m_constraints;
	}

	void Rigidbody::SetKinematic(bool _isKinematic)
	{
		m_isKinematic = _isKinematic;
		if (m_body != nullptr)
			m_body->SetType(m_isStatic ?
				b2BodyType::b2_staticBody : m_isKinematic ?
				b2BodyType::b2_dynamicBody : b2BodyType::b2_kinematicBody);
	}

	void Rigidbody::SetStatic(bool _isStatic)
	{
		m_isStatic = _isStatic;
		if (m_body != nullptr)
			m_body->SetType(m_isStatic ?
				b2BodyType::b2_staticBody : m_isKinematic ?
				b2BodyType::b2_dynamicBody : b2BodyType::b2_kinematicBody);
	}

	void Rigidbody::SetEnabled(bool _enabled)
	{
		Component::SetEnabled(_enabled);

		if (m_body != nullptr)
			m_body->SetEnabled(_enabled);
	}

	void Rigidbody::ApplyForce(const vec2& _force, ForceMode _mode)
	{
		b2Vec2 force = { _force.x * 100.f, -_force.y * 100.f };

		if (_mode == ForceMode::Impulse)
			m_body->ApplyLinearImpulseToCenter(force, true);
		else if (_mode == ForceMode::Force)
			m_body->ApplyForceToCenter(force, true);
	}

	void Rigidbody::ApplyForceAtPoint(const vec2& _force, const vec2& _point, ForceMode _mode)
	{
		b2Vec2 force = { _force.x * 100.f, -_force.y * 100.f };

		if (_mode == ForceMode::Impulse)
			m_body->ApplyLinearImpulse(force, { _point.x, _point.y }, true);
		else if (_mode == ForceMode::Force)
			m_body->ApplyForce(force, { _point.x, _point.y }, true);
	}

	Rigidbody::Rigidbody(GameObject* _owner)
		: Component(_owner), m_body(nullptr), m_bodyDef(nullptr), m_angularVelocity(0),
		m_velocity({ 0, 0 }), m_constraints(Constraints::None), m_mass(1), m_friction(0.1f),
		m_gravityScale(1), m_isKinematic(false), m_isStatic(false), m_fixtureCount(0)
	{
		_owner->ListenToAddRemoveComponent(&Rigidbody::OnAddRemoveComponent, this);
	}

	Rigidbody::~Rigidbody()
	{
		m_owner->StopListeningToAddRemoveComponent(&Rigidbody::OnAddRemoveComponent, this);

		delete m_bodyDef;
		m_bodyDef = nullptr;
	}

	void Rigidbody::Load()
	{
		if (m_bodyDef == nullptr)
			m_bodyDef = new b2BodyDef();
		vec2 pos = m_owner->Transform()->Position();
		float rot = m_owner->Transform()->Rotation();

		m_bodyDef->position.Set(pos.x, pos.y);
		m_bodyDef->angle = rot * DEG2RAD;
		m_bodyDef->fixedRotation = HasConstraint(Constraints::FreezeRotation);
		m_bodyDef->gravityScale = HasConstraint(Constraints::FreezeY) ? 0 : m_gravityScale;
		m_bodyDef->type = m_isStatic ?
			b2BodyType::b2_staticBody : m_isKinematic ?
			b2BodyType::b2_kinematicBody : b2BodyType::b2_dynamicBody;

		m_body = PhysicsManager::CreateBody(m_bodyDef);
		m_body->SetEnabled(IsEnabled());

		PhysicsManager::ObserveBody(this);
	}

	void Rigidbody::Tick()
	{
		m_velocity = { m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y };
		m_angularVelocity = m_body->GetAngularVelocity();

		b2Vec2 pos = m_body->GetPosition();
		float rotation = m_body->GetAngle() * RAD2DEG;
		m_owner->Transform()->SetPosition(pos.x, pos.y);
		m_owner->Transform()->SetRotation(rotation);

		TryConstrainVelocity();
	}

	void Rigidbody::Unload()
	{
		PhysicsManager::StopObservingBody(this);
	}

	bool Rigidbody::HasConstraint(Constraints _constraint)
	{
		return static_cast<Constraints>(static_cast<int>(m_constraints) & static_cast<int>(_constraint)) == _constraint;
	}

	void Rigidbody::TryConstrainVelocity()
	{
		if (HasConstraint(Constraints::FreezeX) ||
			HasConstraint(Constraints::FreezeY) ||
			HasConstraint(Constraints::FreezePosition))
		{
			vec2 velocity = { m_velocity.x, m_velocity.y };

			if (HasConstraint(Constraints::FreezeX))
				velocity.x = 0;
			if (HasConstraint(Constraints::FreezeY))
				velocity.y = 0;
			if (HasConstraint(Constraints::FreezePosition))
				velocity = { 0, 0 };

			SetVelocity(velocity);
		}
	}

	void Rigidbody::OnAddRemoveComponent(Component* _component, bool _added, Component* _caller)
	{
		// do thing here for when add and remove
		if (_component != _caller)
		{
			if (Collider* collider = dynamic_cast<Collider*>(_component))
			{
				if (Rigidbody* rb = dynamic_cast<Rigidbody*>(_caller))
				{
					if (_added)
					{
						collider->AttachTo(rb->m_body, rb);
						rb->m_fixtureCount++;
					}
					else
					{
						collider->DetachFrom(rb->m_body, rb);
						rb->m_fixtureCount--;
					}
				}
			}
		}
	}
}