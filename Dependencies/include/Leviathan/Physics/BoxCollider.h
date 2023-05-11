#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Physics/Collider.h>

#include <glm/vec2.hpp>

using glm::vec2;

class BoxCollider : public Collider
{
public:
	DLL BoxCollider(class GameObject* _owner);

	DLL void SetExtents(const vec2& _extents);

	DLL const vec2& GetExtents() const;

protected:
	vec2 m_extents;

protected:
	DLL virtual class b2Shape* BuildShape() override;
	DLL virtual float GetVolume() override;

	DLL virtual void OnDrawGizmos() override;

};