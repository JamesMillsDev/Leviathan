#pragma once

#include <Leviathan/GameObjects/Component.h>
#include <Leviathan/Leviathan.h>

#include <glm/vec2.hpp>

using glm::vec2;

class Rigidbody : public Component
{
public:
	DLL const vec2& GetVelocity() const;
	DLL const float& GetAngularVelocity() const;
	
	DLL const float& GetGravityScale() const;
	DLL const float& GetMass() const;
	DLL const float& GetFriction() const;

	DLL const bool& IsRotationLocked() const;

	DLL const bool& IsKinematic() const;
	DLL const bool& IsStatic() const;

	DLL void SetVelocity(vec2& _velocity);
	DLL void SetAngularVelocity(float _velocity);

	DLL void SetGravityScale(float _scale);
	DLL void SetMass(float _mass);
	DLL void SetFriction(float _friction);

	DLL void LockRotation(bool _locked);

	DLL void SetKinematic(bool _isKinematic);
	DLL void SetStatic(bool _isStatic);

	DLL virtual void SetEnabled(bool _enabled) override;

protected:
	friend class GameObject;
	friend class TestGame;

	vec2 m_velocity;
	float m_angularVelocity;

	float m_gravityScale;
	float m_mass;
	float m_friction;
	
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
	int m_fixtureCount;

private:
	DLL static void OnAddRemoveComponent(Component* _component, bool _added, Component* _caller);

};