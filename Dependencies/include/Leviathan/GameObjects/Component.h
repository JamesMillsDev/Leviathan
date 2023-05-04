#pragma once

class IComponent
{
protected:
	friend class IGameObject;

	class IGameObject* m_owner;

	IComponent(class IGameObject* _owner) : m_owner(_owner) {}

	virtual void Load() {}
	virtual void Tick() {}
	virtual void Render() {}
	virtual void Unload() {}


};