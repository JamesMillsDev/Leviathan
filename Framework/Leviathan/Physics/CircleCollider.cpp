#include <Leviathan/Physics/CircleCollider.h>

#include <Leviathan/Gizmos.h>
#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TransformComponent.h>

#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>

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

float CircleCollider::GetVolume()
{
    return PI * m_radius * m_radius;
}

void CircleCollider::OnDrawGizmos()
{
    TransformComponent* transform = m_owner->Transform();

    Gizmos::DrawWireCircle(transform->Position() + m_center, m_radius);
}
