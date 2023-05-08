#include <Leviathan/Physics/Rigidbody.h>

#include <Leviathan/Physics/PhysicsManager.h>

Rigidbody::Rigidbody(class GameObject* _owner)
	: Component(_owner), m_body(nullptr), m_bodyDef(nullptr)
{
}

void Rigidbody::Load()
{
}

void Rigidbody::Tick()
{
}

void Rigidbody::Unload()
{
}
