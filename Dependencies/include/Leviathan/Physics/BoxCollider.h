#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <Leviathan/Physics/Collider.h>

#include <glm/vec2.hpp>

using glm::vec2;

namespace Leviathan
{
	class BoxCollider final : public Collider
	{
	public:
		DLL BoxCollider(class GameObject* _owner);

		DLL void SetExtents(const vec2& _extents);

		DLL const vec2& GetExtents() const;

	protected:
		vec2 m_extents;

	protected:
		DLL class b2Shape* BuildShape() override;
		DLL float GetVolume() override;

		DLL void OnDrawGizmos() override;

	};
}