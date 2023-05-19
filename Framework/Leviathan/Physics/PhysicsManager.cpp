#include <Leviathan/Physics/PhysicsManager.h>

#include <Leviathan/Utils/Config.h>
#include <Leviathan/Utils/ConfigValue.h>

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>

#include <Leviathan/Core/Application.h>

#include <Leviathan/Physics/Rigidbody.h>
#include <Leviathan/Physics/Collider.h>
//#include <Leviathan/Physics/ContactListener.h>

#include <glm/vec2.hpp>

#include <raylib/raylib.h>

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

	/*m_contactListener = new ContactListener();
	m_world->SetContactListener(m_contactListener);*/
}

void PhysicsManager::OnDestroy()
{
	delete m_config;
	m_config = nullptr;

	/*delete m_contactListener;
	m_contactListener = nullptr;*/

	delete m_world;
	m_world = nullptr;
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

void PhysicsManager::ObserveBody(Rigidbody* _body)
{
	map<b2Body*, Rigidbody*>& bodies = m_instance->m_bodies;
	if (!bodies.contains(_body->m_body))
		bodies[_body->m_body] = _body;
}

void PhysicsManager::StopObservingBody(Rigidbody* _body)
{
	map<b2Body*, Rigidbody*>& bodies = m_instance->m_bodies;
	if (bodies.contains(_body->m_body))
		bodies.erase(bodies.find(_body->m_body));
}

void PhysicsManager::ObserveCollider(Collider* _collider)
{
	map<b2Fixture*, Collider*>& colliders = m_instance->m_colliders;
	if (!colliders.contains(_collider->m_fixture))
		colliders[_collider->m_fixture] = _collider;
}

DLL void PhysicsManager::StopObservingCollider(Collider* _collider)
{
	map<b2Fixture*, Collider*>& colliders = m_instance->m_colliders;
	if (colliders.contains(_collider->m_fixture))
		colliders.erase(colliders.find(_collider->m_fixture));
}

Rigidbody* PhysicsManager::FindBodyFor(b2Fixture* _fixture)
{
	b2Body* body = _fixture->GetBody();
	map<b2Body*, Rigidbody*>& bodies = m_instance->m_bodies;

	if (bodies.contains(body))
		return bodies[body];

	return nullptr;
}

Collider* PhysicsManager::FindColliderFor(b2Fixture* _fixture)
{
	map<b2Fixture*, Collider*>& colliders = m_instance->m_colliders;

	if (colliders.contains(_fixture))
		return colliders[_fixture];

	return nullptr;
}