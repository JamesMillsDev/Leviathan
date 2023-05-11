#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/GameObjects/Component.h>

#include <glm/vec2.hpp>

using glm::vec2;

class Collider : public Component
{
public:
	DLL Collider(class GameObject* _owner);
	DLL ~Collider();

	DLL void AttachTo(class b2Body* _body, class Rigidbody* _rb);
	DLL void DetachFrom(class b2Body* _body, class Rigidbody* _rb);

	DLL void SetCenter(const vec2& _center);
	DLL const vec2& GetCenter() const;

protected:
	friend class GameObject;

	vec2 m_center;
	class b2Shape* m_shape;
	struct b2FixtureDef* m_fixtureDef;
	class b2Fixture* m_fixture;

protected:
	virtual class b2Shape* BuildShape() = 0;

	DLL virtual void Load() override;

};