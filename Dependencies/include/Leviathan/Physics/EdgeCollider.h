#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Physics/Collider.h>

#include <vector>

using std::vector;

class EdgeCollider : public Collider
{
public:
	DLL EdgeCollider(class GameObject* _owner);

	DLL void AddVert(const vec2& _vert);
	DLL const vector<vec2>& GetVerts() const;

protected:
	vector<vec2> m_verts;

protected:
	DLL virtual class b2Shape* BuildShape() override;

};