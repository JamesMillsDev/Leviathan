#include <Leviathan/Physics/PolygonCollider.h>

#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TransformComponent.h>

#include <Leviathan/Physics/PhysicsManager.h>

#include <Leviathan/Utils/Gizmos.h>

#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

#include <glm/gtx/vector_angle.hpp>

namespace Leviathan
{
	PolygonCollider::PolygonCollider(GameObject* _owner)
		: Collider(_owner)
	{
	}

	void PolygonCollider::AddVert(const vec2& _vert)
	{
		m_boxVerts.emplace_back(_vert.x, _vert.y);
		m_verts.emplace_back(_vert);
	}

	const vector<vec2>& PolygonCollider::GetVerts() const
	{
		return m_verts;
	}

	void PolygonCollider::ComputeBounds(vec2& _min, vec2& _max) const
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

	DLL b2Shape* PolygonCollider::BuildShape()
	{
		b2PolygonShape* polygon = new b2PolygonShape();
		polygon->Set(m_boxVerts.data(), (int32)m_boxVerts.size());

		return polygon;
	}

	float PolygonCollider::GetVolume()
	{
		const int density = PhysicsManager::PolygonCollisionDensity();
		const vector<vec2> voxels = Voxelize(density);

		return (float)(density * density * voxels.size());  // NOLINT(bugprone-implicit-widening-of-multiplication-result)
	}

	void PolygonCollider::OnDrawGizmos()
	{
		vector<vec2> verts;
		for (auto& vert : m_verts)
		{
			b2Vec2 v = m_fixture->GetBody()->GetWorldPoint({ vert.x, vert.y });
			verts.emplace_back(v.x, v.y);
		}

		Gizmos::DrawPolyShape(verts, m_center);
	}

	bool PolygonCollider::IsPointInBounds(const vec2& _point) const
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

		return angle == 2 * PI;
	}

	vector<vec2> PolygonCollider::Voxelize(int _density) const
	{
		vec2 bMin = {}, bMax = {};
		ComputeBounds(bMin, bMax);

		vector<vec2> points;

		for (int x = (int)bMin.x; x < (int)bMax.x; x += _density)
		{
			for (int y = (int)bMin.y; y < (int)bMax.y; y += _density)
			{
				vec2 point = { x, y };
				if (IsPointInBounds(point))
					points.push_back(point);
			}
		}

		return points;
	}
}
