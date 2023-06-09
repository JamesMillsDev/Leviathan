#include <Leviathan/GameObjects/TransformComponent.h>

#include <glm/ext/matrix_transform.hpp>

#include <glm/glm.hpp>

#include <glm/gtc/quaternion.hpp>

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <raylib/raylib.h>

using glm::quat;
using glm::vec3;
using glm::vec4;

TransformComponent*& TransformComponent::Parent()
{
    return m_parent;
}

void TransformComponent::SetParent(TransformComponent* _parent)
{
    if(_parent == nullptr)
    {
        if(m_parent != nullptr)
        {
            m_parent->RemoveChild(this);
        }
    }
    else
    {
        _parent->AddChild(this);
    }
}

float TransformComponent::Rotation() const
{
    vec3 scale;
    quat rot;
    vec3 trans;
    vec3 skew;
    vec4 perspective;

    glm::decompose(GlobalTransform(), scale, rot, trans, skew, perspective);

    return glm::eulerAngles(rot).z * RAD2DEG;
}

float TransformComponent::LocalRotation() const
{
    vec3 scale;
    quat rot;
    vec3 trans;
    vec3 skew;
    vec4 perspective;

    glm::decompose(m_transform, scale, rot, trans, skew, perspective);

    return glm::eulerAngles(rot).z * RAD2DEG;
}

void TransformComponent::SetRotation(const float& _newRot)
{
    vec3 scale;
    quat rot;
    vec3 trans;
    vec3 skew;
    vec4 perspective;

    decompose(m_transform, scale, rot, trans, skew, perspective);

    m_transform = translate(mat4(1.f), trans) *
        toMat4(angleAxis(_newRot * DEG2RAD, vec3(0, 0, 1.f))) *
        glm::scale(mat4(1.f), scale);
}

void TransformComponent::UpdateRotation(const float& _amount)
{
    m_transform = m_transform * toMat4(angleAxis(_amount * DEG2RAD, vec3(0, 0, 1.f)));
}

void TransformComponent::AnchoredPosition(float& _x, float& _y) const
{
    const vec2 pos = AnchoredPosition();
    _x = pos.x;
    _y = pos.y;
}

vec2 TransformComponent::AnchoredPosition() const
{
    vec3 scale;
    quat rot;
    vec3 trans;
    vec3 skew;
    vec4 perspective;

    decompose(GlobalTransform(), scale, rot, trans, skew, perspective);

    return trans;
}

void TransformComponent::LocalPosition(float& _x, float& _y) const
{
    const vec2 pos = LocalPosition();
    _x = pos.x;
    _y = pos.y;
}

vec2 TransformComponent::LocalPosition() const
{
    vec3 scale;
    quat rot;
    vec3 trans;
    vec3 skew;
    vec4 perspective;

    decompose(m_transform, scale, rot, trans, skew, perspective);

    return trans;
}

void TransformComponent::SetAnchoredPosition(const vec2& _newPosition)
{
    vec3 scale;
    quat rot;
    vec3 trans;
    vec3 skew;
    vec4 perspective;

    decompose(m_transform, scale, rot, trans, skew, perspective);

    m_transform = translate(mat4(1.f), vec3(_newPosition, 0.f)) *
        toMat4(rot) *
        glm::scale(mat4(1.f), scale);
}

void TransformComponent::SetAnchoredPosition(const float& _newX, const float& _newY)
{
    SetAnchoredPosition({ _newX, _newY });
}

void TransformComponent::UpdateAnchoredPosition(const vec2& _amount)
{
    m_transform = glm::translate(m_transform, vec3(_amount, 0.f));
}

void TransformComponent::UpdateAnchoredPosition(const float& _x, const float& _y)
{
    UpdateAnchoredPosition({ _x, _y });
}

void TransformComponent::Scale(float& _x, float& _y) const
{
    const vec2 scale = Scale();
    _x = scale.x;
    _y = scale.y;
}

vec2 TransformComponent::Scale() const
{
    vec3 scale;
    quat rot;
    vec3 trans;
    vec3 skew;
    vec4 perspective;

    decompose(GlobalTransform(), scale, rot, trans, skew, perspective);

    return scale;
}

void TransformComponent::LocalScale(float& _x, float& _y) const
{
    const vec2 scale = LocalScale();
    _x = scale.x;
    _y = scale.y;
}

vec2 TransformComponent::LocalScale() const
{
    vec3 scale;
    quat rot;
    vec3 trans;
    vec3 skew;
    vec4 perspective;

    decompose(m_transform, scale, rot, trans, skew, perspective);

    return scale;
}

void TransformComponent::SetScale(const vec2& _newScale)
{
    vec3 scale;
    quat rot;
    vec3 trans;
    vec3 skew;
    vec4 perspective;

    decompose(m_transform, scale, rot, trans, skew, perspective);

    m_transform = translate(mat4(1.f), trans) *
        toMat4(rot) *
        glm::scale(mat4(1.f), vec3(_newScale, 1.f));
}

void TransformComponent::SetScale(const float& _newX, const float& _newY)
{
    SetScale({ _newX, _newY });
}

void TransformComponent::UpdateScale(const vec2& _amount)
{
    m_transform = scale(m_transform, vec3(_amount, 1.f));
}

void TransformComponent::UpdateScale(const float& _x, const float& _y)
{
    UpdateScale({ _x, _y });
}

void TransformComponent::TRS(const vec2& _pos, const float& _angle, const vec2& _scale)
{
    SetAnchoredPosition(_pos);
    SetScale(_scale);
    SetRotation(_angle);
}

mat4 TransformComponent::GlobalTransform() const
{
    return m_parent != nullptr ? m_parent->m_transform * m_transform : m_transform;
}

void TransformComponent::AddChild(TransformComponent* _child)
{
    m_listUpdates.emplace_back([&, this]()
    {
        if(_child->m_parent != nullptr)
            _child->m_parent->RemoveChild(_child);

        _child->m_parent = this;
        m_children.push_back(_child);
    });
}

void TransformComponent::RemoveChild(TransformComponent* _child)
{
    m_listUpdates.emplace_back([&, this]()
    {
        if(_child->m_parent == this)
        {
            _child->m_parent = nullptr;

            const vector<TransformComponent*>::iterator iter = std::ranges::find(m_children, _child);
            if(iter != m_children.end())
                m_children.erase(iter, iter);
        }
    });
}

void TransformComponent::Tick()
{
    for(auto iter = m_listUpdates.begin(); iter != m_listUpdates.end(); ++iter)
        (*iter)();

    m_listUpdates.clear();

    for(auto iter = m_children.begin(); iter != m_children.end(); ++iter)
        (*iter)->Tick();
}
