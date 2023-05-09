#include <Leviathan/GameObjects/TransformComponent.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <raylib.h>

using glm::vec3;
using glm::vec4;
using glm::quat;

TransformComponent*& TransformComponent::Parent()
{
	return m_parent;
}

void TransformComponent::SetParent(TransformComponent* _parent)
{
	if (_parent == nullptr)
	{
		if (m_parent != nullptr)
		{
			m_parent->RemoveChild(this);
		}
	}
	else
	{
		_parent->AddChild(this);
	}
}

float TransformComponent::Rotation()
{
	vec3 scale;
	quat rot;
	vec3 trans;
	vec3 skew;
	vec4 perspective;

	glm::decompose(GlobalTransform(), scale, rot, trans, skew, perspective);

	return glm::eulerAngles(rot).z * RAD2DEG;
}

float TransformComponent::LocalRotation()
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

	glm::decompose(m_transform, scale, rot, trans, skew, perspective);

	m_transform = glm::translate(mat4(1.f), trans) *
		glm::toMat4(glm::angleAxis(_newRot * DEG2RAD, vec3(0, 0, 1.f))) *
		glm::scale(mat4(1.f), scale);
}

void TransformComponent::UpdateRotation(const float& _amount)
{
	m_transform = m_transform * glm::toMat4(glm::angleAxis(_amount * DEG2RAD, vec3(0, 0, 1.f)));
}

void TransformComponent::Position(float& _x, float& _y)
{
	vec2 pos = Position();
	_x = pos.x;
	_y = pos.y;
}

vec2 TransformComponent::Position()
{
	vec3 scale;
	quat rot;
	vec3 trans;
	vec3 skew;
	vec4 perspective;

	glm::decompose(GlobalTransform(), scale, rot, trans, skew, perspective);

	return trans;
}

void TransformComponent::LocalPosition(float& _x, float& _y)
{
	vec2 pos = LocalPosition();
	_x = pos.x;
	_y = pos.y;
}

vec2 TransformComponent::LocalPosition()
{
	vec3 scale;
	quat rot;
	vec3 trans;
	vec3 skew;
	vec4 perspective;

	glm::decompose(m_transform, scale, rot, trans, skew, perspective);

	return trans;
}

void TransformComponent::SetPosition(const vec2& _newPosition)
{
	vec3 scale;
	quat rot;
	vec3 trans;
	vec3 skew;
	vec4 perspective;

	glm::decompose(m_transform, scale, rot, trans, skew, perspective);

	m_transform = glm::translate(mat4(1.f), vec3(_newPosition, 0.f)) *
		glm::toMat4(rot) *
		glm::scale(mat4(1.f), scale);
}

void TransformComponent::SetPosition(const float& _newX, const float& _newY)
{
	SetPosition({ _newX, _newY });
}

void TransformComponent::UpdatePosition(const vec2& _amount)
{
	m_transform = glm::translate(m_transform, vec3(_amount, 0.f));
}

void TransformComponent::UpdatePosition(const float& _x, const float& _y)
{
	UpdatePosition({ _x, _y });
}

void TransformComponent::Scale(float& _x, float& _y)
{
	vec2 scale = Scale();
	_x = scale.x;
	_y = scale.y;
}

vec2 TransformComponent::Scale()
{
	vec3 scale;
	quat rot;
	vec3 trans;
	vec3 skew;
	vec4 perspective;

	glm::decompose(GlobalTransform(), scale, rot, trans, skew, perspective);

	return scale;
}

void TransformComponent::LocalScale(float& _x, float& _y)
{
	vec2 scale = LocalScale();
	_x = scale.x;
	_y = scale.y;
}

vec2 TransformComponent::LocalScale()
{
	vec3 scale;
	quat rot;
	vec3 trans;
	vec3 skew;
	vec4 perspective;

	glm::decompose(m_transform, scale, rot, trans, skew, perspective);

	return scale;
}

void TransformComponent::SetScale(const vec2& _newScale)
{
	vec3 scale;
	quat rot;
	vec3 trans;
	vec3 skew;
	vec4 perspective;

	glm::decompose(m_transform, scale, rot, trans, skew, perspective);

	m_transform = glm::translate(mat4(1.f), trans) *
		glm::toMat4(rot) *
		glm::scale(mat4(1.f), vec3(_newScale, 1.f));
}

void TransformComponent::SetScale(const float& _newX, const float& _newY)
{
	SetScale({ _newX, _newY });
}

void TransformComponent::UpdateScale(const vec2& _amount)
{
	m_transform = glm::scale(m_transform, vec3(_amount, 1.f));
}

void TransformComponent::UpdateScale(const float& _x, const float& _y)
{
	UpdateScale({ _x, _y });
}

void TransformComponent::TRS(const vec2& _pos, const float& _angle, const vec2& _scale)
{
	SetPosition(_pos);
	SetScale(_scale);
	SetRotation(_angle);
}

mat4 TransformComponent::GlobalTransform()
{
	return m_parent != nullptr ? m_parent->m_transform * m_transform : m_transform;
}

void TransformComponent::AddChild(TransformComponent* _child)
{
	m_listUpdates.push_back([&, this]()
		{
			if (_child->m_parent != nullptr)
				_child->m_parent->RemoveChild(_child);

			_child->m_parent = this;
			m_children.push_back(_child);
		});
}

void TransformComponent::RemoveChild(TransformComponent* _child)
{
	m_listUpdates.push_back([&, this]()
		{
			if (_child->m_parent == this)
			{
				_child->m_parent = nullptr;
				
				vector<TransformComponent*>::iterator iter = std::find(m_children.begin(), m_children.end(), _child);
				if (iter != m_children.end())
					m_children.erase(iter, iter);
			}
		});
}

void TransformComponent::Tick()
{
	for (auto iter = m_listUpdates.begin(); iter != m_listUpdates.end(); iter++)
	{
		(*iter)();
	}

	m_listUpdates.clear();

	for (auto iter = m_children.begin(); iter != m_children.end(); iter++)
	{
		(*iter)->Tick();
	}
}
