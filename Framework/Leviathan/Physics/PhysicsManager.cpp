#include <Leviathan/Physics/PhysicsManager.h>

#include <Leviathan/Config.h>

#include <Box2D/Box2D.h>

PhysicsManager::PhysicsManager()
	: m_world(nullptr), m_config(nullptr), m_positionIterations(0), m_velocityIterations(0)
{
}

PhysicsManager::~PhysicsManager()
{
	delete m_config;
	m_config = nullptr;

	delete m_world;
	m_world = nullptr;
}

void PhysicsManager::Tick()
{
	m_instance->m_world->Step(m_instance->TIME_STEP, m_instance->m_velocityIterations, m_instance->m_positionIterations);
}

void PhysicsManager::OnCreate()
{
	m_config = new Config("physics.cfg");

	Vec2 gravity = *m_config->GetValue<Vec2>("World", "gravity");
	m_world = new b2World(gravity);

	m_velocityIterations = *m_config->GetValue<int>("World", "velocityIterations");
	m_positionIterations = *m_config->GetValue<int>("World", "positionIterations");
}