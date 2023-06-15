#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Physics/Collider.h>

#include <glm/vec2.hpp>

using glm::vec2;

namespace Leviathan
{
	class CircleCollider final : public Collider
	{
	public:
		DLL CircleCollider(class GameObject* _owner);

		DLL void SetRadius(const float& _radius);

		DLL const float& GetRadius() const;

	protected:
		float m_radius;

	protected:
		DLL class b2Shape* BuildShape() override;
		DLL float GetVolume() override;

		DLL void OnDrawGizmos() override;

	};


}