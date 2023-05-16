#include <Leviathan/Physics/PhysicsManager.h>

#include <Leviathan/Config.h>
#include <Leviathan/ConfigValue.h>

#include <Box2D/Box2D.h>

#include <Leviathan/Application.h>

#include <glm/vec2.hpp>

#include <raylib.h>

using glm::vec2;

PhysicsManager::PhysicsManager()
	: m_world(nullptr), m_config(nullptr), m_positionIterations(0), 
	m_velocityIterations(0), m_polygonDensity(5)
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
	m_instance->m_world->Step(m_instance->TIME_STEP * GetFrameTime() * 1000, m_instance->m_velocityIterations, m_instance->m_positionIterations);
}

void PhysicsManager::OnCreate()
{
	m_config = new Config("physics.cfg");

	vec2 gravity = m_config->GetValue("World", "gravity")->Get<vec2>();
	m_world = new b2World({ gravity.x, gravity.y });

	m_velocityIterations = m_config->GetValue("World", "velocityIterations")->Get<int>();
	m_positionIterations = m_config->GetValue("World", "positionIterations")->Get<int>();
	m_polygonDensity = m_config->GetValue("Collision", "polygonDensity")->Get<int>();
}

vector<b2Body*> PhysicsManager::GetBodies()
{
	vector<b2Body*> bodies;

	for (int i = 0; i < m_instance->m_world->GetBodyCount(); i++)
	{
		b2Body* body = &m_instance->m_world->GetBodyList()[i];
		if(body != nullptr)
			bodies.push_back(&m_instance->m_world->GetBodyList()[i]);
	}

	return bodies;
}

b2Body* PhysicsManager::CreateBody(b2BodyDef* _bodyDef)
{
	return m_instance->m_world->CreateBody(_bodyDef);
}
