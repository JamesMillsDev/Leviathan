#include <Leviathan/Physics/CircleCollider.h>

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

CircleCollider::CircleCollider(GameObject* _owner)
    : Collider(_owner), m_center(vec2(0.f)), m_radius(10.f)
{
}

void CircleCollider::SetCenter(const vec2& _center)
{
    m_center = _center;
}

void CircleCollider::SetRadius(const float& _radius)
{
    m_radius = _radius;
}

const vec2& CircleCollider::GetCenter() const
{
    return m_center;
}

const float& CircleCollider::GetRadius() const
{
    return m_radius;
}

DLL b2Shape* CircleCollider::BuildShape()
{
    b2CircleShape* circle = new b2CircleShape();
    circle->m_radius = m_radius;
    circle->m_p = { m_center.x, m_center.y };

    return circle;
}
