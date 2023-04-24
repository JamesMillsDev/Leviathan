#include <Leviathan/GameObjects/Transform.h>

#include <Leviathan/Math/Leviamath.h>

Transform*& Transform::Parent()
{
	return m_parent;
}

void Transform::SetParent(Transform* _parent)
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

float Transform::Rotation()
{
	return GlobalTransform().GetRotation();
}

float Transform::LocalRotation()
{
	return m_transform.GetRotation();
}

void Transform::SetRotation(const float& _newRot)
{
	m_transform.SetRotation(_newRot * Leviamath::DEG_2_RAD);
}

void Transform::UpdateRotation(const float& _amount)
{
	m_transform.SetRotation(m_transform.GetRotation() + _amount * Leviamath::DEG_2_RAD);
}

void Transform::Position(float& _x, float& _y)
{
	Vec2 pos = Position();
	_x = pos.x;
	_y = pos.y;
}

Vec2 Transform::Position()
{
	return GlobalTransform().GetTranslation();
}

void Transform::LocalPosition(float& _x, float& _y)
{
	Vec2 pos = LocalPosition();
	_x = pos.x;
	_y = pos.y;
}

Vec2 Transform::LocalPosition()
{
	return m_transform.GetTranslation();
}

void Transform::SetPosition(const Vec2& _newPosition)
{
	m_transform.SetTranslation(_newPosition);
}

void Transform::SetPosition(const float& _newX, const float& _newY)
{
	SetPosition({ _newX, _newY });
}

void Transform::UpdatePosition(const Vec2& _amount)
{
	m_transform.Translate(_amount);
}

void Transform::UpdatePosition(const float& _x, const float& _y)
{
	UpdatePosition({ _x, _y });
}

void Transform::Scale(float& _x, float& _y)
{
	Vec2 scale = Scale();
	_x = scale.x;
	_y = scale.y;
}

Vec2 Transform::Scale()
{
	return GlobalTransform().GetScale();
}

void Transform::LocalScale(float& _x, float& _y)
{
	Vec2 scale = LocalScale();
	_x = scale.x;
	_y = scale.y;
}

Vec2 Transform::LocalScale()
{
	return m_transform.GetScale();
}

void Transform::SetScale(const Vec2& _newScale)
{
	m_transform.SetScale(_newScale);
}

void Transform::SetScale(const float& _newX, const float& _newY)
{
	SetScale({ _newX, _newY });
}

void Transform::UpdateScale(const Vec2& _amount)
{
	m_transform.SetScale(m_transform.GetScale() + _amount);
}

void Transform::UpdateScale(const float& _x, const float& _y)
{
	UpdateScale({ _x, _y });
}

Mat3 Transform::GlobalTransform()
{
	return m_parent != nullptr ? m_parent->m_transform * m_transform : m_transform;
}

void Transform::AddChild(Transform* _child)
{
	m_listUpdates.push_back([&, this]()
		{
			if (_child->m_parent != nullptr)
				_child->m_parent->RemoveChild(_child);

			_child->m_parent = this;
			m_children.push_back(_child);
		});
}

void Transform::RemoveChild(Transform* _child)
{
	m_listUpdates.push_back([&, this]()
		{
			if (_child->m_parent == this)
			{
				_child->m_parent = nullptr;
				
				vector<Transform*>::iterator iter = std::find(m_children.begin(), m_children.end(), _child);
				if (iter != m_children.end())
					m_children.erase(iter, iter);
			}
		});
}

void Transform::Tick()
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
