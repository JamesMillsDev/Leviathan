#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Physics/Collider.h>

#include <glm/vec2.hpp>

using glm::vec2;

class CircleCollider : public Collider
{
public:
	DLL CircleCollider(class GameObject* _owner);

	DLL void SetCenter(const vec2& _center);
	DLL void SetRadius(const float& _radius);

	DLL const vec2& GetCenter() const;
	DLL const float& GetRadius() const;

protected:
	vec2 m_center;
	float m_radius;

protected:
	DLL virtual class b2Shape* BuildShape() override;

};

