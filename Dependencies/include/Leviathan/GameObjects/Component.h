#pragma once

class IComponent
{
protected:
	class IGameObject* m_owner;

	virtual void Load() {}
	virtual void Tick() {}
	virtual void Render() {}
	virtual void Unload() {}

private:
	friend class IGameObject;

	IComponent(class IGameObject* _owner) : m_owner(_owner) {}


};