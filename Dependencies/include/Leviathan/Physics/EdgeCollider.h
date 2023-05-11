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

	DLL virtual void ComputeBounds(vec2& _min, vec2& _max);

protected:
	vector<b2Vec2> m_boxVerts;
	vector<vec2> m_verts;

protected:
	DLL virtual class b2Shape* BuildShape() override;
	DLL virtual float GetVolume() override;

	DLL virtual void OnDrawGizmos() override;
	DLL bool IsPointInBounds(vec2& _point);
	DLL vector<vec2> Voxelize(int _density);

};