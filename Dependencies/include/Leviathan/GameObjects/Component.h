#pragma once

class Component
{
public:
	const bool& IsEnabled() const { return m_enabled; }
	virtual void SetEnabled(bool _enabled) { m_enabled = _enabled; }

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