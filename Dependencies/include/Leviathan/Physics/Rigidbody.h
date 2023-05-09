#pragma once

#include <Leviathan/GameObjects/Component.h>
#include <Leviathan/Math/Vec2.h>

class Rigidbody : public Component
{
public:
	DLL const Vec2& GetVelocity() const;
	DLL const float& GetAngularVelocity() const;
	
	DLL const float& GetGravityScale() const;

	DLL const bool& IsRotationLocked() const;

	DLL const bool& IsKinematic() const;
	DLL const bool& IsStatic() const;

	DLL void SetVelocity(Vec2& _velocity);
	DLL void SetAngularVelocity(float _velocity);

	DLL void SetGravityScale(float _scale);

	DLL void LockRotation(bool _locked);

	DLL void SetKinematic(bool _isKinematic);
	DLL void SetStatic(bool _isStatic);

	DLL virtual void SetEnabled(bool _enabled) override;

protected:
	friend class GameObject;
	friend class TestGame;

	Vec2 m_velocity;
	float m_angularVelocity;
	float m_gravityScale;
	bool m_isKinematic;
	bool m_isStatic;

	bool m_lockRotation;

protected:

	DLL Rigidbody(class GameObject* _owner);
	DLL ~Rigidbody();

	DLL virtual void Load() override;
	DLL virtual void Tick() override;
	DLL virtual void Unload() override;

private:
	class b2Body* m_body;
	struct b2BodyDef* m_bodyDef;

private:
	DLL static void OnAddRemoveComponent(Component* _component, bool _added, Component* _caller);

};