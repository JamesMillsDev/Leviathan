#include <Leviathan/GameObjects/TransformComponent.h>

#include <Leviathan/Math/Leviamath.h>

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
	return GlobalTransform().GetRotation();
}

float TransformComponent::LocalRotation()
{
	return m_transform.GetRotation();
}

void TransformComponent::SetRotation(const float& _newRot)
{
	m_transform.SetRotation(_newRot * DEG_2_RAD);
}

void TransformComponent::UpdateRotation(const float& _amount)
{
	m_transform.SetRotation(m_transform.GetRotation() + _amount * DEG_2_RAD);
}

void TransformComponent::Position(float& _x, float& _y)
{
	Vec2 pos = Position();
	_x = pos.x;
	_y = pos.y;
}

Vec2 TransformComponent::Position()
{
	return GlobalTransform().GetTranslation();
}

void TransformComponent::LocalPosition(float& _x, float& _y)
{
	Vec2 pos = LocalPosition();
	_x = pos.x;
	_y = pos.y;
}

Vec2 TransformComponent::LocalPosition()
{
	return m_transform.GetTranslation();
}

void TransformComponent::SetPosition(const Vec2& _newPosition)
{
	m_transform.SetTranslation(_newPosition);
}

void TransformComponent::SetPosition(const float& _newX, const float& _newY)
{
	SetPosition({ _newX, _newY });
}

void TransformComponent::UpdatePosition(const Vec2& _amount)
{
	m_transform.Translate(_amount);
}

void TransformComponent::UpdatePosition(const float& _x, const float& _y)
{
	UpdatePosition({ _x, _y });
}

void TransformComponent::Scale(float& _x, float& _y)
{
	Vec2 scale = Scale();
	_x = scale.x;
	_y = scale.y;
}

Vec2 TransformComponent::Scale()
{
	return GlobalTransform().GetScale();
}

void TransformComponent::LocalScale(float& _x, float& _y)
{
	Vec2 scale = LocalScale();
	_x = scale.x;
	_y = scale.y;
}

Vec2 TransformComponent::LocalScale()
{
	return m_transform.GetScale();
}

void TransformComponent::SetScale(const Vec2& _newScale)
{
	m_transform.SetScale(_newScale);
}

void TransformComponent::SetScale(const float& _newX, const float& _newY)
{
	SetScale({ _newX, _newY });
}

void TransformComponent::UpdateScale(const Vec2& _amount)
{
	m_transform.SetScale(m_transform.GetScale() + _amount);
}

void TransformComponent::UpdateScale(const float& _x, const float& _y)
{
	UpdateScale({ _x, _y });
}

Mat3 TransformComponent::GlobalTransform()
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
