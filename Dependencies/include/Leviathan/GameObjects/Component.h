#pragma once

#include <Leviathan/Core/Object.h>

class Component : public Object
{
public:
	virtual ~Component() = default;
	const bool& IsEnabled() const { return m_enabled; }
	virtual void SetEnabled(const bool _enabled) { m_enabled = _enabled; }

	const class GameObject* GetOwner() const { return m_owner; }

protected:
	friend class GameObject;

	class GameObject* m_owner;

	bool m_enabled;

protected:
	Component(class GameObject* _owner) : m_owner(_owner), m_enabled(true) {}

	virtual void Load() {}
	virtual void Tick() {}
	virtual void Render() {}
	virtual void Unload() {}

	virtual void OnDrawGizmos() {}


};