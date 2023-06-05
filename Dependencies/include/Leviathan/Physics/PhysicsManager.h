#pragma once

#include <Leviathan/Core/Leviathan.h>
#include <Leviathan/Utils/Singleton.h>

#include <vector>
#include <list>
#include <map>

#include <box2d/b2_math.h>

using std::vector;
using std::list;
using std::pair;
using std::map;

class PhysicsManager : public Singleton<PhysicsManager>
{
public:
	DLL PhysicsManager();
	PhysicsManager(PhysicsManager&) = delete;
	DLL ~PhysicsManager();
	DLL virtual void OnCreate() override;
	DLL virtual void OnDestroy() override;
	DLL static vector<class b2Body*> GetBodies();

	DLL static int PolygonCollisionDensity() { return m_instance->m_polygonDensity; }

private:
	friend class Application;
	friend class Rigidbody;
	friend class Collider;
	friend class ContactListener;

	const float TIME_STEP = 1.f / 60.f;

	class b2World* m_world;
	class Config* m_config;
	/*class ContactListener* m_contactListener;*/
	int m_velocityIterations;
	int m_positionIterations;
	map<class b2Body*, class Rigidbody*> m_bodies;
	map<class b2Fixture*, class Collider*> m_colliders;

	int m_polygonDensity;

private:
	DLL static void Tick();

	DLL static class b2Body* CreateBody(struct b2BodyDef* _bodyDef);

	DLL static void ObserveBody(class Rigidbody* _body);
	DLL static void StopObservingBody(class Rigidbody* _body);

	DLL static void ObserveCollider(class Collider* _collider);
	DLL static void StopObservingCollider(class Collider* _collider);

	DLL static class Rigidbody* FindBodyFor(class b2Fixture* _fixture);
	DLL static class Collider* FindColliderFor(class b2Fixture* _fixture);

};