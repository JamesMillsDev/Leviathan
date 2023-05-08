#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Singleton.h>

#include <functional>
#include <vector>
#include <list>

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

private:
	friend class Application;

	const float TIME_STEP = 1.f / 60.f;

	class b2World* m_world;
	class Config* m_config;
	int m_velocityIterations;
	int m_positionIterations;

private:
	DLL static void Tick();

};