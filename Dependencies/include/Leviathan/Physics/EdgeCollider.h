#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Physics/Collider.h>

#include <box2d/b2_math.h>

#include <vector>

using std::vector;

class EdgeCollider : public Collider
{
public:
	DLL EdgeCollider(class GameObject* _owner);

	DLL void AddVert(const vec2& _vert);
	DLL const vector<vec2>& GetVerts() const;

protected:
	vector<b2Vec2> m_boxVerts;
	vector<vec2> m_verts;

protected:
	DLL virtual class b2Shape* BuildShape() override;

	DLL virtual void OnDrawGizmos() override;

};