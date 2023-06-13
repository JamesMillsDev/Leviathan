#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <Leviathan/GameObjects/Component.h>

#include <glm/vec2.hpp>

using glm::vec2;

class b2Shape;
class b2Body;
struct b2FixtureDef;
class b2Fixture;

namespace Leviathan
{
	class Collider : public Component
	{
	public:
		DLL Collider(class GameObject* _owner);
		DLL ~Collider() override;

		DLL void AttachTo(b2Body* _body, const class Rigidbody* _rb);
		DLL void DetachFrom(b2Body* _body, class Rigidbody* _rb);

		DLL void SetCenter(const vec2& _center);
		DLL const vec2& GetCenter() const;

		DLL void SetIsTrigger(bool _isTrigger);
		DLL const bool IsTrigger() const;

	protected:
		friend class GameObject;
		friend class PhysicsManager;

		vec2 m_center;
		b2Shape* m_shape;
		b2FixtureDef* m_fixtureDef;
		b2Fixture* m_fixture;
		bool m_isTrigger;

	protected:
		virtual b2Shape* BuildShape() = 0;
		virtual float GetVolume() = 0;

		DLL void Load() override;

	};
}