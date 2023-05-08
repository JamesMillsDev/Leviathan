#pragma once

#include <Leviathan/GameObjects/Component.h>

class Rigidbody : public Component
{
public:

protected:
	friend class GameObject;

protected:
	Rigidbody(class GameObject* _owner);

	virtual void Load() override;
	virtual void Tick() override;
	virtual void Unload() override;

private:
	class b2Body* m_body;
	struct b2BodyDef* m_bodyDef;

};