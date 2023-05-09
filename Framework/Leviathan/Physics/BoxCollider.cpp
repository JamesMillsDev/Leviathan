#include <Leviathan/Physics/BoxCollider.h>

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

BoxCollider::BoxCollider(GameObject* _owner)
    : Collider(_owner), m_center(vec2(0.f)), m_extents(vec2(10.f))
{
}

void BoxCollider::SetCenter(const vec2& _center)
{
    m_center = _center;
}

void BoxCollider::SetExtents(const vec2& _extents)
{
    m_extents = _extents;
}

const vec2& BoxCollider::GetCenter() const
{
    return m_center;
}

const vec2& BoxCollider::GetExtents() const
{
    return m_extents;
}

b2Shape* BoxCollider::BuildShape()
{
    b2Vec2 points[4]
    {
        { m_center.x - m_extents.x, m_center.y - m_extents.y },
        { m_center.x + m_extents.x, m_center.y - m_extents.y },
        { m_center.x + m_extents.x, m_center.y + m_extents.y },
        { m_center.x - m_extents.x, m_center.y + m_extents.y }
    };

    b2PolygonShape* polygon = new b2PolygonShape();
    polygon->Set(points, 4);

    return polygon;
}
