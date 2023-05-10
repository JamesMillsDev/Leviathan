#include <Leviathan/Physics/EdgeCollider.h>

#include <Box2D/Collision/Shapes/b2PolygonShape.h>

EdgeCollider::EdgeCollider(GameObject* _owner)
	: Collider(_owner)
{
}

void EdgeCollider::AddVert(const vec2& _vert)
{
	m_verts.push_back(_vert);
}

const vector<vec2>& EdgeCollider::GetVerts() const
{
	return m_verts;
}

DLL b2Shape* EdgeCollider::BuildShape()
{
	b2Vec2* verts = new b2Vec2[m_verts.size()];
	int i = 0;
	for (auto iter = m_verts.begin(); iter != m_verts.end(); iter++, i++)
	{
		verts[i] = { iter->x + m_center.x, iter->y + m_center.y };
	}

	b2PolygonShape* polygon = new b2PolygonShape();
	polygon->Set(verts, m_verts.size());

	return polygon;
}
