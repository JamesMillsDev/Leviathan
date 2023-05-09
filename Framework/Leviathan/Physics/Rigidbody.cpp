#include <Leviathan/Physics/Rigidbody.h>

#include <Leviathan/Physics/PhysicsManager.h>
#include <Leviathan/GameObjects/GameObject.h>

#include <Box2D/Dynamics/b2Body.h>

#include <functional>

const Vec2& Rigidbody::GetVelocity() const
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

const bool& Rigidbody::IsRotationLocked() const
{
	return m_lockRotation;
}

const bool& Rigidbody::IsKinematic() const
{
	return m_isKinematic;
}

const bool& Rigidbody::IsStatic() const
{
	return m_isStatic;
}

void Rigidbody::SetVelocity(Vec2& _velocity)
{
	m_body->SetLinearVelocity(_velocity);
}

void Rigidbody::SetAngularVelocity(float _velocity)
{
	m_body->SetAngularVelocity(_velocity);
}

void Rigidbody::SetGravityScale(float _scale)
{
	m_gravityScale = _scale;
	m_body->SetGravityScale(_scale);
}

void Rigidbody::LockRotation(bool _locked)
{
	m_lockRotation = _locked;
	m_body->SetFixedRotation(_locked);
}

void Rigidbody::SetKinematic(bool _isKinematic)
{
	m_isKinematic = _isKinematic;
	m_body->SetType(m_isStatic ?
		b2BodyType::b2_staticBody : m_isKinematic ?
		b2BodyType::b2_dynamicBody : b2BodyType::b2_kinematicBody);
}

void Rigidbody::SetStatic(bool _isStatic)
{
	m_isStatic = _isStatic;
	m_body->SetType(m_isStatic ?
		b2BodyType::b2_staticBody : m_isKinematic ?
		b2BodyType::b2_dynamicBody : b2BodyType::b2_kinematicBody);
}

void Rigidbody::SetEnabled(bool _enabled)
{
	Component::SetEnabled(_enabled);

	if (m_body != nullptr)
		m_body->SetActive(_enabled);
}

Rigidbody::Rigidbody(GameObject* _owner)
	: Component(_owner), m_body(nullptr), m_bodyDef(nullptr), m_angularVelocity(0),
	m_velocity({ 0, 0 }), m_lockRotation(false), m_gravityScale(1), m_isKinematic(false),
	m_isStatic(false)
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
	Vec2 pos = m_owner->Transform()->Position();
	float rot = m_owner->Transform()->Rotation();

	m_bodyDef->position.Set(pos.x, pos.y);
	m_bodyDef->angle = rot * DEG_2_RAD;
	m_bodyDef->fixedRotation = m_lockRotation;
	m_bodyDef->gravityScale = m_gravityScale;
	m_bodyDef->type = m_isStatic ?
		b2BodyType::b2_staticBody : m_isKinematic ?
		b2BodyType::b2_kinematicBody : b2BodyType::b2_dynamicBody;

	m_body = PhysicsManager::CreateBody(m_bodyDef);
	m_body->SetActive(IsEnabled());
}

void Rigidbody::Tick()
{
	m_velocity = { m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y };
	m_angularVelocity = m_body->GetAngularVelocity();

	b2Vec2 pos = m_body->GetPosition();
	float32 rotation = m_body->GetAngle() * RAD_2_DEG;
	m_owner->Transform()->SetPosition(pos.x, pos.y);
	m_owner->Transform()->SetRotation(rotation);
}

void Rigidbody::Unload()
{
}

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

void Rigidbody::OnAddRemoveComponent(Component* _component, bool _added, Component* _caller)
{
	// do thing here for when add and remove
	if (_component == _caller)
	{
		if (Rigidbody* rb = dynamic_cast<Rigidbody*>(_caller))
		{
			Vec2 scale = rb->m_owner->Transform()->Scale();

			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(scale.x / 2, scale.y / 2);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.3f;

			rb->m_body->CreateFixture(&fixtureDef);
		}
	}
}