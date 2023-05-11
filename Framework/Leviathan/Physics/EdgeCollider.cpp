#include <Leviathan/Physics/EdgeCollider.h>

#include <Leviathan/Gizmos.h>
#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TransformComponent.h>

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

EdgeCollider::EdgeCollider(GameObject* _owner)
	: Collider(_owner)
{
}

void EdgeCollider::AddVert(const vec2& _vert)
{
	m_boxVerts.emplace_back(_vert.x, _vert.y);
	m_verts.emplace_back(_vert);
}

const vector<vec2>& EdgeCollider::GetVerts() const
{
	return m_verts;
}

DLL b2Shape* EdgeCollider::BuildShape()
{
	b2PolygonShape* polygon = new b2PolygonShape();
	polygon->Set((m_boxVerts).data(), m_boxVerts.size());

	return polygon;
}

void EdgeCollider::OnDrawGizmos()
{
	TransformComponent* transform = m_owner->Transform();

	vector<vec2> verts;
	for (auto& vert : m_verts)
	{
		b2Vec2 v = m_fixture->GetBody()->GetWorldPoint({ vert.x, vert.y });
		verts.push_back({ v.x, v.y });
	}

	Gizmos::DrawPolyShape(verts, m_center);
}
