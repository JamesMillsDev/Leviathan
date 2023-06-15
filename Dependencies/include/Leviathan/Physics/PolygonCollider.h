#pragma once

#include <Leviathan/Leviathan.h>

#include <Leviathan/Physics/Collider.h>

#include <box2d/b2_math.h>

#include <vector>

using std::vector;

namespace Leviathan
{
    class PolygonCollider final : public Collider
    {
    public:
        DLL PolygonCollider(class GameObject* _owner);

        DLL void AddVert(const vec2& _vert);
        DLL const vector<vec2>& GetVerts() const;

        DLL void ComputeBounds(vec2& _min, vec2& _max) const;

    protected:
        vector<b2Vec2> m_boxVerts;
        vector<vec2> m_verts;

    protected:
        DLL class b2Shape* BuildShape() override;
        DLL float GetVolume() override;

        DLL void OnDrawGizmos() override;
        DLL bool IsPointInBounds(const vec2& _point) const;
        DLL vector<vec2> Voxelize(int _density) const;
    };

}