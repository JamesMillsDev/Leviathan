#include <Leviathan/Physics/EdgeCollider.h>

#include <Leviathan/Gizmos.h>

#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TransformComponent.h>

#include <Leviathan/Physics/PhysicsManager.h>

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include <glm/gtx/vector_angle.hpp>

#include <iostream>

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

void EdgeCollider::ComputeBounds(vec2& _min, vec2& _max)
{
	float xMin = FLT_MAX, yMin = FLT_MAX;
	float xMax = FLT_MIN, yMax = FLT_MIN;

	for (auto& vert : m_verts)
	{
		xMin = fminf(xMin, vert.x);
		yMin = fminf(yMin, vert.y);
		xMax = fmaxf(xMax, vert.x);
		yMax = fmaxf(yMax, vert.y);
	}

	_min.x = xMin;
	_min.y = yMin;
	_max.x = xMax;
	_max.y = yMax;
}

DLL b2Shape* EdgeCollider::BuildShape()
{
	b2PolygonShape* polygon = new b2PolygonShape();
	polygon->Set((m_boxVerts).data(), m_boxVerts.size());

	return polygon;
}

float EdgeCollider::GetVolume()
{
	int density = PhysicsManager::PolygonCollisionDensity();
	vector<vec2> voxels = Voxelize(density);

	return (density * density) * voxels.size();
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

bool EdgeCollider::IsPointInBounds(vec2& _point)
{
	vec2 a = m_verts[0] - _point;
	vec2 b = m_verts[m_verts.size() - 1] - _point;

	float angle = glm::angle(a, b);
	for (int i = 0; i < m_verts.size() - 1; i++)
	{
		a = m_verts[i] - _point;
		b = m_verts[i + 1] - _point;

		angle += glm::angle(a, b);
	}

	std::cout << angle << std::endl;

	return angle == 2 * PI;
}

vector<vec2> EdgeCollider::Voxelize(int _density)
{
	vec2 bMin = {}, bMax = {};
	ComputeBounds(bMin, bMax);

	vector<vec2> points;

	for (int x = bMin.x; x < bMax.x; x += _density)
	{
		for (int y = bMin.y; y < bMax.y; y += _density)
		{
			vec2 point = { x, y };
			if (IsPointInBounds(point))
			{
				points.push_back(point);
			}
		}
	}

	return points;
}
