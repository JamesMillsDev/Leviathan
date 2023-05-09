#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/GameObjects/Component.h>

class Collider : public Component
{
public:
	DLL Collider(class GameObject* _owner);
	DLL ~Collider();

	DLL void AttachTo(class b2Body* _body, class Rigidbody* _rb);
	DLL void DetachFrom(class b2Body* _body, class Rigidbody* _rb);

protected:
	friend class GameObject;

protected:
	virtual class b2Shape* BuildShape() = 0;

	DLL virtual void Load() override;

private:
	class b2Shape* m_shape;
	struct b2FixtureDef* m_fixtureDef;
	class b2Fixture* m_fixture;

};