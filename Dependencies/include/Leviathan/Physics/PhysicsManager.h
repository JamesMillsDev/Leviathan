#pragma once

#include <Leviathan/Core/Leviathan.h>
#include <Leviathan/Utils/Singleton.h>

#include <functional>
#include <vector>
#include <list>

#include <box2d/b2_math.h>

using std::function;
using std::vector;
using std::list;
using std::pair;

class PhysicsManager : public Singleton<PhysicsManager>
{
public:
	DLL PhysicsManager();
	PhysicsManager(PhysicsManager&) = delete;
	DLL ~PhysicsManager();
	DLL virtual void OnCreate() override;
	DLL static vector<class b2Body*> GetBodies();

	DLL static int PolygonCollisionDensity() { return m_instance->m_polygonDensity; }

private:
	friend class Application;
	friend class Rigidbody;

	const float TIME_STEP = 1.f / 60.f;

	class b2World* m_world;
	class Config* m_config;
	int m_velocityIterations;
	int m_positionIterations;

	int m_polygonDensity;

private:
	DLL static void Tick();

	DLL static class b2Body* CreateBody(struct b2BodyDef* _bodyDef);

};