#include <Leviathan/Physics/BoxCollider.h>

#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TransformComponent.h>

#include <Leviathan/Utils/Gizmos.h>

#include <box2d/b2_polygon_shape.h>

#include <raylib/raylib.h>

namespace Leviathan
{
    BoxCollider::BoxCollider(GameObject* _owner)
        : Collider(_owner), m_extents(vec2(10.f))
    {
    }

    void BoxCollider::SetExtents(const vec2& _extents)
    {
        m_extents = _extents;
    }

    const vec2& BoxCollider::GetExtents() const
    {
        return m_extents;
    }

    b2Shape* BoxCollider::BuildShape()
    {
        const b2Vec2 points[4]
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

    float BoxCollider::GetVolume()
    {
        return (m_extents.x * 2.f) + (m_extents.y * 2.f);
    }

    void BoxCollider::OnDrawGizmos()
    {
        const TransformComponent* transform = m_owner->Transform();

        Gizmos::DrawWireRect(transform->AnchoredPosition() + m_center, m_extents, transform->Rotation());
    }
}
