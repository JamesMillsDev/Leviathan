#include <Leviathan/Physics/PhysicsManager.h>

#include <Leviathan/Config.h>

#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Draw.h>

#include <Leviathan/Application.h>

#include <glm/vec2.hpp>

using glm::vec2;

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

	vec2 gravity = *m_config->GetValue<vec2>("World", "gravity");
	m_world = new b2World({ gravity.x, gravity.y });

	m_velocityIterations = *m_config->GetValue<int>("World", "velocityIterations");
	m_positionIterations = *m_config->GetValue<int>("World", "positionIterations");
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
