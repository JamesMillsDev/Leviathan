#pragma once

class Component
{
protected:
	friend class GameObject;

	class GameObject* m_owner;

	Component(class GameObject* _owner) : m_owner(_owner) {}

	virtual void Load() {}
	virtual void Tick() {}
	virtual void Render() {}
	virtual void Unload() {}


};