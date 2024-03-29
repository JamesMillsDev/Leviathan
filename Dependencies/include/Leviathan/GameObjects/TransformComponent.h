#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <functional>
#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

using std::function;
using std::vector;

using glm::vec2;
using glm::mat4;

typedef function<void()> TransformUpdateAction;

class TransformComponent
{
public:
    DLL TransformComponent*& Parent();
    DLL void SetParent(TransformComponent* _parent);

    DLL float Rotation() const;
    DLL float LocalRotation() const;

    DLL void SetRotation(const float& _newRot);

    DLL void UpdateRotation(const float& _amount);

    DLL void Position(float& _x, float& _y) const;
    DLL vec2 Position() const;

    DLL void LocalPosition(float& _x, float& _y) const;
    DLL vec2 LocalPosition() const;

    DLL void SetPosition(const vec2& _newPosition);
    DLL void SetPosition(const float& _newX, const float& _newY);

    DLL void UpdatePosition(const vec2& _amount);
    DLL void UpdatePosition(const float& _x, const float& _y);

    DLL void Scale(float& _x, float& _y) const;
    DLL vec2 Scale() const;

    DLL void LocalScale(float& _x, float& _y) const;
    DLL vec2 LocalScale() const;

    DLL void SetScale(const vec2& _newScale);
    DLL void SetScale(const float& _newX, const float& _newY);

    DLL void UpdateScale(const vec2& _amount);
    DLL void UpdateScale(const float& _x, const float& _y);

    DLL void TRS(const vec2& _pos, const float& _angle, const vec2& _scale);

private:
    friend class GameObject;

    mat4 m_transform;
    TransformComponent* m_parent;
    vector<TransformComponent*> m_children;
    vector<TransformUpdateAction> m_listUpdates;

private:
    TransformComponent() : m_transform(mat4(1.f)), m_parent(nullptr)
    {
    }

    DLL mat4 GlobalTransform() const;

    DLL void AddChild(TransformComponent* _child);
    DLL void RemoveChild(TransformComponent* _child);
    DLL void Tick();
};
